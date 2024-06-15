#pragma once

namespace List
{
    template <class T>
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T &data);
    };
}

#include "structs/node.hpp"