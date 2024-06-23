#pragma once

#include "structs/node.h"
#include "structs/iterator.h"

namespace List
{
    /**
     * @brief Template class representing a linked list.
     * @tparam T The type of data stored in the linked list.
     */
    template <class T>
    class LinkedList
    {
    public:
    	/**
         * @brief Constructs an empty linked list.
         */
        LinkedList();
        
        /**
         * @brief Copy constructor.
         * @param other Another LinkedList object to copy from.
         */
        LinkedList(const LinkedList<T> &other);
        
        /**
         * @brief Assignment operator.
         * @param other Another LinkedList object to assign from.
         * @return Reference to this LinkedList object after assignment.
         */
        LinkedList<T> &operator=(const LinkedList<T> &other);
        
        /**
         * @brief Destructor.
         */
        virtual ~LinkedList();
        
        /**
         * @brief Resets the linked list to an empty state.
         */
        void reset();
        
         /**
         * @brief Adds a new node with the given data to the end of the linked list.
         * @param data The data to be added to the linked list.
         */
        void addNode(T &data);
        
        /**
         * @brief Searches nodes in the linked list using a custom comparison function.
         * @tparam K The type of the value to compare against.
         * @param list Another LinkedList object where matching nodes will be added.
         * @param compare A function pointer to compare T and K.
         * @param compareValue The value to compare against K.
         */
        template <class K>
        void searchNodes(LinkedList<T> &list, bool (*compare)(T &a, K b), K compareValue);
        
         /**
         * @brief Searches nodes in the linked list by comparing node data directly.
         * @param list Another LinkedList object where matching nodes will be added.
         * @param compareValue The value to compare against node data.
         */
        void searchNodes(LinkedList<T> &list, T compareValue);
        
        /**
         * @brief Sorts the nodes in the linked list using a custom comparison function. 
         * @param compare A function pointer to a comparison function.
         */
        void sortNodes(bool (*compare)(T &a, T &b));
        
        /**
         * @brief Sorts the nodes in the linked list using the default comparison.
         */
        void sortNodes();
        
        /**
         * @brief Deletes the node at the specified index in the linked list.
         * @param index The index of the node to delete.
         */
        void deleteNode(int index);
        
        /**
         * @brief Deletes nodes in the linked list that match the given data.
         * @param data The data to match and delete.
         */
        void deleteNode(T &data);
        
        /**
         * @brief Checks if the linked list is empty.
         * @return true if the linked list is empty, false otherwise.
         */
        bool isEmpty();
        
        /**
         * @brief Gets a pointer to the data stored at the specified index in the linked list.
         * @param index The index of the data to retrieve.
         * @return Pointer to the data at the specified index, or nullptr if index is out of bounds.
         */
        T *getData(int index);
        
        /**
         * @brief Gets a pointer to the data stored in a node that matches the given data.
         * @param data The data to match.
         * @return Pointer to the matching data, or nullptr if no match is found.
         */
        T *getData(T &data);
        
        /**
         * @brief Gets the number of nodes in the linked list.
         * @return The size of the linked list.
         */
        int getSize();

        /**
         * @brief Returns an iterator for iterating through the linked list.
         * @return An iterator for the linked list.
         */
        Iterator<T> iterate();

    protected:
    	/**
         * @brief Pointer to the first node in the linked list.
         */
        Node<T> *first;
        
        /**
         * @brief The current size of the linked list.
         */
        int size;

        /**
         * @brief Divides a linked list into two halves. 
         * @param head Pointer to the head of the list to divide.
         * @param newHead Reference to a pointer where the new head of the divided list will be stored.
         */
        void divideList(Node<T> *head, Node<T> *&newHead);
        
        /**
         * @brief Merges two sorted linked lists into one sorted linked list using a custom comparison function.
         * @param head Pointer to the head of the first list to merge.
         * @param secondHead Pointer to the head of the second list to merge.
         * @param compare A function pointer to a comparison function.
         * @return Pointer to the head of the merged sorted list.
         */
        Node<T> *mergeList(Node<T> *head, Node<T> *secondHead, bool (*compare)(T &a, T &b));
        
        /**
         * @brief Merges two sorted linked lists into one sorted linked list using the default comparison. 
         * @param head Pointer to the head of the first list to merge.
         * @param secondHead Pointer to the head of the second list to merge.
         * @return Pointer to the head of the merged sorted list.
         */
        Node<T> *mergeList(Node<T> *head, Node<T> *secondHead);
        
        /**
         * @brief Recursively sorts a linked list using a custom comparison function.
         * @param head Reference to a pointer to the head of the list to sort.
         * @param compare A function pointer to a comparison function.
         */
        void recSortList(Node<T> *&head, bool (*compare)(T &a, T &b));
        
        /**
         * @brief Recursively sorts a linked list using the default comparison.
         * @param head Reference to a pointer to the head of the list to sort.
         */
        void recSortList(Node<T> *&head);
    };
}

#include "structs/linkedList.hpp"