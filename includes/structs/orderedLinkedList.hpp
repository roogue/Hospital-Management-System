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

    Node<T> *first = this->first;
    Node<T> *last = nullptr;
    do
    {
        Node<T> *middle = this->getMiddle(first, last);

        if (middle == nullptr)
        {
            return nullptr;
        }

        if (middle->data == data)
        {
            return &middle->data;
        }

        else if (middle->data < data)
        {
            first = middle->next;
        }
        else
        {
            last = middle;
        }

    } while (last == nullptr || last != first);

    throw std::out_of_range("Index out of range");
};

template <class T>
Node<T> *OrderedLinkedList<T>::getMiddle(Node<T> *first, Node<T> *last)
{
    if (first == nullptr)
    {
        return nullptr;
    }

    Node<T> *slow = first;
    Node<T> *fast = first->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
};