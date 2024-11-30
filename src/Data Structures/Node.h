#ifndef NODE_H
#define NODE_H

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

#endif