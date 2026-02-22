/******************************************************************
 Student Name: Violet Allmon
 File Name: FIFOQueue.hpp
    Project 2
 
    FIFOQueue class definition. This class will be used to create a
    first-in-first-out queue of customer objects. The FIFO queue will be
    implemented using a linked list, where each node in the list will
    contain a pointer to a customer object and a pointer to the next
    node in the list. The FIFO queue will be ordered based on the
    arrival time of the customers, with the customer that has the
    earliest arrival time being at the front of the queue. 
 *****************************************************************/
#ifndef FIFOQUEUE_HPP
#define FIFOQUEUE_HPP

#include "Customer.hpp"
    using namespace std;

    class FIFOQ
    {
        private:
            Customer * head; //pointer to the first customer in the queue
            Customer * tail; //pointer to the last customer in the queue
            int size; //number of customers in the queue

        public:
            FIFOQ(); //constructor
            ~FIFOQ(); //destructor
            void enqueue(Customer * newCustomer); //function to add a customer to the queue
            Customer * dequeue(); //function to remove a customer from the queue
            bool isEmpty(); //function to check if the queue is empty
            int getSize(); //function to get the number of customers in the queue
    };

    #endif 