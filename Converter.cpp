/*********************************************************************************************
Title:       Converter.cpp
Author:      Erik L. Meyer
Created on:  August 10, 2021
Description: Implementation of functions declared in Converter.h
Purpose:     Translates  Token trees and writes to the output file.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex>
#include "Converter.h"
#include "Token.h"
#include "TokenTree.h"
#include "ToTrTree.h"

using namespace std;
using namespace C;
using namespace T;
using namespace TT;
using namespace TTT;



// TODO: Rework this so it isn't brute forcing the translation
void Converter::translate(TokenTree t){
  if (strcmp(t.getRoot().getVal(), "module")){
    char classDec[BUF_SIZE];
    strcpy(classDec, "class ");
    strcat(classDec, (const char*)t.getRoot().getLeft()->getVal());
    strcat(classDec, "{\n");
    brackets++;
    fputs(classDec, outFile);
  } else if(regex_match(t.getRoot().getVal(), regex("^.+(put)$"))){
    if(!inPrivate){
      fputs("private:\n", outFile);
      inPrivate = true;
    }

    t.setCurrent(t.getRoot());
    if(NULL == t.getCurrent().getLeft()){
      // error
    }
    do{
      char varDec[BUF_SIZE];
      strcpy(varDec, "int ");
      strcat(varDec, t.getCurrent().getLeft()->getVal());
      strcat(varDec, ";\n");
      fputs(varDec, outFile);
      t.setCurrent(t.getCurrent().getLeft());
    } while(NULL != t.getCurrent().getLeft());
  }
}

void Converter::write(ToTrTree t){
  TokenTree* translating = (TokenTree*) malloc(sizeof(TokenTree));
  translating = t.getRoot();
  int act = 0;

  while (2 != act){
    switch(act){
      case 0:
        translate(*translating);
        if(NULL != translating->getChild()){
          translating = translating->getChild();
          act = 0;
        } else if (NULL != translating->getNext()){
          translate(*translating);
          translating = translating->getNext();
          act = 0;
        } else{
          translate(*translating);
          translating = translating->getParent();
          if (NULL != translating->getChild()){
            delete translating->getChild();
          } else{
            delete translating->getNext();
          }
          act = 1;
        }
        break;
      case 1:
        if (NULL != translating->getNext()){
          translating = translating->getNext();
          act = 0;
        } else{
          if (NULL == translating->getParent()){
            act = 2;
            break;
          }
          translating = translating->getParent();
          if (NULL != translating->getChild()){
            delete translating->getChild();
          } else{
            delete translating->getNext();
          }
          act = 1;
        }
        break;
    }
  }
  for (int i = 0; i < brackets; i++){
    fputs("}\n", outFile);
  }
  free(translating);
}
