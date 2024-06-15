#pragma once

#include "structs/node.h"

namespace List
{
    template <class T>
    class Iterator
    {
    public:
        Iterator(Node<T> *startNode);
        bool hasNext();
        T *getData();
        void next();

    private:
        Node<T> *current;
    };

}

#include "structs/iterator.hpp"