/***************************************************************
  Student Name: Violet Allmon
  File Name: main.cpp
  Project 2

  Main function to run the bank teller simulation. This file will create
  an instance of the MathSim class and call the runSimulation function
  to execute the simulation for the provided input files.
 ***************************************************************/
#include "MathSim.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    MathSim sim;
    sim.runSimulation("test1.txt");
    cout.flush();
    cerr.flush();
    sim.runSimulation("test2.txt");
    exit(0);  // Force clean exit to avoid destructor issues
}
