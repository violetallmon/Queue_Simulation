/***************************************************************
  Student Name: Violet Allmon
  File Name: PriorityQueue.cpp
  Project 2

  PriorityQueue class definition. This class will be used to create 
  a priority queue of customer objects. The priority queue will be 
  implemented using a linked list, where each node in the list will 
  contain a pointer to a customer object and a pointer to the next 
  node in the list. The priority queue will be ordered based on the 
  arrival time of the customers, with the customer that has the 
  earliest arrival time being at the front of the queue.
***************************************************************/

#include "PriorityQueue.hpp"
#include <iostream>
using namespace std;

PQ::PQ()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}
PQ::~PQ()
{
    while (!isEmpty())
    {
        dequeue();
    }
}
void PQ::enqueue(Customer * newCustomer)
{
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
Customer * PQ::dequeue()
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
bool PQ::isEmpty()
{
    return size == 0;
}
int PQ::getSize()
{
    return size;
}
