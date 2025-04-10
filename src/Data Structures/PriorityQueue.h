#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

template <typename T>
class priNode
{
private:
    T item;
    int priority;
    priNode<T> *next;

public:
    priNode();
    priNode(const T &item, int priority);
    priNode(const T &item, int priority, priNode<T> *nextNodePtr);
    void setItem(const T &item, int priority);
    void setNext(priNode<T> *nextNodePtr);
    T getItem(int &priority) const;
    priNode<T> *getNext() const;
    int getPriority() const;
};

template <typename T>
class PriorityQueue
{
private:
    priNode<T> *head;

public:
    PriorityQueue();
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue<T> &otherQueue);
    bool isEmpty() const;
    void enqueue(const T &item, int priority);
    bool dequeue(T &frontEntry, int &priority);
    bool peek(T &frontEntry, int &priority) const;
    int size() const;
    void display() const;
    void print(std::ostream &os) const;
    priNode<T> *getHead() const;
};

template <typename T>
priNode<T> *PriorityQueue<T>::getHead() const
{
    return head;
}

template <typename T>
priNode<T>::priNode() : next(nullptr), priority(0) {}

template <typename T>
priNode<T>::priNode(const T &item, int priority) : item(item), priority(priority), next(nullptr) {}

template <typename T>
priNode<T>::priNode(const T &item, int priority, priNode<T> *nextNodePtr)
    : item(item), priority(priority), next(nextNodePtr) {}


template <typename T>
void priNode<T>::setItem(const T &item, int priority)
{
    this->item = item;
    this->priority = priority;
}

template <typename T>
void priNode<T>::setNext(priNode<T> *nextNodePtr)
{
    next = nextNodePtr;
}

template <typename T>
T priNode<T>::getItem(int &priority) const
{
    priority = this->priority;
    return item;
}

template <typename T>
priNode<T> *priNode<T>::getNext() const
{
    return next;
}

template <typename T>
int priNode<T>::getPriority() const
{
    return priority;
}

template <typename T>
PriorityQueue<T>::PriorityQueue() : head(nullptr) {}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    T tempItem;
    int tempPriority;
    while (dequeue(tempItem, tempPriority))
        ;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &otherQueue) : head(nullptr)
{
    if (!otherQueue.head)
        return; // If the source queue is empty, nothing to copy.

    priNode<T> *current = otherQueue.head; // Pointer to traverse the source queue.
    while (current)
    {
        int tempPriority = current->getPriority(); // Store the current node's priority.
        enqueue(current->getItem(tempPriority), tempPriority); // Enqueue the item and priority into the new queue.
        current = current->getNext(); // Move to the next node.
    }
}


template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
void PriorityQueue<T>::enqueue(const T &item, int priority)
{
    priNode<T> *newNode = new priNode<T>(item, priority);
    if (isEmpty() || priority > head->getPriority())
    {
        newNode->setNext(head);
        head = newNode;
        return;
    }

    priNode<T> *current = head;
    while (current->getNext() && current->getNext()->getPriority() >= priority)
    {
        current = current->getNext();
    }
    newNode->setNext(current->getNext());
    current->setNext(newNode);
}

template <typename T>
bool PriorityQueue<T>::dequeue(T &frontEntry, int &priority)
{
    if (isEmpty())
        return false;

    priNode<T> *nodeToDelete = head;
    frontEntry = head->getItem(priority);
    head = head->getNext();
    delete nodeToDelete;
    return true;
}

template <typename T>
bool PriorityQueue<T>::peek(T &frontEntry, int &priority) const
{
    if (isEmpty())
        return false;

    frontEntry = head->getItem(priority);
    return true;
}

template <typename T>
int PriorityQueue<T>::size() const
{
    int count = 0;
    priNode<T> *current = head;
    while (current)
    {
        count++;
        current = current->getNext();
    }
    return count;
}

template <typename T>
void PriorityQueue<T>::display() const
{
    priNode<T> *current = head;
    while (current)
    {
        std::cout << "Item: " << current->getItem(current->getPriority()) << ", Priority: " << current->getPriority() << std::endl;
        current = current->getNext();
    }
}

template <typename T>
void PriorityQueue<T>::print(std::ostream &os) const 
{
    priNode<T>* current = head;
    int tempPri;

    if (current != nullptr)
    {
        while (current != nullptr) 
        {
            std::cout << " " << current->getItem(tempPri)->getPID();
            if (current->getNext() != nullptr) { std::cout << ","; }
            
            current = current->getNext();
        }
    }
    else
    {
        std::cout << " 0";
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const PriorityQueue<T> &queue)
{
    queue.print(os);
    return os;
}

#endif // PRIORITY_QUEUE_H
