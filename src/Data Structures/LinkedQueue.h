#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

// Node class for LinkedQueue
template <typename T>
class Node
{
private:
    T item;
    Node<T> *next;

public:
    Node();
    Node(const T &r_Item);
    Node(const T &r_Item, Node<T> *nextNodePtr);
    void setItem(const T &r_Item);
    void setNext(Node<T> *nextNodePtr);
    T getItem() const;
    Node<T> *getNext() const;
};

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

// LinkedQueue class
template <typename T>
class LinkedQueue
{
private:
    Node<T> *backPtr;
    Node<T> *frontPtr;

public:
    LinkedQueue();
    bool isEmpty() const;
    bool enqueue(const T &newEntry);
    bool dequeue(T &frntEntry);
    bool peek(T &frntEntry) const;
    ~LinkedQueue();
    LinkedQueue(const LinkedQueue<T> &LQ);
};

// LinkedQueue class implementations
template <typename T>
LinkedQueue<T>::LinkedQueue() : backPtr(nullptr), frontPtr(nullptr) {}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return frontPtr == nullptr;
}

template <typename T>
bool LinkedQueue<T>::enqueue(const T &newEntry)
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
bool LinkedQueue<T>::dequeue(T &frntEntry)
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
bool LinkedQueue<T>::peek(T &frntEntry) const
{
    if (isEmpty())
        return false;
    frntEntry = frontPtr->getItem();
    return true;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    T temp;
    while (dequeue(temp))
        ;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &LQ) : backPtr(nullptr), frontPtr(nullptr)
{
    Node<T> *NodePtr = LQ.frontPtr;
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());
        NodePtr = NodePtr->getNext();
    }
}

#endif
