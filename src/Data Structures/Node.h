#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
private:
    T data;
    Node *next;
public:
    Node(T data) : data(data), next(nullptr) {}
    void setData(T d) { data = d; }
    void setNext(Node *n) { next = n; }
    T getData() { return data; }
    Node *getNext() { return next; }
};

#endif