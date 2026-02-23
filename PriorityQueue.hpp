/***************************************************************
  Student Name: Violet Allmon
  File Name: PriorityQueue.hpp
  Project 2

  PriorityQueue class definition. This class will be used to create 
  a priority queue of customer objects. The priority queue will be
    implemented using a linked list, where each node in the list will
    contain a pointer to a customer object and a pointer to the next
    node in the list. The priority queue will be ordered based on the
    arrival time of the customers, with the customer that has the
    earliest arrival time being at the front of the queue.
  ***************************************************************/

#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP
#include "Customer.hpp"
    using namespace std;

    class PQ
    {
        private:
            Customer* heap[201]; //array to store the customers in the priority queue
            int size; //number of customers in the priority queue
            void bubbleUp(int index); //function to maintain the heap property after adding a new customer
            void bubbleDown(int index); //function to maintain the heap property after removing a customer

        public:
            PQ(); //constructor
            ~PQ(); //destructor
            void enqueue(Customer* newCustomer); //function to add a customer to the priority queue
            Customer* dequeue(); //function to remove a customer from the priority queue
            bool isEmpty(); //function to check if the priority queue is empty
            int getSize(); //function to get the number of customers in the priority queue
    };

    #endif