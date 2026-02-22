/***************************************************************
  Student Name: Violet Allmon
  File Name: Customer.hpp
  Project 2

  Customer class definition. This class will be used to create customer 
  objects that will be added to the queue and processed by the tellers. 
  Each customer object will have an arrival time, a start of service time, 
  a departure time, and a pointer to the next customer in the queue.
  ***************************************************************/

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <string>
using namespace std;

class Customer
{
    public:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        float pqTime;
        Customer * nextCust; //pointer to the next customer in the queue
        Customer(float arrivalTime)
        {
            this->arrivalTime = arrivalTime;
            this->startOfServiceTime = 0;
            this->departureTime = 0;
            this->pqTime = 0;
            this->nextCust = nullptr;
        }
        void setStartOfServiceTime(float startOfServiceTime)
        {
            this->startOfServiceTime = startOfServiceTime;
        }
        void setDepartureTime(float departureTime)
        {
            this->departureTime = departureTime;
        }
        void setPQTime(float pqTime)
        {
            this->pqTime = pqTime;
        }
        float getPQTime()
        {
            return pqTime;
        }
};

#endif