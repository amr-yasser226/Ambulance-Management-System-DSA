#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class StackNode
{
private:
    T item;
    StackNode<T> *next;

public:
    StackNode(const T &r_Item, StackNode<T> *nextNodePtr = nullptr)
    {
        item = r_Item;
        next = nextNodePtr;
    }

    void setItem(const T &r_Item)
    {
        item = r_Item;
    }

    void setNext(StackNode<T> *nextNodePtr)
    {
        next = nextNodePtr;
    }

    T getItem() const
    {
        return item;
    }

    StackNode<T> *getNext() const
    {
        return next;
    }
};

template <typename T>
class Stack
{
private:
    StackNode<T> *topPtr;

public:
    Stack() : topPtr(nullptr) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            T temp;
            pop(temp);
        }
    }

    bool isEmpty() const
    {
        return topPtr == nullptr;
    }

    void push(const T &newEntry)
    {
        StackNode<T> *newNode = new StackNode<T>(newEntry, topPtr);
        topPtr = newNode;
    }

    bool pop(T &topEntry)
    {
        if (isEmpty())
            return false;

        StackNode<T> *nodeToDelete = topPtr;
        topEntry = topPtr->getItem();
        topPtr = topPtr->getNext();
        delete nodeToDelete;
        return true;
    }

    bool peek(T &topEntry) const
    {
        if (isEmpty())
            return false;

        topEntry = topPtr->getItem();
        return true;
    }
};

#endif // STACK_H