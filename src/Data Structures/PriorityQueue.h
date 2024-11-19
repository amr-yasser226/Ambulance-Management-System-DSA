#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Define the priNode class
template <typename T>
class priNode
{
private:
    T item;           // A data item
    int pri;          // Priority of the item
    priNode<T> *next; // Pointer to the next node

public:
    // Constructor
    priNode(const T &r_Item, int PRI)
    {
        setItem(r_Item, PRI);
        next = nullptr;
    }

    // Set the item and its priority
    void setItem(const T &r_Item, int PRI)
    {
        item = r_Item;
        pri = PRI;
    }

    // Set the next node pointer
    void setNext(priNode<T> *nextNodePtr)
    {
        next = nextNodePtr;
    }

    // Get the item and update the priority reference
    T getItem(int &PRI) const
    {
        PRI = pri;
        return item;
    }

    // Get the next node pointer
    priNode<T> *getNext() const
    {
        return next;
    }

    // Get the priority of the node
    int getPri() const
    {
        return pri;
    }
};

// Define the priQueue class, which implements a priority queue using a linked list
template <typename T>
class priQueue
{
private:
    priNode<T> *head; // Pointer to the head of the list

public:
    // Constructor
    priQueue() : head(nullptr) {}

    // Destructor to free memory
    ~priQueue()
    {
        T tmp;
        int p;
        while (dequeue(tmp, p))
            ;
    }

    // Enqueue a new node based on its priority
    void enqueue(const T &data, int priority)
    {
        priNode<T> *newNode = new priNode<T>(data, priority);

        // If the list is empty or the new node has the highest priority
        if (head == nullptr || priority > head->getPri())
        {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        // Traverse to find the correct position for the new node
        priNode<T> *current = head;
        while (current->getNext() && priority <= current->getNext()->getPri())
        {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    // Dequeue the node with the highest priority
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

    // Peek at the node with the highest priority without removing it
    bool peek(T &topEntry, int &pri)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    // Check if the priority queue is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }
};

#endif // PRIORITY_QUEUE_H
