#include <stdexcept>
#include <iostream>
#include "structs/linkedList.h"
#include "structs/orderedLinkedList.h"

using namespace List;

template <class T>
void OrderedLinkedList<T>::addNode(T &data)
{
    Node<T> *newData = new Node<T>(data);

    if (this->isEmpty())
    {
        this->first = newData;
        this->size++;

        return;
    }

    if (this->first->data >= data)
    {
        newData->next = this->first;
        this->first = newData;
        this->size++;
        return;
    }

    Node<T> *temp = this->first;
    while (temp->next != nullptr && temp->next->data < data)
    {
        temp = temp->next;
    }

    newData->next = temp->next;
    temp->next = newData;
    this->size++;
    return;
}

template <class T>
void OrderedLinkedList<T>::deleteNode(T &data)
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
        if (head->data > data)
        {
            break;
        }

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

    throw std::out_of_range("Node not found");
}

template <class T>
T *OrderedLinkedList<T>::getData(T &data)
{
    if (this->isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    Node<T> *temp = this->first;
    while (temp != nullptr)
    {
        if (temp->data > data)
        {
            break;
        }

        if (temp->data == data)
        {
            T *dataPtr = &temp->data;
            return dataPtr;
        }
        temp = temp->next;
    }

    throw std::out_of_range("Index out of range");
};