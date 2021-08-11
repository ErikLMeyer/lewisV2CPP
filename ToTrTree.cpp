/*********************************************************************************************
Title:       ToTrTree.cpp
Author:      Erik L. Meyer
Created on:  August 6, 2021
Description: Implementation of some functions in the ToTrTree class.
Purpose:     Arranges TokenTree objects into a tree.
Usage:       Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
#include <string>
#include <string.h>
#include "TokenTree.h"
#include "ToTrTree.h"

using namespace T;
using namespace TT;
using namespace TTT;
using namespace std;

void ToTrTree::placeTree(int act, TokenTree toAdd){
	if (NULL == p_root){
		*p_root = toAdd;
		p_current = p_root;
		return;
	}
	
	switch(act){
		case 0: // Next line
			p_current->setNext(toAdd);
			p_current = p_current->getNext();
			break;
		case 1: // Statement is within a block
			if (NULL == markerMain)
				markerMain = p_current;
			else{
				markerSub = p_current;
        markerMain = p_current->getParent();
      }
			
			p_current->setChild(toAdd);
			p_current = p_current->getChild();
			break;
		case 2: // block closed, move up marker until more code or until reached main marker
			//if (markerSub == markerMain)
				// error
			p_current = markerSub = markerSub->getParent();
			break;
    case 3: // return to main control flow
      p_current = markerMain;
      markerSub = markerMain = NULL;
      break;
		default:
			// error
			break;
	}
}
