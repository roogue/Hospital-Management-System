#include "structs/iterator.h"

using namespace List;

template <class T>
Iterator<T>::Iterator(Node<T> *startNode) : current(startNode){};

template <class T>
bool Iterator<T>::hasNext()
{
    return this->current->next != nullptr;
}

template <class T>
T *Iterator<T>::getData()
{
    if (this->current == nullptr)
    {
        return nullptr;
    }
    return &this->current->data;
}

template <class T>
void Iterator<T>::next()
{
    this->current = this->current->next;
}