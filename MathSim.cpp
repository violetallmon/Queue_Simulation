#include "MathSim.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

MathSim::MathSim()
{
    currentTime = 0;
    percentIdleTime = 0;
    avgNumInSystem = 0;
    avgTimeInSystem = 0;
    avgNumInQueue = 0;
    avgTimeInQueue = 0;
    utilFactor = 0;
    lambda = 0;
    mu = 0;
    m = 0;
    numEvents = 0;
}
void MathSim::runSimulation()
{
    try {
        //code to run the simulation will go here
        ifstream inputfile("test1.txt");
        if(!inputfile.is_open())
        {
            cerr << "Error: Unable to open test1.txt" << endl;
            return;
        }
        if (!(inputfile >> lambda >> mu >> m >> numEvents)) {
            cerr << "Error: Failed to read from test1.txt" << endl;
            inputfile.close();
            return;
        }
        inputfile.close();
        
        if (lambda <= 0 || mu <= 0 || m <= 0) {
            cerr << "Error: lambda, mu, m must be positive" << endl;
            return;
        }
        
        calculateResults();
        printResults();
    } catch (const exception& e) {
        cerr << "Exception in runSimulation: " << e.what() << endl;
    }

}
void MathSim::processCustomer(Customer * customer)
{
    //code to process a customer will go here
}
void MathSim::printResults()
{
    //code to print the results of the simulation will go here
    cout << "Results of the simulation:" << endl;
    cout << "Percentage of time the tellers are idle: " << percentIdleTime << endl;
    cout << "Average number of customers in the system: " << avgNumInSystem << endl;
    cout << "Average time a customer spends in the system: " << avgTimeInSystem << endl;
    cout << "Average number of customers in the queue: " << avgNumInQueue << endl;
    cout << "Average time a customer spends in the queue: " << avgTimeInQueue << endl;
    cout << "Utilization factor of the tellers: " << utilFactor << endl;
}
void MathSim::calculateResults()
{
    //code to calculate the results of the simulation will go here
    calculatePercentIdleTime();
    calculateAvgNumInSystem();
    calculateAvgTimeInSystem();
    calculateAvgNumInQueue();
    calculateAvgTimeInQueue();
    calculateUtilFactor();
}
float MathSim::factorial(int n)
{
    if(n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}
void MathSim::calculatePercentIdleTime()
{
    if (lambda <= 0 || mu <= 0) {
        cerr << "Warning: lambda or mu <= 0, skipping calculatePercentIdleTime" << endl;
        percentIdleTime = 0;
        return;
    }
    if (m * mu <= lambda) {
        cerr << "Warning: m*mu <= lambda (system unstable), setting percentIdleTime = 0" << endl;
        percentIdleTime = 0;
        return;
    }
    
    float rho = (float)lambda / mu;  // traffic intensity
    float summation = 0;
    for(int i = m - 1; i >= 0; i--)
    {
        summation += 1.0f/factorial(i) * pow(rho, i);
    }
    if (summation == 0) {
        cerr << "Warning: summation is zero, cannot calculate percentIdleTime" << endl;
        percentIdleTime = 0;
        return;
    }
    float term = (1.0f/factorial(m)) * pow(rho, m) * (m*mu) / (m*mu - lambda);
    percentIdleTime = 1.0f / (summation + term);
}
void MathSim::calculateAvgNumInSystem()
{
    if (lambda <= 0 || mu <= 0 || m <= 0 || percentIdleTime == 0) {
        cerr << "Warning: Invalid parameters for calculateAvgNumInSystem" << endl;
        avgNumInSystem = 0;
        return;
    }
    if (m * mu <= lambda) {
        cerr << "Warning: System unstable (m*mu <= lambda), setting avgNumInSystem = 0" << endl;
        avgNumInSystem = 0;
        return;
    }
    float rho = (float)lambda / mu;
    float numerator = rho * pow(rho, m) * m * mu;
    float denominator = (factorial(m - 1) * pow(m*mu - lambda, 2.0f) * percentIdleTime);
    if (denominator == 0 || !isfinite(denominator)) {
        cerr << "Warning: Invalid denominator in avgNumInSystem" << endl;
        avgNumInSystem = 0;
        return;
    }
    avgNumInSystem = numerator / denominator + rho;
}
void MathSim::calculateAvgTimeInSystem()
{
    if (lambda <= 0) {
        cerr << "Warning: lambda <= 0, cannot calculate avgTimeInSystem" << endl;
        avgTimeInSystem = 0;
        return;
    }
    avgTimeInSystem = avgNumInSystem / lambda; // formula for calculating the average time a customer spends in the system
}
void MathSim::calculateAvgNumInQueue()
{
    float rho = (float)lambda / mu;
    avgNumInQueue = avgNumInSystem - rho;
}
void MathSim::calculateAvgTimeInQueue()
{
    if (lambda <= 0) {
        cerr << "Warning: lambda <= 0, cannot calculate avgTimeInQueue" << endl;
        avgTimeInQueue = 0;
        return;
    }
    avgTimeInQueue = avgNumInQueue / lambda; // formula for calculating the average time a customer spends in the queue
}
void MathSim::calculateUtilFactor()
{
    utilFactor = (float)lambda / (m * mu);
}