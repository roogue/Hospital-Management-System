#pragma once

#include "structs/linkedList.h"

namespace List
{
    /**
     * @brief Template class representing an ordered linked list.
     * Inherits functionality from LinkedList<T>.
     * @tparam T The type of data stored in the ordered linked list.
     */
    template <class T>
    class OrderedLinkedList : public LinkedList<T>
    {
    public:
        /**
         * @brief Adds a node with the given data to the ordered linked list in sorted order.
         * @param data The data to be added to the ordered linked list.
         */
        void addNode(T &data);

        /**
         * @brief Deletes the node containing the given data from the ordered linked list.
         * @param data The data to be deleted from the ordered linked list.
         */
        void deleteNode(T &data);

        /**
         * @brief Retrieves the data stored in the node that matches the given data.
         * Uses the base class method LinkedList<T>::getData.
         *
         * @param data The data to match against nodes in the ordered linked list.
         * @return Pointer to the matching data, or nullptr if no match is found.
         */
        using LinkedList<T>::getData;

        /**
         * @brief Retrieves the data stored in the node that matches the given data.
         * @param data The data to match against nodes in the ordered linked list.
         * @return Pointer to the matching data, or nullptr if no match is found.
         */
        T *getData(T &data);

    protected:
        /**
         * @brief Inherited from LinkedList<T>.
         */
        using LinkedList<T>::first;

        /**
         * @brief Inherited from LinkedList<T>.
         */
        using LinkedList<T>::size;

        /**
         * @brief Get the middle node of the list.
         * @param first The entry of the list.
         * @param last The last node to traverse in the list.
         * @return The middle node.
         */
        Node<T> *getMiddle(Node<T> *first, Node<T> *last);
    };
}

#include "orderedLinkedList.hpp"