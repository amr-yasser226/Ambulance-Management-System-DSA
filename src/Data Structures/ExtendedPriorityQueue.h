#ifndef EXTENDED_PRIORITY_QUEUE_H
#define EXTENDED_PRIORITY_QUEUE_H

#include <iostream>

template <typename T>
class extPriNode
{
private:
    T item;
    double priority;
    extPriNode<T> *next;

public:
    extPriNode();
    extPriNode(const T &item, double priority);
    extPriNode(const T &item, double priority, extPriNode<T> *nextNodePtr);
    void setItem(const T &item, double priority);
    void setNext(extPriNode<T> *nextNodePtr);
    T getItem(double &priority) const;
    extPriNode<T> *getNext() const;
    double getPriority() const;
};

template <typename T>
class ExtendedPriorityQueue
{
private:
    extPriNode<T> *head;

public:
    ExtendedPriorityQueue();
    ~ExtendedPriorityQueue();
    ExtendedPriorityQueue(const ExtendedPriorityQueue<T> &otherQueue);
    bool isEmpty() const;
    void enqueue(const T &item, double priority);
    bool dequeue(T &frontEntry, double &priority);
    bool peek(T &frontEntry, double &priority) const;
    int size() const;
    void display() const; // this one is just for debugging mostly
    extPriNode<T> *getHead() const;
    void print(std::ostream &os) const; // operator overloadding function to print the *OUT or *BACK
};

template <typename T>
extPriNode<T> *ExtendedPriorityQueue<T>::getHead() const
{
    return head;
}

template <typename T>
extPriNode<T>::extPriNode() : next(nullptr), priority(0.0) {}

template <typename T>
extPriNode<T>::extPriNode(const T &item, double priority) : item(item), priority(priority), next(nullptr) {}

template <typename T>
extPriNode<T>::extPriNode(const T &item, double priority, extPriNode<T> *nextNodePtr)
    : item(item), priority(priority), next(nextNodePtr) {}


template <typename T>
void extPriNode<T>::setItem(const T &item, double priority)
{
    this->item = item;
    this->priority = priority;
}

template <typename T>
void extPriNode<T>::setNext(extPriNode<T> *nextNodePtr)
{
    next = nextNodePtr;
}

template <typename T>
T extPriNode<T>::getItem(double &priority) const
{
    priority = this->priority;
    return item;
}

template <typename T>
extPriNode<T> *extPriNode<T>::getNext() const
{
    return next;
}

template <typename T>
double extPriNode<T>::getPriority() const
{
    return priority;
}

template <typename T>
ExtendedPriorityQueue<T>::ExtendedPriorityQueue() : head(nullptr) {}

template <typename T>
ExtendedPriorityQueue<T>::~ExtendedPriorityQueue()
{
    T tempItem;
    double tempPriority;
    while (dequeue(tempItem, tempPriority))
        ;
}

template <typename T>
ExtendedPriorityQueue<T>::ExtendedPriorityQueue(const ExtendedPriorityQueue<T> &otherQueue) : head(nullptr)
{
    if (!otherQueue.head)
        return; // If the source queue is empty, nothing to copy.

    extPriNode<T> *current = otherQueue.head; // Pointer to traverse the source queue.
    while (current)
    {
        double tempPriority = current->getPriority(); // Store the current node's priority.
        enqueue(current->getItem(tempPriority), tempPriority); // Enqueue the item and priority into the new queue.
        current = current->getNext(); // Move to the next node.
    }
}


template <typename T>
bool ExtendedPriorityQueue<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
void ExtendedPriorityQueue<T>::enqueue(const T &item, double priority)
{
    extPriNode<T> *newNode = new extPriNode<T>(item, priority);

    if (isEmpty() || priority < head->getPriority())
    {
        newNode->setNext(head);
        head = newNode;
        return;
    }

    extPriNode<T> *current = head;
    while (current->getNext() && current->getNext()->getPriority() <= priority)
    {
        current = current->getNext();
    }

    newNode->setNext(current->getNext());
    current->setNext(newNode);
}

template <typename T>
bool ExtendedPriorityQueue<T>::dequeue(T &frontEntry, double &priority)
{
    if (isEmpty())
        return false;

    extPriNode<T> *nodeToDelete = head;
    frontEntry = head->getItem(priority);
    head = head->getNext();
    delete nodeToDelete;
    return true;
}

template <typename T>
bool ExtendedPriorityQueue<T>::peek(T &frontEntry, double &priority) const
{
    if (isEmpty())
        return false;

    frontEntry = head->getItem(priority);
    return true;
}

template <typename T>
int ExtendedPriorityQueue<T>::size() const
{
    int count = 0;
    extPriNode<T> *current = head;
    while (current)
    {
        count++;
        current = current->getNext();
    }
    return count;
}

template <typename T>
void ExtendedPriorityQueue<T>::display() const
{
    extPriNode<T> *current = head;
    while (current)
    {
        double priority = current->getPriority();
        std::cout << "Item: " << current->getItem(priority)
                  << ", Priority: " << priority << std::endl;
        current = current->getNext();
    }
}

template <typename T>
void ExtendedPriorityQueue<T>::print(std::ostream &os) const
{
    extPriNode<T> *current = head;
    // os << size() << " ➜ Out cars: ";
    double priority;
    while (current)
    {
        T item = current->getItem(priority);
        os << "S" << item->getUniqueID()
           << "_H" << item->getCurrentPatient()->getNearestHospitalID()
           << "_P" << item->getCurrentPatient()->getPID();

        if (current->getNext() != nullptr) { os << ", "; }
        current = current->getNext();
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ExtendedPriorityQueue<T> &queue)
{
    queue.print(os);
    return os;
}

#endif // EXTENDED_PRIORITY_QUEUE_H
