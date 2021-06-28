#include <vector>
#include <string>
#include "hash.h"

using namespace std;

int primes[] = {2, 3, 5, 7};

hashTable::hashTable(int size) {
    this -> capacity = getPrime(size);
    data.resize(capacity);
}

int hashTable::insert(const std::string &key, void *pv) {
    int position = hash(key);

    if (contains(key))
        return 1;

    if (capacity - filled > capacity/2)
        if (!rehash())
            return 2;

    while (data[position].isOccupied)
        if (++position == capacity)
            position = 0;

    data[position].key = key;
    data[position].isOccupied = true;
    data[position].isDeleted = false;
    data[position].pv = pv;
    filled++;

    return 0;
}

bool hashTable::contains(const std::string &key) {
    return findPos(key) != -1;
}

void * hashTable::getPointer(const std::string &key, bool *b) {
    int position = findPos(key);

    if (position == -1)
        return nullptr;

    if (b)
        *b = position != -1;

    return data[position].pv;
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int position = findPos(key);

    if (position == -1)
        return 1;

    data[position].pv = pv;

    return 0;
}

bool hashTable::remove(const std::string &key) {
    int position = findPos(key);

    if (position == -1)
        return false;

    data[position].isOccupied = false;
    data[position].isDeleted = true;
    filled--;

    return true;
}

int hashTable::hash(const std::string &key) {

}

int hashTable::findPos(const std::string &key) {
    int position = hash(key);

    while (data[position].isOccupied)
        if (data[position].key == key)
            return position;
        else
            if (++position == capacity)
                position = 0;

    return -1;
}

bool hashTable::rehash() {

}

unsigned int hashTable::getPrime(int size) {

}

