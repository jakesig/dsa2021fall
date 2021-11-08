/** Jacob Sigman
 *  Programming Assignment 2
 *  Professor Sable
 *  heap.cpp
 *
 *  This code implements a binary heap, containing all
 *  the implemented functions from the heap.h file.
 */

#include <string>
#include "heap.h"

/** heap(): Initializes heap, allocating space for the nodes of heap,
 *  and the mapping (hash table) based on the specified capacity.
 *
 *  @param {int} capacity - The initial capacity of the heap.
 */

heap::heap(int capacity):mapping(capacity * 2) {
    data.resize(capacity + 1);
    this -> capacity = capacity;
    filled = 0;
}

/** insert(): Inserts a new node with the specified id, string,
 *  key, and an optional pointer into the binary heap. The key
 *  is used to determine the final position of the new node.
 *
 *  @param {string} id - ID to insert onto heap.
 *  @param {int} key - Key to insert onto heap.
 *  @param {void *} pv - Optional pointer to insert onto heap.
 *  @return {int} - 0 on success, 1 if at capacity, 2 if a node with the given id already exists.
 */

int heap::insert(const std::string &id, int key, void *pv) {

    /** If heap is at capacity, return 1.
     */

    if (filled == capacity)
        return 1;

    /** If a node with the given id already exists, return 2.
     */

    if (mapping.contains(id))
        return 2;

    /** Increment filled, then set the id, key, and optional pointer
     *  respectively.
     */

    data[++filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    /** Insert id and reference to the node into the hash table,
     *  then percolate up.
     */

    mapping.insert(id, &data[filled]);
    percolateUp(filled);

    return 0;
}

/** setKey(): Sets the key of the specified node to the specified value.
 *
 *  @param {string} id - The ID of the node.
 *  @param {int} key - The key to set.
 *  @return {int} - 0 on success, 1 if node with given id does not exist.
 */

int heap::setKey(const std::string &id, int key) {

    /** Get the pointer to change the key of, then use the built-in
     *  boolean function to check if it exists. If it does not exist,
     *  return 1.
     */

    bool b;
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));

    if (!b)
        return 1;

    /** Change the key of the pointer, storing the old key to know which
     *  direction to percolate.
     */

    int old = pn -> key;
    pn -> key = key;

    if (old > key)
        percolateUp(getPos(pn));

    if (old < key)
        percolateDown(getPos(pn));

    return 0;
}

/** deleteMin(): Returns the data associated with the smallest key, and deletes that node from the heap.
 *
 *  @param {string *} pId - If supplied, write to that address the ID of the deleted node.
 *  @param {int *} pKey - If supplied, write to that address the key of the deleted node.
 *  @param {void *} ppData - If supplied, write to that address the associated void pointer.
 *  @return {int} - 0 on success, 1 if the heap is empty.
 */

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {

    /** If the heap is empty, return 1.
     */

    if (filled == 0)
        return 1;

    /** Obtain the minimum node (at position 1), then set the parameters
     *  if they were provided.
     */

    node min = data[1];
    if (pId != nullptr)
        *pId = min.id;
    if (pKey != nullptr)
        *pKey = min.key;
    if (ppData != nullptr)
        *(static_cast<void **> (ppData)) = min.pData;

    /** Remove the minimum node from mapping.
     *  Set the root node to the last leaf, then percolate down.
     */

    mapping.remove(min.id);
    data[1] = data[filled--];
    percolateDown(1);

    return 0;
}

/** remove(): Deletes the node with the specified id from the binary heap.
 *
 *  @param {string} id - The id of the node to be removed.
 *  @param {int *} pKey - If supplied, write to that address the key of the deleted node.
 *  @param {void *} ppData - If supplied, write to that address the associated void pointer.
 *  @return {int} - 0 on success, 1 if the node with the given id does not exist.
 */

int heap::remove(const std::string &id, int *pKey, void *ppData) {

    /** Get the pointer to change the key of, then use the built-in
     *  boolean function to check if it exists. If it does not exist,
     *  return 1.
     */

    bool b;
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));

    if (!b)
        return 1;

    /** Set the parameters if they were provided.
     */

    if (pKey != nullptr)
        *pKey = pn -> key;
    if (ppData != nullptr)
        *(static_cast<void **> (ppData)) = pn -> pData;

    /** Set the node to the last leaf, storing the old value to know which
     *  direction to percolate. Then, remove the key from mapping.
     */

    int old = pn -> key;
    mapping.remove(id);
    *pn = data[filled--];

    if (old > pn -> key){
        percolateUp(getPos(pn));

    if (old < pn -> key)
        percolateDown(getPos(pn));

    return 0;
}

/** percolateUp(): Shift all nodes upwards to ensure the heap is a Min Heap
 *
 *  @param {int} posCur - The current position.
 */

void heap::percolateUp(int posCur) {

    /** While the bottom of the heap has not been reached.
     */

    while (posCur/2 > 0) {

        /** If the parent node is smaller than the child node,
         *  swap the two nodes, then add the swapped node to mapping.
         */

        if (data[posCur].key < data[posCur/2].key) {
            node temp = data[posCur/2];
            data[posCur/2] = data[posCur];
            data[posCur] = temp;
            mapping.setPointer(data[posCur].id, &data[posCur]);
            posCur/=2;
            mapping.setPointer(data[posCur].id, &data[posCur]);
        }

        /** Otherwise, there is no need to continue percolating.
         */

        else
            break;
    }

    /** Set the pointer once more just in case no movement happened.
     */

    mapping.setPointer(data[posCur].id, &data[posCur]);
}

/** percolateDown(): Shift all nodes downwards to ensure the heap is a Min Heap
 *
 *  @param {int} posCur - The current position.
 */

void heap::percolateDown(int posCur) {

    /** Variable declarations, one to keep track of the child node, and one
     *  to keep track of the removed node.
     */

    node hole = data[posCur];

    for(int pos; posCur*2 <= filled; posCur = pos) {
        pos = posCur*2;

        if (pos != filled && (data[pos+1].key < data[pos].key))
            ++pos;

        if (data[pos].key < hole.key) {
            data[posCur] = data[pos];
            mapping.setPointer(data[posCur].id, &data[posCur]);
        }

        else
            break;
    }

    data[posCur] = hole;
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

/** getPos(): Gets the position of a node.
 *
 *  @param pn - Provided pointer to node.
 *  @return {int} - The position of the provided node.
 */

int heap::getPos(node *pn) {
    return pn - &data[0];
}
