#pragma once

namespace List
{
    /**
     * @brief Node class for a linked list.
     * @tparam T The type of data stored in the node.
     */
    template <class T>
    class Node
    {
    public:
        /**
         * @brief The data stored in the node.
         */
        T data;

        /**
         * @brief Pointer to the next node in the list.
         */
        Node *next;

        /**
         * @brief Constructs a node with the given data.
         * @param data The data to be stored in the node.
         */
        Node(T &data);
    };
}

#include "structs/node.hpp"