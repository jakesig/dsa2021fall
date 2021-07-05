#include <string>
#include <vector>
#include "heap.h"

heap::heap(int capacity):mapping(capacity*2) {
    data.resize(capacity+1);
    this -> capacity = capacity;
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (filled == capacity)
        return 1;

    if (mapping.contains(id))
        return 2;

    data[++filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    mapping.insert(id, &data[filled]);

    return 0;
}

int heap::setKey(const std::string &id, int key) {

}

int heap::remove(const std::string &id, int *pKey, void *ppData) {

}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {

}

void heap::percolateUp(int posCur) {

}

void heap::percolateDown(int posCur) {

}

int heap::getPos(node *pn) {
    return pn - &data[0];
}