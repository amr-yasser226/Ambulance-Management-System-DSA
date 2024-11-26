#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

template <typename T>
class priNode
{
private:
    T item;
    int pri;
    priNode<T> *next;
public:
    priNode(const T &r_Item, int PRI)
    {
        setItem(r_Item, PRI);
        next = nullptr;
    }

    void setItem(const T &r_Item, int PRI)
    {
        item = r_Item;
        pri = PRI;
    }

    void setNext(priNode<T> *nextNodePtr)
    {
        next = nextNodePtr;
    }

    T getItem(int &PRI) const
    {
        PRI = pri;
        return item;
    }

    priNode<T> *getNext() const
    {
        return next;
    }

    int getPri() const
    {
        return pri;
    }

    void display() const
    {
        std::cout << "Data: " << item << " | Priority: " << pri << std::endl;
    }
};

template <typename T>
class priQueue
{
private:
    priNode<T> *head;
public:
    priQueue() : head(nullptr) {}

    ~priQueue()
    {
        T tmp;
        int p;
        while (dequeue(tmp, p))
            ;
    }

    priNode<T>* getHead() const
    {
        return head;
    }

    void enqueue(const T &data, int priority)
    {
        priNode<T> *newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri())
        {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T> *current = head;
        while (current->getNext() && priority <= current->getNext()->getPri())
        {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T &topEntry, int &pri)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T> *temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T &topEntry, int &pri)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void display() const
    {
        priNode<T> *current = head;
        while (current != nullptr)
        {
            current->display();
            current = current->getNext();
        }
    }

    int size() const
    {
        int count = 0;
        priNode<T> *current = head;
        while (current != nullptr)
        {
            count++;
            current = current->getNext();
        }
        return count;
    }
};

#endif // PRIORITY_QUEUE_H