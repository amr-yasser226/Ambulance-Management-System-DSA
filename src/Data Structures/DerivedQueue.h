#ifndef DERIVED_QUEUE_H
#define DERIVED_QUEUE_H

#include "Node.h"
#include <iostream>

template <typename T>
class DerivedQueue
{
private:
    Node<T> *backPtr;
    Node<T> *frontPtr;

public:
    DerivedQueue();
    bool isEmpty() const;
    bool enqueue(const T &newEntry);
    bool dequeue(T &frntEntry);
    bool peek(T &frntEntry) const;
    ~DerivedQueue();
    DerivedQueue(const DerivedQueue<T> &LQ);
};

template <typename T>
DerivedQueue<T>::DerivedQueue() : backPtr(nullptr), frontPtr(nullptr) {}

template <typename T>
bool DerivedQueue<T>::isEmpty() const
{
    return frontPtr == nullptr;
}

template <typename T>
bool DerivedQueue<T>::enqueue(const T &newEntry)
{
    Node<T> *newNodePtr = new Node<T>(newEntry);
    if (isEmpty())
        frontPtr = newNodePtr;
    else
        backPtr->setNext(newNodePtr);
    backPtr = newNodePtr;
    return true;
}

template <typename T>
bool DerivedQueue<T>::dequeue(T &frntEntry)
{
    if (isEmpty())
        return false;
    Node<T> *nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    if (nodeToDeletePtr == backPtr)
        backPtr = nullptr;
    delete nodeToDeletePtr;
    return true;
}

template <typename T>
bool DerivedQueue<T>::peek(T &frntEntry) const
{
    if (isEmpty())
        return false;
    frntEntry = frontPtr->getItem();
    return true;
}

template <typename T>
DerivedQueue<T>::~DerivedQueue()
{
    T temp;
    while (dequeue(temp))
        ;
}

template <typename T>
DerivedQueue<T>::DerivedQueue(const DerivedQueue<T> &LQ) : backPtr(nullptr), frontPtr(nullptr)
{
    Node<T> *NodePtr = LQ.frontPtr;
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());
        NodePtr = NodePtr->getNext();
    }
}

#endif // LINKED_QUEUE_H