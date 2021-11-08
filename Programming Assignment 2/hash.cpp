/** Jacob Sigman
 *  Programming Assignment 2
 *  Professor Sable
 *  hash.cpp
 *
 *  This code implements a hash table, containing all
 *  the implemented functions from the hash.h file.
 */

#include <vector>
#include <string>
#include "hash.h"

using namespace std;

/** An array containing a sequence of prime numbers.
 *  Source: https://planetmath.org/goodhashtableprimes
 */

const int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

/** hashTable(): Initializes hash table.
 *  Uses getPrime to choose a prime number at least as large as
 *  the specified size for the initial size of the hash table.
 *
 *  @param {int} size - The initial size of the hash table.
 */

hashTable::hashTable(int size) {
    this -> capacity = getPrime(size);
    data.resize(capacity);
}

/** insert(): Insert the specified key into the hash table.
 *  If an optional pointer is provided, associate that pointer
 *  with the key.
 *
 *  @param {string} key - The key to be inserted.
 *  @param {void} pv - Optional pointer to associate with key.
 *  @return {int} - 0 on success, 1 if key exists, 2 if rehash fails.
 */

int hashTable::insert(const std::string &key, void *pv) {

    /** If the hash table is at larger than half capacity,
     *  rehash, and if that fails, return 2.
     */

    if (filled * 2 >= capacity)
        if (!rehash())
            return 2;

    /** Determine position to place key.
     *  Then, check if this key is in the hash table.
     */

    int position = hash(key);

    if (contains(key))
        return 1;

    /** Find an open spot using linear probing if necessary.
     *  If the end is reached, set the position to 0 and continue probing.
     */

    while (data[position].isOccupied && !data[position].isDeleted)
        if (++position == capacity)
            position = 0;

    /** Once the position is found, set the key to its provided value,
     *  isOccupied to true, and isDeleted to false.
     *  If optional pointer is provided, set that to its provided value.
     */

    data[position].key = key;
    data[position].isOccupied = true;
    data[position].isDeleted = false;
    data[position].pv = pv;
    filled++;

    return 0;
}

/** contains(): Check if the specified key is in the hash table.
 *
 *  @param {string} key - The key to search for.
 *  @return {bool} - true if key is in hash table, false otherwise.
 */

bool hashTable::contains(const std::string &key) {
    return findPos(key) != -1;
}

/** getPointer(): Gets the pointer associated with the specified key.
 *
 *  @param {string} key - Key to get pointer from.
 *  @param {bool} b - Optional bool to be modified, true if key is in hash table, false otherwise.
 *  @return {void *} - Pointer associated with key, nullptr if no such pointer exists.
 */

void * hashTable::getPointer(const std::string &key, bool *b) {
    int position = findPos(key);

    if (b)
        *b = (position != -1);

    if (position == -1)
        return nullptr;

    return data[position].pv;
}

/** setPointer(): Sets the pointer associated with the specified key.
 *
 *  @param {string} key - Key to associate pointer with.
 *  @param {void *} pv - Pointer to associate key with.
 *  @return {int} - 0 on success, 1 if key does not exist in hash table.
 */

int hashTable::setPointer(const std::string &key, void *pv) {
    int position = findPos(key);

    if (position == -1)
        return 1;

    data[position].pv = pv;

    return 0;
}

/** remove(): Deletes item with the specified key.
 *
 *  @param {string} key - Key to delete item from.
 *  @return {bool} - true on success, false if key does not exist in hash table.
 */

bool hashTable::remove(const std::string &key) {

    /** Determine position to remove key from, return false if
     *  key was not found.
     */

    int position = findPos(key);

    if (position == -1)
        return false;

    /** Set isDeleted to true,
     *  and decrement from filled.
     */

    data[position].isDeleted = true;
    filled--;

    return true;
}

/** hash(): The hash function.
 *  Source: https://www.daniweb.com/programming/software-development/threads/231987/string-hash-function
 *
 *  @param {string} key - The key to hash.
 *  @return {int} - The hashed value of the key.
 */

int hashTable::hash(const std::string &key) {
    unsigned hash = 0;

    for (int i = 0; i < key.length(); ++i)
        hash ^= (hash << 5) + (hash >> 2) + key[i];

    return hash % capacity;
}

/** findPos(): Search for an item with the specified key.
 *
 *  @param {string} key - The key to search for.
 *  @return {int} - Position if found, -1 otherwise.
 */

int hashTable::findPos(const std::string &key) {
    int position = hash(key);

    while (data[position].isOccupied)
        if (data[position].key == key && !data[position].isDeleted)
            return position;
        else
            if (++position == capacity)
                position = 0;

    return -1;
}

/** rehash(): Makes the hash table bigger.
 *
 *  @return {bool} - true if success, false otherwise.
 */

bool hashTable::rehash() {

    /** If the final value of primes has been reached,
     *  don't rehash.
     */

    if (capacity == getPrime(capacity))
        return false;

    /** Get a new capacity, save all the data in a
     *  different vector, then resize the data vector.
     */

    capacity = getPrime(capacity);
    vector<hashItem> oldData = data;
    data.clear();
    data.resize(capacity);
    filled = 0;

    /** Copy over all the old data into the new
     *  resized data vector.
     */

    for (hashItem item : oldData)
        if (item.isOccupied)
            insert(item.key, item.pv);

    return true;
}

/** getPrime(): Return a prime number at least as large as size.
 *  Uses a precomputed sequence of selected prime numbers.
 *
 *  @param {int} size - The size of the hash table.
 *  @return {unsigned int} - A prime number at least as large as size.
 */

unsigned int hashTable::getPrime(int size) {

    /** Parse through array of primes until one is found that is larger
     *  than size. If nothing is found just return the last value in the
     *  primes array.
     */

    for (int i : primes)
        if (i > size)
            return i;

    return primes[25];
}

