/*********************************************************************************************
Title:       Token.h
Author:      Erik L. Meyer
Created on:  July 13, 2021
Description: Declaration of the token class.
Purpose:     An object for tracking some of the information tied to a symbol.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

namespace T{
    enum LexType {
      DIRECTIVE,
      KEYWORD,
      BIT_WIDTH,
      OPERATOR, // +, =, &&, etc.
      LITERAL,
      TASK,
      DELAY,
      IDENTIFIER,
      MACRO
    };

    // Verilog's reserved keywords. 94 elements
    static const char* keywords[] = {"and", "always", "assign", "attribute", "begin", "buf",
	  "bufif0", "bufif1", "case", "cmos", "deassign", "default", "defparam", "disable", "else",
	  "endattribute", "end", "endcase", "endfunction", "endprimitive", "endmodule", "endtable",
	  "endtask", "event", "for", "force", "forever", "fork", "function", "highz0", "highz1", "if",
	  "initial", "inout", "input", "integer", "join", "large", "medium", "module", "nand",
	  "negedge", "nor", "not", "notif0", "notif1", "nmos", "or", "output", "parameter", "pmos",
	  "posedge", "primitive", "pulldown", "pullup", "pull0", "pull1", "rcmos", "reg", "release",
	  "repeat", "rnmos", "rpmos", "rtran", "rtranif0", "rtranif1", "scalared", "small", "specify",
	  "specparam", "stron0", "strong1", "supply0", "supply1", "table", "task", "tran", "tranif0",
	  "tranif1", "time", "tri", "triand", "trior", "trireg", "tri0", "tri1", "vectored", "wait",
	  "wand", "weak0", "weak1", "while", "wire", "wor"};

  class Token
  {
    private:
      LexType type; // specifies keyword, constant, etc.
      int lineNo;
      const char* origFile;
      char* val; // The word/symbol/etc. used in the file. e.g. i_leftIn, 54, $write, or 9'hD
      Token *p_parent, *p_leftH, *p_rightH;
      
    public:
      Token(){
		lineNo = 0;
        origFile = NULL;
        val = NULL;
        // parent = NULL;
        p_parent = (Token*) malloc(sizeof(Token)); //&parent;
        // leftH = NULL;
        p_leftH = (Token*) malloc(sizeof(Token)); //&leftH;
        // rightH = NULL;
        p_rightH = (Token*) malloc(sizeof(Token)); //&rightH;
      }

      Token(int ln, const char* f, char* v){
        lineNo = ln;
        origFile = f;
        val = v;
        // parent = NULL;
        p_parent = (Token*) malloc(sizeof(Token)); //&parent;
        // leftH = NULL;
        p_leftH = (Token*) malloc(sizeof(Token)); //&leftH;
        // rightH = NULL;
        p_rightH = (Token*) malloc(sizeof(Token)); //&rightH;
      }

      ~Token(){
		delete origFile;
        delete val;
        delete p_parent;
        delete p_leftH;
        delete p_rightH;
      }
      
      // Getters
      LexType getType() const { return type; }
      int getLineNo() const { return lineNo; }
      const char* getOrigFile() const { return origFile; }
      char* getVal() const { return val; }
      Token* getRight() const { return p_rightH; }
      // Token getLeft() const { return leftH; }
      Token* getLeft() const { return p_leftH; }
      Token* getParent() const { return p_parent; }
      
      // Setters
      void setType(LexType t){ type = t; }
      void setLineNo(int ln){ lineNo = ln; }
      void setOrigFile(const char* fn){ origFile = fn; }
      void setVal(char* v){ val = v; }
      void setParent(Token p){ *p_parent = p; }
      void setParent(Token* p){ p_parent = p; }
      void setLeft(Token l);
      void setLeft(Token* l){ this->setLeft(*l); }
      void setRight(Token r);
      void setRight(Token* r){ this->setRight(*r); }
      
      // Actions
      void assignType();
      
      // Error checking
      int errorCheck();
      
      /* All of these return false if token is improperly formed. 
        Prints appropriate error message with relevant information. */
      bool checkValidDirective();
      bool checkValidKeyword();
      bool checkValidBitWidths();
      bool checkValidOperator();
      bool checkValidLiteral();
      bool checkValidTask();
      bool checkValidDelay();
      bool checkValidIdentifier();
      
      // Overloads
      Token operator=(Token t);
      
  };
}