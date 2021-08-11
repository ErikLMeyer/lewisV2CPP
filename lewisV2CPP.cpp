/*********************************************************************************************
Title:       lewisV2CPP.cpp
Author:      Erik L. Meyer
Created on:  July 13, 2021
Description: The main file of the translator software.
Purpose:     Takes in the files to be translated.
Usage:       ./lewisV2CPP [Verilog files] [output file]
		     Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/


#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <regex>
#include "Token.h"
#include "TokenTree.h"
#include "ToTrTree.h"
#include "Converter.h"

using namespace T;
using namespace TT;
using namespace TTT;
using namespace C;
using namespace std;

const int BUF_SIZE = 1024;
const char* IGNORE_CHARS = " \f\n\r\t\v,;";

vector<FILE*> files;
int noErr, noWarn; // # of errors and warnings
ToTrTree mainMod;
bool closedComment; // Tracks if a multiline comment has closed for stripComments

void printNoWarn(string message){
	if (0 < noWarn){
		cout << message;
		printf("%d warnings", noWarn);
	}
}

/* void subTokenize(char* line, TokenTree s, const char* fn, int ln){
	// seperate certain tokens even further
  size_t sOT, eOT;
			
} */

/* Strips comments from the passed char array.
   Returns a new char array with the comments removed
   if there are any.
   Returns an array with the same values if there are no comments
   or if the comments are improperly formatted. */
char* stripComments(char c[]){
  string line = c;
  size_t foundO = -1;
  size_t foundC;
  bool hasRun = true;
 
  do {
    foundC = line.find("*/", foundO + 1);
    foundO = line.find("/*", foundO + 1);
    if (closedComment and foundC < foundO){
      return c;
    }
    
    if (foundO != string::npos){
      foundC = line.find("*/", foundO + 1);
      closedComment = false;
      if (foundC != string::npos){
        closedComment = true;
        line.replace(foundO, (foundC + 2) - foundO, "");
      } else{
        line.replace(foundO, line.length(), "");
        break;
      }
    } else{
      foundC = line.find("*/");
      if (foundC != string::npos){
        closedComment = true;
        line.replace(0, (foundC + 2), "");
      } else
        hasRun = false;
    }
  } while (string::npos != foundO);

  if (!hasRun and !closedComment)
    line.replace(0, line.length(), "");

  char* cReturn = new char [line.length() + 1];
  strcpy(cReturn, line.c_str());
  return cReturn;
}

// Returns true if given char array == "//"
bool isSingleComment(char* s){
	if (strcmp(s, "//") == 0)
		return true;
	return false;
}

bool isBlockKeyword(char* v){
  // The keywords that result in blocks
  // TODO: Add the rest or find a better way to do it
  const char* blockKeywords[] = {keywords[1], keywords[4], keywords[39]};
  for (int i = 0; i < 3; i++){
    if(strcmp(v, blockKeywords[i]))
      return true;
  }
  return false;
}

bool isEndKeyword(char* v){
  if(regex_match(v, regex("^(end).*$"))){
    return true;
  } else
    return false;
}

void read(FILE* f, const char* fn){
	char buf[BUF_SIZE];
	int lineNo = 0;
  int noOfParen = 0;
	bool parenHasClosed = true;
	bool newBranch;
	
	while(NULL != fgets(buf, BUF_SIZE, f)){
	  TokenTree *thisStatement = new TokenTree();
    // For removing multiline comments
		strcpy(buf, stripComments(buf));
		
    char* line;
		line = strtok(buf, IGNORE_CHARS);
		
		/* turn elements of line into Token objects, send them to the current tree */
		while (line != NULL){
			if (isSingleComment(line))
				break;
      /* send line to be split further.
         Is used to account for programmers that
         don't believe in putting spaces between their operators */
      // subTokenize(line, thisStatement, fn, lineNo);
      Token newTok(lineNo, fn, line);
			// Determine token type
			newTok.assignType();
      // error check newTok for lexical errors
			thisStatement->placeToken(newTok);
			line = strtok(NULL, IGNORE_CHARS);
		}
		
		lineNo++;
		if (newBranch){
			// send in thisStatement to ToTrTree for assignment
      if (NULL == mainMod.getCurrent()){
        mainMod.placeTree(0, *thisStatement);
      } else if (!isEndKeyword(mainMod.getCurrent()->getRoot().getVal())){
        if (isBlockKeyword(mainMod.getCurrent()->getRoot().getVal()) && 
            NULL == mainMod.getCurrent()->getChild()){
          mainMod.placeTree(1, *thisStatement);
        } else{
          mainMod.placeTree(0, *thisStatement);
        }
      } else{
        mainMod.placeTree(2, *thisStatement);
      }
      // error check thisStatement for single line syntax errors
			// clear thisStatement so it can be reused in the next loop
			// If thisStatement = subModule instantiation, mainMod.addSubmodule(that sub module)
			// read(subModule.v, true); Add multithreading if time allows
		}
	}
  // error check ToTrTree for scope and all other errors prior to exiting function
}

bool parse(const char* vFileName){
	// read file
  read(files[0], vFileName);
	
	// Close vFileName
  fclose(files[0]);
  files.erase(files.begin());
	return (0 < noErr);
}

int main(int argc, char* argv[]){
	// Check for valid command line arguments
  if (1 >= argc){
    cout << "Must specify files to compile.\n";
    return 1;
  }
  if(!regex_match(argv[argc - 1], regex("^.+(\\.cpp)$"))){
    cout << "Must specify a valid output file.\n";
    return 1;
  }

	// Check if specified files exist
  for (int i = 1; i < argc - 1; i++){
    files.push_back(fopen(argv[i], "r"));
    if (NULL == files.back()){
      cout << "Unable to open file " << argv[i] << ".";
      return 1;
    }
  }

  int i = 1;
  while(NULL != files[0]){
	  if (!parse(argv[i])){
		  printf("Parsed %s with %d errors", argv[i], noErr);
	  	printNoWarn(", and ");
	  }
    i++;
	}

  Converter convert(argv[argc - 1]);
  convert.write(mainMod);
  
	// cleanup memory
	printNoWarn("Finished with ");
	
  if (0 < noErr)
    return 1;
	return 0;
}