/*********************************************************************************************
Title:       Token.cpp
Author:      Erik L. Meyer
Created on:  July 15, 2021
Description: Implementation of some of the functions of the Token class.
Purpose:     Turns symbols into Tokens which have some information of the file they're from.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include "Token.h"

using namespace T;
using namespace std;

void Token::setLeft(Token l){
	*p_leftH = l;
	p_leftH->setParent(*this);
}

void Token::setRight(Token r){
	*p_rightH = r;
	p_rightH->setParent(*this);
}

void Token::assignType(){
	switch(this->val[0]){
		case '`':
			// check if this token is a directive or a call for a macro
			// if directive {
				// type = DIRECTIVE;
				// checkValidDirective
			// } else
				// type = MACRO;
				// checkValidMacro
			break;
		case '$':
			// type = TASK;
			//checkValidTask
			break;
		case '#':
			// type = DELAY;
			// checkValidDelay
			break;
		case '[':
			// type = BIT_WIDTH;
			// checkValidBitWidths
			break;
		case '\'':
			// type = LITERAL;
			// checkValidLiteral
			break;
		default:
			if ('_' == val[0] || isalpha(val[0])){
				/* if (\) Escaped identifiers not supported, ability to use commas makes
					tokenization too hard
					Person who wrote the verilog is trying to be fancy
					checkValidEscaped */
				// Determine if keyword or variable
        if ('_' != val[0]){
          // hardcoded 94. Should be changed to just be the length of keywords[]
          for(int i = 0; i < 94; i++){
            if (strcmp(val, keywords[i])){
              type = KEYWORD;
              break;
            }
          }
        } else
          type = IDENTIFIER;
				// checkValid whichever it is
			} else if (isdigit(val[0])){
				type = LITERAL;
				// checkValidLiteral
			} else{
				// Special exception for directives
        // check if token is an operator
				// raise error
      }
			break;
				
	}
}

int Token::errorCheck(){
	switch(this->type){
		// case for every token type
			// if (!(checkValid for token type))
				// return 1;
			// break;
		default:
			return 0;
			break;
	}
}

// TODO: implement a sort of symbol table

/*bool Token::checkValidDirective(){
	// check against an array with all the directives
}

bool Token::checkValidKeyword(){
	// check against an array with all the keywords
}

bool Token::checkValidBitWidths(){
	
}

bool Token::checkValidOperator(){
	// check against an array with all the expressions/operators
}

// Checks if Integer Literal is formed properly, returns false if not
bool Token::checkValidLiteral(){
	// lead with either number or '.
	// scientific notation allowed
	// if has ', must be followed by b, O, d, or h
	// b can have z or x following the letter
	// bases must have valid characters for their base
	// underscores are allowed for readability
}

bool Token::checkValidTask(){
	
}

bool Token::checkValidDelay(){
	// 
	// can have at most 3 values, seperated by commas
	// can use previously defined variables
}

bool Token::checkValidIdentifier(){
	for (unsigned int i = 0; i < (unsigned)strlen(this->val); i++){
		if (isalnum(this->val[i]) == 0 && '_' != this->val[i]){
			cout << "Variables can only conatin letters, numbers, or underscores.\n" << this;
			return false;
		}
	}
	return true;
} */

Token Token::operator=(Token t){
  Token tok;
  tok.setType(t.getType());
  tok.setLineNo(t.getLineNo());
  tok.setOrigFile(t.getOrigFile());
  tok.setVal(t.getVal());
  tok.setParent(t.getParent());
  tok.setLeft(t.getLeft());
  tok.setRight(t.getRight());

  return tok;
}

std::ostream& operator<<(std::ostream &strm, const Token &t) {
	return strm << "Symbol: " << t.getVal() << " on line " << t.getLineNo() << " in " 
				<< t.getOrigFile() << ".";
}