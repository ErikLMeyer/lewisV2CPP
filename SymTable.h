/**********************************************************************************************
Title:       SymTable.h
Author:      Erik L. Meyer
Created on:  July 30, 2021
Description: Declaration of the SymTable object
Purpose:     Stores some symbols that have been turned into Tokens for error checking and other
			 purposes.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
**********************************************************************************************/
#pragma once
#include <vector>
#include <string.h>
#include <string>

namespace ST{
  static struct Symbol{
      std::string name;
      auto value;
    };

  class SymTable{
    private:
      std::vector<Symbol> tab;
    public:
      SymTable(){}
      ~SymTable(){}
      
      // Getters
      std::vector<Symbol> getTable(){ return tab; }
      
      // Setters
      void setTable(std::vector<Symbol> t){ tab = t; }
      
      // Manipulate
      void addSymbol();
      void addSymbol(std::string n);
      void addSymbol(std::string n, auto v);
      void changeValue(std::string n, auto v);
      bool findSymbol(std::string n);
      
  };
}