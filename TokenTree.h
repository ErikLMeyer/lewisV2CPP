/*********************************************************************************************
Title:       TokenTree.h
Author:      Erik L. Meyer
Created on:  July 13, 2021
Description: Class declaration for the TokenTree object
Purpose:     Arranges Token objects into a tree.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#pragma once
#include "Token.h"
#include <stdlib.h>

namespace TT{
  class TokenTree{	
    private:
      T::Token root, current;
      T::Token *p_root, *p_current;
      TokenTree *p_parent, *p_next, *p_child;
      
    public:
      TokenTree(){
        root = T::Token();
        p_root = &root;
        current = T::Token();
        p_current = &current;
        p_parent = (TokenTree*) malloc(sizeof(TokenTree));
        p_next = (TokenTree*) malloc(sizeof(TokenTree));
        p_child = (TokenTree*) malloc(sizeof(TokenTree));
      }

      ~TokenTree(){
        // free(p_root);
        delete p_root;
        delete p_current;
        delete p_parent;
        delete p_next;
        delete p_child;
      }
      
      // Getters
      T::Token getRoot() const { return root; }
      T::Token getCurrent() const { return current; }
      TokenTree* getParent() const { return p_parent; }
      TokenTree* getChild() const { return p_child; }
      TokenTree* getNext() const { return p_next; }
      
      // Setters
      void setRoot(T::Token r){ *p_root = r; }
      void setRoot(T::Token* r){ p_root = r; }
      void setCurrent(T::Token c){ *p_current = c; }
      void setCurrent(T::Token* c){ p_current = c; }
      void setParent(TokenTree p){ *p_parent = p; }
      void setParent(TokenTree* p){ p_parent = p; }
      void setChild(TokenTree c);
      void setChild(TokenTree* c){ this->setChild(*c); }
      void setNext(TokenTree n);
      void setNext(TokenTree* n){ this->setNext(*n); }
      
      // Does stuff
      void placeToken(T::Token nextToken);
      void removeToken();
      void mergeTokens();
      
      // Error check
      bool isValidStatement();
      
      TokenTree operator=(TokenTree t);
  };
}