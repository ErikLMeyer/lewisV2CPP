/******************************************************************************************
Title:       testMod.v                                                                     
Author:      Erik L. Meyer                                                                 
Created on:  August 7, 2021                                                                
Description: An extremely basic Verilog file.                                              
Purpose:     Compiles with the program into a C++ file. This file is used to test the basic
             functionality of the program.                                                 
Usage:       Compile with: ./lewisV2CPP testMod.v testMod.cpp                              
******************************************************************************************/

module testMod; // module declaration
  input i_inA, i_inB;
  input i_clk;
  output o_out;
  wire w_a;

  always @ (posedge i_clk)
  assign w_a = i_inA & i_inB;
  assign o_out = w_a;
endmodule

