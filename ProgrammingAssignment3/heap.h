/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  heap.h
 *
 *  This code implements a binary heap, containing all
 *  the class information and functions to be implemented
 *  in the heap.cpp file.
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <string>
#include <vector>
#include "hash.h"

class heap {

    public:

        /** heap(): Initializes heap, allocating space for the nodes of heap,
         *  and the mapping (hash table) based on the specified capacity.
         *
         *  @param {int} capacity - The initial capacity of the heap.
         */

        heap(int capacity);

        /** insert(): Inserts a new node with the specified id, string,
         *  key, and an optional pointer into the binary heap. The key
         *  is used to determine the final position of the new node.
         *
         *  @param {string} id - ID to insert onto heap.
         *  @param {int} key - Key to insert onto heap.
         *  @param {void *} pv - Optional pointer to insert onto heap.
         *  @return {int} - 0 on success, 1 if at capacity, 2 if a node with the given id already exists.
         */

        int insert(const std::string &id, int key, void *pv = nullptr);

        /** setKey(): Sets the key of the specified node to the specified value.
         *
         *  @param {string} id - The ID of the node.
         *  @param {int} key - The key to set.
         *  @return {int} - 0 on success, 1 if node with given id does not exist.
         */

        int setKey(const std::string &id, int key);

        /** deleteMin(): Returns the data associated with the smallest key, and deletes that node from the heap.
         *
         *  @param {string *} pId - If supplied, write to that address the ID of the deleted node.
         *  @param {int *} pKey - If supplied, write to that address the key of the deleted node.
         *  @param {void *} ppData - If supplied, write to that address the associated void pointer.
         *  @return {int} - 0 on success, 1 if the heap is empty.
         */

        int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

        /** remove(): Deletes the node with the specified id from the binary heap.
         *
         *  @param {string} id - The id of the node to be removed.
         *  @param {int *} pKey - If supplied, write to that address the key of the deleted node.
         *  @param {void *} ppData - If supplied, write to that address the associated void pointer.
         *  @return {int} - 0 on success, 1 if the node with the given id does not exist.
         */

        int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

    private:

        /** node subclass
         */

        class node {

            /** Public variables for hashItem:
             *  id - the ID of the node.
             *  key - int used as a key.
             *  pData - a pointer related to the node; nullptr if no key provided.
             */

            public:
                std::string id;
                int key;
                void *pData;

        };

        /** Private variables for heap:
         *  capacity - Contains the current capacity of the heap.
         *  filled - Contains the number of occupied items in the heap.
         *  data - The actual binary heap.
         *  mapping - maps ids to node pointers.
         */

        int capacity;
        int filled{};
        std::vector<node> data;
        hashTable mapping;

        /** percolateUp(): Shift all nodes upwards to ensure the heap is a Min Heap
         *
         *  @param {int} posCur - The current position.
         */

        void percolateUp(int posCur);

        /** percolateDown(): Shift all nodes downwards to ensure the heap is a Min Heap
         *
         *  @param {int} posCur - The current position.
         */

        void percolateDown(int posCur);

        /** getPos(): Gets the position of a node.
         *
         *  @param pn - Provided pointer to node.
         *  @return {int} - The position of the provided node.
         */

        int getPos(node *pn);

};

#endif //_HEAP_H