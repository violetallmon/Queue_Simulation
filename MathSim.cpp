/**********************************************
  Student Name: Violet Allmon
  File Name: MathSim.cpp
  Project 2

  MathSim class implementation. This class will be used to run the
  simulation of the bank tellers and customers. The MathSim class will
  contain the main simulation loop, as well as functions to calculate
  the results of the simulation and print them to the console.
***************************************************************/
#include "MathSim.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

MathSim::MathSim()
{
    currentTime = 0;
    percentIdleTime = 0;
    avgNumInSystem = 0;
    avgTimeInSystem = 0;
    avgNumInQueue = 0;
    avgTimeInQueue = 0;
    rho = 0;
    lambda = 0;
    mu = 0;
    m = 0;
    numEvents = 0;
}
void MathSim::runSimulation(string filename)
{
    try {
        // Read input file
        ifstream inputfile(filename);
        if(!inputfile.is_open())
        {
            cerr << "Error: Unable to open " << filename << endl;
            return;
        }
        if (!(inputfile >> lambda >> mu >> m >> numEvents)) {
            cerr << "Error: Failed to read from " << filename << endl;
            inputfile.close();
            return;
        }
        inputfile.close();
        
        if (lambda <= 0 || mu <= 0 || m <= 0) {
            cerr << "Error: lambda, mu, m must be positive" << endl;
            return;
        }

        PQ eventQueue;
        FIFOQ waitQueue;
        vector<Customer*> allCustomers;  // Track all customers for cleanup

        currentTime = 0;
        int busyTellers = 0;
        int customersWhoWaited = 0;
        float totalWaitTime = 0, totalServiceTime = 0, totalSystemTime = 0;
        int customersProcessed = 0;

        // Schedule first arrival
        float nextArrivalTime = getNextRandomInterval(1.0f / lambda);
        Customer* firstEvent = new Customer(nextArrivalTime, "ARRIVAL");
        firstEvent->setPQTime(nextArrivalTime);
        allCustomers.push_back(firstEvent);
        eventQueue.enqueue(firstEvent);
        
        // Main simulation loop
        while (customersProcessed < numEvents && !eventQueue.isEmpty()) {
            Customer* event = eventQueue.dequeue();
            if (!event) break;
            
            currentTime = event->getPQTime();
            
            if (event->eventType == "ARRIVAL") {
                if (busyTellers < m) {
                    // Teller available
                    busyTellers++;
                    float serviceTime = getNextRandomInterval(1.0f / mu);
                    totalServiceTime += serviceTime;
                    event->setStartOfServiceTime(currentTime);
                    event->setDepartureTime(currentTime + serviceTime);
                    event->setPQTime(currentTime + serviceTime);
                    event->eventType = "DEPARTURE";
                    eventQueue.enqueue(event);
                } else {
                    // All tellers busy
                    waitQueue.enqueue(event);
                    customersWhoWaited++;
                }
                
                // Schedule next arrival
                float nextArrival = getNextRandomInterval(1.0f / lambda);
                Customer* nextEvent = new Customer(currentTime + nextArrival, "ARRIVAL");
                nextEvent->setPQTime(currentTime + nextArrival);
                allCustomers.push_back(nextEvent);
                eventQueue.enqueue(nextEvent);
            } else if (event->eventType == "DEPARTURE") {
                customersProcessed++;
                totalSystemTime += (currentTime - event->arrivalTime);
                busyTellers--;
                
                if (!waitQueue.isEmpty()) {
                    // Serve waiting customer
                    Customer* waitingCustomer = waitQueue.dequeue();
                    float waitTime = currentTime - waitingCustomer->arrivalTime;
                    totalWaitTime += waitTime;
                    
                    busyTellers++;
                    float serviceTime = getNextRandomInterval(1.0f / mu);
                    totalServiceTime += serviceTime;
                    waitingCustomer->setStartOfServiceTime(currentTime);
                    waitingCustomer->setDepartureTime(currentTime + serviceTime);
                    waitingCustomer->setPQTime(currentTime + serviceTime);
                    waitingCustomer->eventType = "DEPARTURE";
                    eventQueue.enqueue(waitingCustomer);
                }
            }
        }

        // Calculate results
        calculateResults();
        printResults();
        
        cout << "\nSimulation Statistics:" << endl;
        cout << "Customers processed: " << customersProcessed << endl;
        cout << "Customers who waited: " << customersWhoWaited << endl;
        if (customersProcessed > 0) {
            cout << "Average service time: " << (float)(totalServiceTime / customersProcessed) << endl;
            cout << "Average time in system: " << (float)(totalSystemTime / customersProcessed) << endl;
        }
        if (customersWhoWaited > 0) {
            cout << "Average wait time: " << (float)(totalWaitTime / customersWhoWaited) << endl;
        } else {
            cout << "Average wait time: 0 (no customers waited)" << endl;
        }
        cout << endl << endl;
        
        // Cleanup - delete all created customers
        for (Customer* c : allCustomers) {
            delete c;
        }
        allCustomers.clear();
        
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
    cout << "Utilization factor of the tellers: " << rho << endl;
}
void MathSim::calculateResults()
{
    //code to calculate the results of the simulation will go here
    calculateUtilFactor();
    calculatePercentIdleTime();
    calculateAvgNumInSystem();
    calculateAvgTimeInSystem();
    calculateAvgNumInQueue();
    calculateAvgTimeInQueue();
    
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
    
    float summation = 0;
    for(int i = m - 1; i >= 0; i--)
    {
        summation += 1.0f/factorial(i) * pow((float)lambda/mu, i);
    }
    float term = (1.0f/factorial(m)) * pow((float)lambda/mu, m) * ((float)(m*mu) / (m*mu - lambda));
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
    
    float numerator = (float)(lambda * mu * pow((float)lambda/mu, m) * percentIdleTime);
    float denominator = (float)(factorial(m - 1) * pow((float)m*mu - lambda, 2.0f));
    if (denominator == 0 || !isfinite(denominator)) {
        cerr << "Warning: Invalid denominator in avgNumInSystem" << endl;
        avgNumInSystem = 0;
        return;
    }
    avgNumInSystem = (numerator / denominator) + (float)lambda / mu; // formula for calculating the average number of customers in the system
}
void MathSim::calculateAvgTimeInSystem()
{
    if (lambda <= 0) {
        cerr << "Warning: lambda <= 0, cannot calculate avgTimeInSystem" << endl;
        avgTimeInSystem = 0;
        return;
    }
    avgTimeInSystem = (float)avgNumInSystem / lambda; // formula for calculating the average time a customer spends in the system
}
void MathSim::calculateAvgNumInQueue()
{
    avgNumInQueue = (float)(avgNumInSystem - (float)lambda / mu); // formula for calculating the average number of customers in the queue
}
void MathSim::calculateAvgTimeInQueue()
{
    if (lambda <= 0) {
        cerr << "Warning: lambda <= 0, cannot calculate avgTimeInQueue" << endl;
        avgTimeInQueue = 0;
        return;
    }
    avgTimeInQueue = (float)avgNumInQueue / lambda; // formula for calculating the average time a customer spends in the queue
}
void MathSim::calculateUtilFactor()
{
    rho = (float)lambda / (m * mu);
}
float MathSim::getNextRandomInterval(float avg) {
    float f = (float)rand() / RAND_MAX;
    while (f == 0) f = (float)rand() / RAND_MAX; // Avoid ln(0)
    return -avg * log(f);
}