#pragma once

#include "structs/node.h"

namespace List
{
    /**
     * @brief Iterator class for a linked list.
     * @tparam T The type of data stored in the linked list nodes.
     */
    template <class T>
    class Iterator
    {
    public:
    	/**
		 *@brief Constructs an iterator starting at the given node.
    	 *@param startNode Pointer to the starting node.
    	 */
        Iterator(Node<T> *startNode);
        
        /** 
         * @return true if there is a next element, false otherwise.
         */
        bool hasNext();
        
        /**
         * @return Pointer to the data of the current node.
         */
        T *getData();
        
        /** 
		 *@brief The `next` method advances the iterator to the next node in the list.
		 */
        void next();

    private:
    	/** 
		 *@brief Keeps track of the iterator's position as it traverses the list.
		 */
        Node<T> *current;
    };

}

#include "structs/iterator.hpp"