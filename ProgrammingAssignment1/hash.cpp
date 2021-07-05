#include <vector>
#include <string>
#include "hash.h"

using namespace std;

//Source: https://planetmath.org/goodhashtableprimes
const int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

hashTable::hashTable(int size) {
    this -> capacity = getPrime(size);
    data.resize(capacity);
}

int hashTable::insert(const std::string &key, void *pv) {
    int position = hash(key);

    if (contains(key))
        return 1;

    if (filled * 2 >= capacity)
        if (!rehash())
            return 2;

    while (data[position].isOccupied && !data[position].isDeleted)
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

// Source: https://www.daniweb.com/programming/software-development/threads/231987/string-hash-function

int hashTable::hash(const std::string &key) {
    unsigned hash = 0;

    for (int i = 0; i < key.length(); ++i)
        hash ^= (hash << 5) + (hash >> 2) + key[i];

    return hash % capacity;
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
    if (capacity == getPrime(capacity))
        return false;

    capacity = getPrime(capacity);
    vector<hashItem> oldData = data;
    data.clear();
    data.resize(capacity);
    filled = 0;

    for (hashItem item : oldData) {
        if (item.isOccupied)
            insert(item.key, item.pv);
    }

    return true;
}

unsigned int hashTable::getPrime(int size) {
    for (int i : primes)
        if (i > size * 2)
            return i;

    return primes[25];
}

