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

template <typename T>
Node<T>::Node() : item(), next(nullptr)
{
}

template <typename T>
Node<T>::Node(const T &r_Item) : item(r_Item), next(nullptr)
{
}

template <typename T>
Node<T>::Node(const T &r_Item, Node<T> *nextNodePtr) : item(r_Item), next(nextNodePtr)
{
}

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
Node<T>* Node<T>::getNext() const
{
    return next;
}

#endif // NODE_H