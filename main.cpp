#include "MathSim.hpp"
#include <cstdlib>
#include <iostream>

int main()
{
    MathSim sim;
    sim.runSimulation();
    std::cout.flush();
    std::cerr.flush();
    exit(0);  // Force clean exit to avoid destructor issues
}
