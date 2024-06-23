#include <iostream>
#include <stdexcept>
#include "structs/linkedList.h"

using namespace List;

template <class T>
LinkedList<T>::LinkedList()
{
    this->first = nullptr;
    this->size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    this->reset();
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
    : first(nullptr),
      size(0)
{
    if (other.first == nullptr)
    {
        return;
    }

    // Creates a deep copy of the provided linked list.
    Node<T> *currentOther = other.first;
    Node<T> *currentNew = nullptr;

    while (currentOther != nullptr)
    {
        Node<T> *newNode = new Node<T>(currentOther->data);

        if (this->first == nullptr) // If current list has no element yet.
        {
            this->first = newNode;
            currentNew = this->first;
        }
        else // Add the subsequent nodes from other list to current list
        {
            currentNew->next = newNode;
            currentNew = newNode;
        }

        currentOther = currentOther->next;
        this->size++;
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    // Reset the list as if the list is not empty.
    this->reset();

    if (other.first != nullptr)
    {
        Node<T> *currentOther = other.first;
        Node<T> *currentNew = nullptr;

        while (currentOther != nullptr)
        {
            Node<T> *newNode = new Node<T>(currentOther->data);

            if (first == nullptr)
            {
                first = newNode;
                currentNew = first;
            }
            else
            {
                currentNew->next = newNode;
                currentNew = newNode;
            }

            currentOther = currentOther->next;
            size++;
        }
    }

    return *this;
}

template <class T>
void LinkedList<T>::reset()
{
    while (this->first != nullptr)
    {
        Node<T> *temp = this->first;
        this->first = this->first->next;
        delete temp;
    }

    this->size = 0;
}

template <class T>
void LinkedList<T>::addNode(T &data)
{
    Node<T> *newData = new Node<T>(data);

    // If the list is empty, just point LinkedList<T>::first to the node.
    if (this->isEmpty())
    {
        this->first = newData;
        this->size++;
        return;
    }

    // Else iterate through list, then attach the node at the end of the list.
    Node<T> *temp = this->first;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newData;
    this->size++;

    return;
}

template <class T>
template <class K>
void LinkedList<T>::searchNodes(LinkedList<T> &list, bool (*compare)(T &a, K b), K compareValue)
{
    Node<T> *current = this->first;
    while (current != nullptr)
    {
        if (compare(current->data, compareValue))
        {
            list.addNode(current->data);
        }
        current = current->next;
    }
};

template <class T>
void LinkedList<T>::searchNodes(LinkedList<T> &list, T compareValue)
{
    Node<T> *current = this->first;
    while (current != nullptr)
    {
        if (current->data == compareValue)
        {
            list.addNode(current->data);
        }
        current = current->next;
    }
};

template <class T>
void LinkedList<T>::sortNodes(bool (*compare)(T &a, T &b))
{
    this->recSortList(this->first, compare); // call merge sort function
};

template <class T>
void LinkedList<T>::sortNodes()
{
    this->recSortList(this->first); // call merge sort function
};

template <class T>
void LinkedList<T>::deleteNode(int index)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    if (index == 0) // Delete first node
    {
        Node<T> *temp = this->first;
        this->first = this->first->next;
        delete temp;
        this->size--;
        return;
    }

    int currentIndex = 1;
    Node<T> *head = this->first->next;
    Node<T> *trail = this->first;
    while (head != nullptr)
    {
        if (currentIndex == index)
        {
            trail->next = head->next;
            delete head;
            this->size--;
            return;
        }

        trail = head;
        head = head->next;
        currentIndex++;
    }

    throw std::out_of_range("Index out of range");
}

template <class T>
void LinkedList<T>::deleteNode(T &data)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    if (this->first->data == data) // Delete first node if matches
    {
        Node<T> *temp = this->first;
        this->first = this->first->next;
        delete temp;
        this->size--;
        return;
    }

    Node<T> *head = this->first->next;
    Node<T> *trail = this->first;
    while (head != nullptr)
    {
        if (head->data == data)
        {
            trail->next = head->next;
            delete head;
            this->size--;
            return;
        }
        trail = head;
        head = head->next;
    }

    throw std::out_of_range("Index out of range");
}

template <class T>
T *LinkedList<T>::getData(int index)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    int currentIndex = 0;
    Node<T> *temp = this->first;
    while (temp != nullptr) // Traverse through the list, and get the data that matches the index.
    {
        if (currentIndex == index)
        {
            return &temp->data;
        }

        temp = temp->next;
        currentIndex++;
    }

    throw std::out_of_range("Index out of range");
};

