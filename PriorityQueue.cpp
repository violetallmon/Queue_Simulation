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
    size = 0;
    for (int i = 0; i < 200; i++)
    {
        heap[i] = nullptr;
    }
}
PQ::~PQ()
{
    // Don't delete - queues don't own their pointers, simulation does
    for (int i = 1; i <= size; i++)
    {
        heap[i] = nullptr;
    }
}
void PQ::enqueue(Customer * newCustomer)
{
    if (size >= 200) return; // Capacity limit
    size++;
    heap[size] = newCustomer; // 1-based indexing: add at size
    bubbleUp(size);
}
Customer * PQ::dequeue()
{
    if (isEmpty())
    {
        return nullptr;
    }
    else
    {
        Customer * temp = heap[1];  // Remove root
        heap[1] = heap[size];       // Move last element to root
        heap[size] = nullptr;
        size--;
        if (size > 0) {
            bubbleDown(1);
        }
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
void PQ::bubbleUp(int index)
{
    while (index > 1) {
        int parent = index / 2;
        if (!heap[index] || !heap[parent]) {
            break;
        }
        if (heap[index]->getPQTime() < heap[parent]->getPQTime()) {
            Customer* temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}
void PQ::bubbleDown(int index) {
    int smallest = index;
    int left = 2 * index;      // 1-based: left child at 2*i
    int right = 2 * index + 1; // 1-based: right child at 2*i + 1

    if (!heap[index]) {
        return;  // Nothing to bubble down
    }

    if (left <= size && heap[left] && heap[left]->getPQTime() < heap[smallest]->getPQTime()) {
        smallest = left;
    }
    if (right <= size && heap[right] && heap[right]->getPQTime() < heap[smallest]->getPQTime()) {
        smallest = right;
    }
    if (smallest != index) {
        Customer* temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        bubbleDown(smallest);
    }
}
