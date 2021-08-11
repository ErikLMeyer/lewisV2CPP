/*********************************************************************************************
Title:       TokenTree.cpp
Author:      Erik L. Meyer
Created on:  July 15, 2021
Description: Implementations of some of the functions of the TokenTree class.
Purpose:     Arranges Token objects into a tree.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#include <stdio.h>
#include "TokenTree.h"
#include "Token.h"

using namespace T;
using namespace TT;
using namespace std;

void TokenTree::setChild(TokenTree c){
	*p_child = c;
	p_child->setParent(*this);
}

void TokenTree::setNext(TokenTree n){
	*p_next = n;
	p_next->setParent(*this);
}

void TokenTree::placeToken(Token nextToken){
	switch (nextToken.getType()){
		case DIRECTIVE:
			if (NULL == p_root){
				*p_root = nextToken;
				p_current = &root;
			} else{
				if (DIRECTIVE == current.getType()){
					// raise error, can't have consecutive directives on same line
				} else{
					p_current->setLeft(nextToken);
					p_current = current.getLeft();
				}
			}
			break;
		case KEYWORD:
			if (NULL == p_root){
				*p_root = nextToken;
				current = root;
			} else{
				if (KEYWORD == current.getType()){
					if (false){
					// If the line has too many consecutive keywords, raise error
					} else {
						p_current->setLeft(nextToken);
						p_current = current.getLeft();
					}
				}
			}
			break;
		case BIT_WIDTH:
			// figure out how these work better
			break;
		case OPERATOR:
			if (NULL == p_root){
				// error
			} else{
				p_current = p_root;
				while (NULL != current.getRight()){
					p_current = current.getRight();
				}
				p_current->setRight(nextToken);
				p_current = current.getRight();
			}
			break;
		case LITERAL:
			if (NULL == p_root){
				// error
			} else{
				p_current->setLeft(nextToken);
				p_current = current.getLeft();
			}
			break;
		case TASK:
			if (NULL == p_root){
				*p_root = nextToken;
				p_current = p_root;
			} else{
				// error
			}
			break;
		case DELAY:
			if (NULL == p_root){
				*p_root = nextToken;
				current = root;
			} else{
				p_current->setLeft(nextToken);
				p_current = current.getLeft();
			}
			break;
		case IDENTIFIER:
			if (NULL == p_root){
				*p_root = nextToken;
				p_current = p_root;
			} else{
				p_current->setLeft(nextToken);
				p_current = current.getLeft();
			}
			break;
		case MACRO:
			if (NULL == p_root){
				*p_root = nextToken;
				current = root;
			} else{
				p_current->setLeft(nextToken);
				p_current = current.getLeft();
			}
			break;
		default:
			// raise error
			break;
	}
}

/* bool TokenTree::isValidStatement(){
	// If bit width or operator is root, error's probably already been raised
	
} */

TokenTree TokenTree::operator=(TokenTree t){
  TokenTree tree;

  tree.setRoot(t.getRoot());
  tree.setCurrent(t.getCurrent());
  tree.setParent(t.getParent());
  tree.setNext(t.getNext());
  tree.setChild(t.getChild());

  return tree;
}