template <class T>
T *LinkedList<T>::getData(T &data)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    Node<T> *temp = this->first;
    while (temp != nullptr) // Traverse through the list, and get the data that matches the data.
    {
        if (temp->data == data)
        {
            return &temp->data;
        }
        temp = temp->next;
    }

    throw std::out_of_range("Index out of range");
};

template <class T>
bool LinkedList<T>::isEmpty()
{
    return this->size == 0;
}

template <class T>
int LinkedList<T>::getSize()
{
    return this->size;
}

template <class T>
void LinkedList<T>::divideList(Node<T> *head, Node<T> *&newHead)
{
    Node<T> *current;
    Node<T> *middle;

    if (head == nullptr) // List have no node (cannot divide)
    {
        newHead = nullptr;
    }
    else if (head->next == nullptr) // List only have one node (cannot divide)
    {
        newHead = nullptr;
    }
    else // List has more than two nodes
    {
        // Traverse the list with two pointer,
        // One traverse twice the length than the other to get the middle node in the list.
        current = head->next;
        middle = head;

        if (current != nullptr)
        {
            current = current->next;
        }
        while (current != nullptr)
        {
            middle = middle->next;
            current = current->next;
            if (current != nullptr)
            {
                current = current->next;
            }
        }

        newHead = middle->next;
        middle->next = nullptr;
    }
};

template <class T>
Node<T> *LinkedList<T>::mergeList(Node<T> *head, Node<T> *secondHead, bool (*compare)(T &a, T &b))
{
    Node<T> *lastMerged;
    Node<T> *newHead;

    if (head == nullptr)
    {
        return secondHead;
    }
    else if (secondHead == nullptr)
    {
        return head;
    }
    else
    {
        // Compare the first node of each list
        // to choose the smallest node
        if (compare(head->data, secondHead->data))
        {
            newHead = head;
            head = head->next;
            lastMerged = newHead;
        }
        else
        {
            newHead = secondHead;
            secondHead = secondHead->next;
            lastMerged = newHead;
        }

        while (head != nullptr && secondHead != nullptr)
        {
            // Compare and choose smaller node
            if (compare(head->data, secondHead->data))
            {
                lastMerged->next = head;
                lastMerged = head;
                head = head->next;
            }
            else
            {
                lastMerged->next = secondHead;
                lastMerged = secondHead;
                secondHead = secondHead->next;
            }
        }

        // Let the list slides in if the other list is empty.
        if (head == nullptr)
        {
            lastMerged->next = secondHead;
        }
        else
        {
            lastMerged->next = head;
        }

        return newHead;
    }
}

template <class T>
Node<T> *LinkedList<T>::mergeList(Node<T> *head, Node<T> *secondHead)
{
    Node<T> *lastMerged;
    Node<T> *newHead;

    if (head == nullptr)
    {
        return secondHead;
    }
    else if (secondHead == nullptr)
    {
        return head;
    }
    else
    {
        if (head->data < secondHead->data)
        {
            newHead = head;
            head = head->next;
            lastMerged = newHead;
        }
        else
        {
            newHead = secondHead;
            secondHead = secondHead->next;
            lastMerged = newHead;
        }

        while (head != nullptr && secondHead != nullptr)
        {
            if (head->data < secondHead->data)
            {
                lastMerged->next = head;
                lastMerged = head;
                head = head->next;
            }
            else
            {
                lastMerged->next = secondHead;
                lastMerged = secondHead;
                secondHead = secondHead->next;
            }
        }
    
        if (head == nullptr)
        {
            lastMerged->next = secondHead;
        }
        else
        {
            lastMerged->next = head;
        }

        return newHead;
    }
}

template <class T>
void LinkedList<T>::recSortList(Node<T> *&head, bool (*compare)(T &a, T &b))
{
    Node<T> *otherHead;
    if (head != nullptr)
    {
        if (head->next != nullptr)
        {
            this->divideList(head, otherHead); // Divide list and get two pointers pointing to each of the list
            // Sort recursively of those lists.
            this->recSortList(head, compare);
            this->recSortList(otherHead, compare);
            head = this->mergeList(head, otherHead, compare); // Merge the sorted list together.
        }
    }
}

template <class T>
void LinkedList<T>::recSortList(Node<T> *&head)
{
    Node<T> *otherHead;

    if (head != nullptr)
    {
        if (head->next != nullptr)
        {
            this->divideList(head, otherHead);
            this->recSortList(head);
            this->recSortList(otherHead);
            head = this->mergeList(head, otherHead);
        }
    }
}

template <class T>
Iterator<T> LinkedList<T>::iterate()
{
    return Iterator<T>(this->first);
}