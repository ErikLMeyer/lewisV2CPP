/*********************************************************************************************
Title:       VCDDumper.h
Author:      Erik L. Meyer
Created on:  July 14, 2021
Description: Declaration of the VCDDumper class.
Purpose:     Writes a .vcd file during runtime of the translated Verilog object.
Usage:       ./lewisV2CPP -vcd [Verilog files] [output file]
		     Build with: [compiler] [options] lewisV2CPP.cpp [all other files in this folder]
*********************************************************************************************/
class VCDDumper{
	private:
		uint sTime; // Number of time units in the simulation
		vector<SymTable::Symbol> comps; // vetor of all ports and their values at PREVIOUS time step
	public:
		VCDDumper(){}
		~VCDDumper(){}
		
		// Getters
		uint getSTime(){ return sTime; }
		// Get the entire list, comps
		
		// Setters
		void setSTime(uint t){ sTime = t; }
		// Set comps
		
		// Writers
		
		/* Writes the header of the vcd file and puts variables into comps */
		void writeHead();
		
		/* Writes the values of the variables in comps to the vcd file.
		/  Compares values in comps to current values, and if they are different, writes the current 
		/  value and replaces it in comps. Should be called at every time step in simulation. */
		void writeData();
		
}