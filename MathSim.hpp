/***************************************************************
  Student Name: Violet Allmon
  File Name: MathSim.hpp
  Project 2

    MathSim class definition. This class will be used to run the
    simulation of the bank tellers and customers. The MathSim class will
    contain the main simulation loop, as well as functions to calculate
    the results of the simulation and print them to the console.
 ***************************************************************/
#ifndef MathSim_HPP
#define MathSim_HPP
#include "Customer.hpp"
#include "FIFOQueue.hpp"
#include "PriorityQueue.hpp"
#include <iostream>
using namespace std;

class MathSim
{
    private:
        float currentTime; //current time in the simulation
        float percentIdleTime; //percentage of time the tellers are idle
        float avgNumInSystem; //average number of customers in the queue
        float avgTimeInSystem; //average time a customer spends in the system
        float avgNumInQueue; //average number of customers in the queue
        float avgTimeInQueue; //average time a customer spends in the queue
        float rho; //utilization factor of the tellers

    public:
        int lambda; //average number of customers arriving per unit time
        int mu; //average number of customers served per unit time
        int m; //number of tellers
        int numEvents; //number of events to simulate

   
        MathSim(); //constructor
        float factorial(int n); //function to calculate the factorial of a number
        void runSimulation(string filename); //function to run the simulation
        void printResults(); //function to print the results of the simulation
        void calculateResults(); //function to calculate the results of the simulation
        void calculatePercentIdleTime(); //function to calculate the percentage of time the tellers are
        void calculateAvgNumInSystem(); //function to calculate the average number of customers in the system
        void calculateAvgTimeInSystem(); //function to calculate the average time a customer spends in the system
        void calculateAvgNumInQueue(); //function to calculate the average number of customers in the queue
        void calculateAvgTimeInQueue(); //function to calculate the average time a customer spends in the queue
        void calculateUtilFactor(); //function to calculate the utilization factor of the tellers
        float getNextRandomInterval(float avg); //function to get the next random interval for customer arrivals and service times
};

#endif