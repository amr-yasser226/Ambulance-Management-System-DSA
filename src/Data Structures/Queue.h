#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Node.h"
#include <iostream>

template <typename T>
class Queue
{
private:
    Node<T> *backPtr;
    Node<T> *frontPtr;
    int itemCount; // Keeps track of the number of items in the queue

public:
    Queue();
    bool isEmpty() const;
    bool enqueue(const T &newEntry);
    bool dequeue(T &frntEntry);
    bool peek(T &frntEntry) const;
    int size() const; // Returns the current size of the queue
    ~Queue();
    Queue(const Queue<T> &LQ);
};

template <typename T>
Queue<T>::Queue() : backPtr(nullptr), frontPtr(nullptr), itemCount(0) {}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return frontPtr == nullptr;
}

template <typename T>
bool Queue<T>::enqueue(const T &newEntry)
{
    Node<T> *newNodePtr = new Node<T>(newEntry);
    if (isEmpty())
        frontPtr = newNodePtr;
    else
        backPtr->setNext(newNodePtr);
    backPtr = newNodePtr;
    itemCount++; // Increment the count
    return true;
}

template <typename T>
bool Queue<T>::dequeue(T &frntEntry)
{
    if (isEmpty())
        return false;
    Node<T> *nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    if (nodeToDeletePtr == backPtr)
        backPtr = nullptr;
    delete nodeToDeletePtr;
    if (itemCount > 0) itemCount--; // Decrement the count
    return true;
}

template <typename T>
bool Queue<T>::peek(T &frntEntry) const
{
    if (isEmpty())
        return false;
    frntEntry = frontPtr->getItem();
    return true;
}

template <typename T>
int Queue<T>::size() const
{
    return itemCount; // Return the number of items in the queue
}

template <typename T>
Queue<T>::~Queue()
{
    T temp;
    while (dequeue(temp))
        ;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &LQ) : backPtr(nullptr), frontPtr(nullptr), itemCount(0)
{
    Node<T> *NodePtr = LQ.frontPtr;
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());
        NodePtr = NodePtr->getNext();
    }
}

#endif // QUEUE_H
