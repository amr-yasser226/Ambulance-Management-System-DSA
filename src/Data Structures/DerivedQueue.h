#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <iostream>
#include "Node.h"

// DerivedQueue class for integers
class DerivedQueue
{
private:
    Node<int> *backPtr;
    Node<int> *frontPtr;

public:
    DerivedQueue();
    bool isEmpty() const;
    bool enqueue(const int &newEntry);
    bool dequeue(int &frntEntry);
    bool peek(int &frntEntry) const;
    ~DerivedQueue();
    DerivedQueue(const DerivedQueue &LQ);
};

// DerivedQueue class implementations

DerivedQueue::DerivedQueue() : backPtr(nullptr), frontPtr(nullptr) {}

bool DerivedQueue::isEmpty() const
{
    return frontPtr == nullptr;
}

bool DerivedQueue::enqueue(const int &newEntry)
{
    Node<int> *newNodePtr = new Node<int>(newEntry);
    if (isEmpty())
        frontPtr = newNodePtr;
    else
        backPtr->setNext(newNodePtr);
    backPtr = newNodePtr;
    return true;
}

bool DerivedQueue::dequeue(int &frntEntry)
{
    if (isEmpty())
        return false;
    Node<int> *nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    if (nodeToDeletePtr == backPtr)
        backPtr = nullptr;
    delete nodeToDeletePtr;
    return true;
}

bool DerivedQueue::peek(int &frntEntry) const
{
    if (isEmpty())
        return false;
    frntEntry = frontPtr->getItem();
    return true;
}

DerivedQueue::~DerivedQueue()
{
    int temp;
    while (dequeue(temp))
        ;
}

DerivedQueue::DerivedQueue(const DerivedQueue &LQ) : backPtr(nullptr), frontPtr(nullptr)
{
    Node<int> *nodePtr = LQ.frontPtr;
    while (nodePtr)
    {
        enqueue(nodePtr->getItem());
        nodePtr = nodePtr->getNext();
    }
}

#endif // LINKED_QUEUE_H
