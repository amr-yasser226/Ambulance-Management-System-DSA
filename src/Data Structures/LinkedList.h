#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList
{
private:
    Node<T> *head; // Pointer to the head node
    int itemCount; // Tracks the number of items in the list

public:
    LinkedList();
    ~LinkedList();

    bool isEmpty() const;
    int size() const;

    void insertFirst(const T &newEntry);
    void insertLast(const T &newEntry);
    bool deleteNodeByValue(const T &value); // Deletes the first node with the specified value
    bool deleteNodeAtPosition(int position); // Deletes a node at the specified position (0-based index)
    Node<T> *getHead() const;
    T peek() const; // Returns the value at the head of the list
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), itemCount(0) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *nodeToDelete = current;
        current = current->getNext();
        delete nodeToDelete;
    }
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
int LinkedList<T>::size() const
{
    return itemCount;
}

template <typename T>
void LinkedList<T>::insertFirst(const T &newEntry)
{
    Node<T> *newNode = new Node<T>(newEntry, head);
    head = newNode;
    itemCount++;
}

template <typename T>
void LinkedList<T>::insertLast(const T &newEntry)
{
    Node<T> *newNode = new Node<T>(newEntry);
    if (isEmpty())
    {
        head = newNode;
    }
    else
    {
        Node<T> *current = head;
        while (current->getNext() != nullptr)
        {
            current = current->getNext();
        }
        current->setNext(newNode);
    }
    itemCount++;
}

template <typename T>
Node<T> *LinkedList<T>::getHead() const
{
    return head;
}

template <typename T>
bool LinkedList<T>::deleteNodeByValue(const T &value)
{
    if (isEmpty())
        return false;

    Node<T> *current = head;
    Node<T> *previous = nullptr;

    // Search for the node with the given value
    while (current != nullptr && current->getItem() != value)
    {
        previous = current;
        current = current->getNext();
    }

    if (current == nullptr)
        return false; // Value not found

    if (current == head)
    {
        head = head->getNext(); // Update head if the first node is to be deleted
    }
    else
    {
        previous->setNext(current->getNext()); // Bypass the node to delete it
    }

    delete current;
    itemCount--;
    return true;
}

template <typename T>
bool LinkedList<T>::deleteNodeAtPosition(int position)
{
    if (position < 0 || position >= itemCount || isEmpty())
        return false;

    Node<T> *current = head;
    Node<T> *previous = nullptr;

    // Traverse to the desired position
    for (int i = 0; i < position; ++i)
    {
        previous = current;
        current = current->getNext();
    }

    if (current == head)
    {
        head = head->getNext(); // Update head if the first node is to be deleted
    }
    else
    {
        previous->setNext(current->getNext()); // Bypass the node to delete it
    }

    delete current;
    itemCount--;
    return true;
}

template <typename T>
T LinkedList<T>::peek() const
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty. Cannot peek.");
    }
    return head->getItem(); // Return the value of the first node
}


#endif // LINKED_LIST_H
