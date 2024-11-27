#ifndef STACK_H
#define STACK_H

// Node class for the Stack
template <typename T>
class StackNode
{
private:
    T item;             // A data item
    StackNode<T> *next; // Pointer to the next node

public:
    // Constructor
    StackNode(const T &r_Item, StackNode<T> *nextNodePtr = nullptr)
    {
        item = r_Item;
        next = nextNodePtr;
    }

    // Setters
    void setItem(const T &r_Item)
    {
        item = r_Item;
    }

    void setNext(StackNode<T> *nextNodePtr)
    {
        next = nextNodePtr;
    }

    // Getters
    T getItem() const
    {
        return item;
    }

    StackNode<T> *getNext() const
    {
        return next;
    }
};

// Stack class
template <typename T>
class Stack
{
private:
    StackNode<T> *topPtr; // Pointer to the top of the stack

public:
    // Constructor
    Stack() : topPtr(nullptr) {}

    // Destructor
    ~Stack()
    {
        while (!isEmpty())
        {
            T temp;
            pop(temp);
        }
    }

    // Check if the stack is empty
    bool isEmpty() const
    {
        return topPtr == nullptr;
    }

    // Push a new item onto the stack
    void push(const T &newEntry)
    {
        StackNode<T> *newNode = new StackNode<T>(newEntry, topPtr);
        topPtr = newNode;
    }

    // Pop the top item off the stack
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

    // Peek at the top item of the stack without removing it
    bool peek(T &topEntry) const
    {
        if (isEmpty())
            return false;

        topEntry = topPtr->getItem();
        return true;
    }
};

#endif // STACK_H