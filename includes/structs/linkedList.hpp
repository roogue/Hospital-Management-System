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

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

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

    // If the list is empty
    if (this->isEmpty())
    {
        this->first = newData;
        this->size++;
        return;
    }

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
    this->recSortList(this->first, compare);
};

template <class T>
void LinkedList<T>::sortNodes()
{
    this->recSortList(this->first);
};

template <class T>
void LinkedList<T>::deleteNode(int index)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    if (index == 0)
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

    // Delete first node if matches
    if (this->first->data == data)
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
    while (temp != nullptr)
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
    while (temp != nullptr)
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

    if (head == nullptr) // list have no node (cannot divide)
    {
        newHead = nullptr;
    }
    else if (head->next == nullptr) // list only have one node (cannot divide)
    {
        newHead = nullptr;
    }
    else
    {
        current = head->next;
        middle = head;

        if (current != nullptr) // list has more than two nodes
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
        // Compare the first node
        // Choose the smallest node
        if (compare(head->data, secondHead->data)) // Compare
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
            if (compare(head->data, secondHead->data)) // Compare
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
        // Compare the first node
        // Choose the smallest node
        if (head->data < secondHead->data) // Compare
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
            if (head->data < secondHead->data) // Compare
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
            this->divideList(head, otherHead);

            this->recSortList(head, compare);
            this->recSortList(otherHead, compare);
            head = this->mergeList(head, otherHead, compare);
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