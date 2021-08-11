/*********************************************************************************************
Title:       ToTrTree.h
Author:      Erik L. Meyer
Created on:  July 13, 2021
Description: Declaration of the ToTrTree class.
Purpose:     Arranges TokenTree objects into a tree.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#pragma once
#include <vector>
#include <string.h>
#include <string>
#include "TokenTree.h"
// #include "SymTable.h"

namespace TTT{
  class ToTrTree{
    private:
      TT::TokenTree *p_root, *p_current;
      TT::TokenTree *markerMain, *markerSub;
      std::string module;
      std::vector<ToTrTree> submodules;
      
    public:
      ToTrTree(){
        p_root = (TT::TokenTree*) malloc(sizeof(TT::TokenTree));
        p_current = (TT::TokenTree*) malloc(sizeof(TT::TokenTree));
        markerMain = (TT::TokenTree*) malloc(sizeof(TT::TokenTree));
        markerSub = (TT::TokenTree*) malloc(sizeof(TT::TokenTree));
      }
      ~ToTrTree(){}
      
      // Getters
      TT::TokenTree* getRoot(){ return p_root; }
      TT::TokenTree* getCurrent(){ return p_current; }
      std::string getName(){ return module; }
      std::vector<ToTrTree> getSubModules(){ return submodules; }
      
      // Setters
      void setRoot(TT::TokenTree* r){ p_root = r; }
      void setRoot(TT::TokenTree r){ *p_root = r; }
      void setCurrent(TT::TokenTree* c){ p_current = c; }
      void setCurrent(TT::TokenTree c){ *p_current = c; }
      void setName(std::string m){ module = m; }
      void setSubmodules(std::vector<ToTrTree> sm){ submodules = sm; }
      
      // Actions
      void placeTree(int act, TT::TokenTree toAdd);
      void addSubmodule();
      
      // Error checks
      bool isUnused();
      bool isNeverDeclared();
      bool isOutOfScope();
    
  };
}