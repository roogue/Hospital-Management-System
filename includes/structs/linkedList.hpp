#include <iostream>
#include <stdexcept>
#include "structs/linkedList.h"

using namespace List;

template <class T>
Node<T>::Node(T &data)
{
    this->data = data;
    this->next = nullptr;
}

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
            T *dataPtr = &temp->data;
            return dataPtr;
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
            T *dataPtr = &temp->data;
            return dataPtr;
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