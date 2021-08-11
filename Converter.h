/*********************************************************************************************
Title:       Converter.h
Author:      Erik L. Meyer
Created on:  July 13, 2021
Description: Class declaration of the Converter object
Purpose:     Translate trees and writes to file.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "TokenTree.h"
#include "ToTrTree.h"

namespace C{
  class Converter{
    private:
      char* outFileName;
      FILE* outFile;
      const int BUF_SIZE = 1024;
      int brackets;
      bool inPrivate = false;
      int numVars; // keeps track of how many getters and setters to write
    public:
      Converter(const char* out){
        outFileName = (char*) malloc(sizeof(out));
        strcpy(outFileName, out);
        outFile = fopen(outFileName, "w");
        free(outFileName);
      }

      ~Converter(){
        fclose(outFile);
      }
      
      
      void translate(TT::TokenTree t);
      void write(TTT::ToTrTree t);
  };
}