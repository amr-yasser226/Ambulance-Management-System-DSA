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
    int itemCount; // Keeps track of the number of items in the queue

public:
    DerivedQueue();
    bool isEmpty() const;
    bool enqueue(const T &newEntry);
    bool dequeue(T &frntEntry);
    bool peek(T &frntEntry) const;
    int size() const; // Returns the current size of the queue
    void print(std::ostream &os) const;
    ~DerivedQueue();
    DerivedQueue(const DerivedQueue<T> &LQ);
};

template <typename T>
DerivedQueue<T>::DerivedQueue() : backPtr(nullptr), frontPtr(nullptr), itemCount(0) {}

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
    itemCount++; // Increment the count
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
    if (itemCount > 0) itemCount--; // Decrement the count
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
int DerivedQueue<T>::size() const
{
    return itemCount; // Return the number of items in the queue
}

template <typename T>
DerivedQueue<T>::~DerivedQueue()
{
    T temp;
    while (dequeue(temp))
        ;
}

template <typename T>
DerivedQueue<T>::DerivedQueue(const DerivedQueue<T> &LQ) : backPtr(nullptr), frontPtr(nullptr), itemCount(0)
{
    Node<T> *NodePtr = LQ.frontPtr;
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());
        NodePtr = NodePtr->getNext();
    }
}

template <typename T>
void DerivedQueue<T>::print(std::ostream &os) const 
{
    Node<T>* current = frontPtr;

    if (current != nullptr)
    {
        while (current != nullptr) 
        {
            std::cout << " " << current->getItem()->getPID();
            if (current->getNext() != nullptr) { std::cout << ","; }
            
            current = current->getNext();
        }
    }
    else
    {
        std::cout << " 0";
    }
    std::cout << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DerivedQueue<T> &queue)
{
    queue.print(os);
    return os;
}

#endif // DERIVED_QUEUE_H
