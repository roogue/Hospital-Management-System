#include "structs/node.h"
#include "structs/iterator.h"

template <class T>
Node<T>::Node(T &data)
{
    this->data = data;
    this->next = nullptr;
}
