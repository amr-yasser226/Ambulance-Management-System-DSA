#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Node.h"
#include <iostream>

// Node class implementations
template <typename T>
Node<T>::Node() : next(nullptr) {}

template <typename T>
Node<T>::Node(const T &r_Item) : item(r_Item), next(nullptr) {}

template <typename T>
Node<T>::Node(const T &r_Item, Node<T> *nextNodePtr) : item(r_Item), next(nextNodePtr) {}

template <typename T>
void Node<T>::setItem(const T &r_Item)
{
    item = r_Item;
}

template <typename T>
void Node<T>::setNext(Node<T> *nextNodePtr)
{
    next = nextNodePtr;
}

template <typename T>
T Node<T>::getItem() const
{
    return item;
}

template <typename T>
Node<T> *Node<T>::getNext() const
{
    return next;
}

// Queue class
template <typename T>
class Queue
{
private:
    Node<T> *backPtr;
    Node<T> *frontPtr;

public:
    Queue();
    bool isEmpty() const;
    bool enqueue(const T &newEntry);
    bool dequeue(T &frntEntry);
    bool peek(T &frntEntry) const;
    ~Queue();
    Queue(const Queue<T> &LQ);
};

// Queue class implementations
template <typename T>
Queue<T>::Queue() : backPtr(nullptr), frontPtr(nullptr) {}

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
Queue<T>::~Queue()
{
    T temp;
    while (dequeue(temp))
        ;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &LQ) : backPtr(nullptr), frontPtr(nullptr)
{
    Node<T> *NodePtr = LQ.frontPtr;
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());
        NodePtr = NodePtr->getNext();
    }
}

#endif // LINKED_QUEUE_H