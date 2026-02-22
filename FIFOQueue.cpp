/***************************************************************
  Student Name: Violet Allmon
  File Name: FIFOQueue.cpp
  Project 2

  FIFOQueue class definition. This class will be used to create a 
  first-in-first-out queue of customer objects. The FIFO queue will be 
  implemented using a linked list, where each node in the list will
  contain a pointer to a customer object and a pointer to the next 
  node in the list. The FIFO queue will be ordered based on the
  arrival time of the customers, with the customer that has the
  earliest arrival time being at the front of the queue.
*****************************************************************/
#include "FIFOQueue.hpp"
#include <iostream>
using namespace std;
FIFOQ::FIFOQ()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}
FIFOQ::~FIFOQ()
{
    while (!isEmpty())
    {
        dequeue();
    }
}
void FIFOQ::enqueue(Customer * newCustomer)
{
    if(size >= 200)
    {
        cout << "Queue is full. Cannot add more customers." << endl;
        return;
    }
    if (isEmpty())
    {
        head = newCustomer;
        tail = newCustomer;
    }
    else
    {
        tail->nextCust = newCustomer;
        tail = newCustomer;
    }
    size++;
}
Customer * FIFOQ::dequeue()
{
    if (isEmpty())
    {
        return nullptr;
    }
    else
    {
        Customer * temp = head;
        head = head->nextCust;
        size--;
        return temp;
    }
}
bool FIFOQ::isEmpty()
{
    return size == 0;
}
int FIFOQ::getSize()
{
    return size;
}
