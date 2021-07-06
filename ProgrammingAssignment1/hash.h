/** Jacob Sigman
 *  Programming Assignment 1
 *  Professor Sable
 *  hash.h
 *
 *  This code implements a hash table, containing all
 *  the class information and functions to be implemented
 *  in the hash.cpp file.
 */

#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>

class hashTable {

    public:

        /** hashTable(): Initializes hash table.
         *  Uses getPrime to choose a prime number at least as large as
         *  the specified size for the initial size of the hash table.
         *
         *  @param {int} size - The initial size of the hash table.
         */

        hashTable(int size = 0);

        /** insert(): Insert the specified key into the hash table.
         *  If an optional pointer is provided, associate that pointer
         *  with the key.
         *
         *  @param {string} key - The key to be inserted.
         *  @param {void} pv - Optional pointer to associate with key.
         *  @return {int} - 0 on success, 1 if key exists, 2 if rehash fails.
         */

        int insert(const std::string &key, void *pv = nullptr);

        /** contains(): Check if the specified key is in the hash table.
         *
         *  @param {string} key - The key to search for.
         *  @return {bool} - true if key is in hash table, false otherwise.
         */

        bool contains(const std::string &key);

        /** getPointer(): Gets the pointer associated with the specified key.
         *
         *  @param {string} key - Key to get pointer from.
         *  @param {bool} b - Optional bool to be modified, true if key is in hash table, false otherwise.
         *  @return {void *} - Pointer associated with key, nullptr if no such pointer exists.
         */

        void *getPointer(const std::string &key, bool *b = nullptr);

        /** setPointer(): Sets the pointer associated with the specified key.
         *
         *  @param {string} key - Key to associate pointer with.
         *  @param {void *} pv - Pointer to associate key with.
         *  @return {int} - 0 on success, 1 if key does not exist in hash table.
         */

        int setPointer(const std::string &key, void *pv);

        /** remove(): Deletes item with the specified key.
         *
         *  @param {string} key - Key to delete item from.
         *  @return {bool} - true on success, false if key does not exist in hash table.
         */

        bool remove(const std::string &key);

    private:

        /** hashItem subclass
         */

        class hashItem {

            /** Public variables for hashItem:
             *  key - string used as a key.
             *  isOccupied - if false, the hashItem is empty.
             *  isDeleted - if true, this item has been lazily deleted.
             *  pv - a pointer related to the key; nullptr if no key provided.
             */

            public:
                std::string key {""};
                bool isOccupied {false};
                bool isDeleted {false};
                void *pv {nullptr};
                hashItem() = default;

        };

        /** Private variables for hashTable:
         *  capacity - Contains the current capacity of the hash table.
         *  filled - Contains the number of occupied items in the hash table.
         *  data - The actual entries of the hash table.
         */

        int capacity;
        int filled{};
        std::vector<hashItem> data;

        /** hash(): The hash function.
         *
         *  @param {string} key - The key to hash.
         *  @return {int} - The hashed value of the key.
         */

        int hash(const std::string &key);

        /** findPos(): Search for an item with the specified key.
         *
         *  @param {string} key - The key to search for.
         *  @return {int} - Position if found, -1 otherwise.
         */

        int findPos(const std::string &key);

        /** rehash(): Makes the hash table bigger.
         *
         *  @return {bool} - true if success, false otherwise.
         */

        bool rehash();

        /** getPrime(): Return a prime number at least as large as size.
         *  Uses a precomputed sequence of selected prime numbers.
         *
         *  @param {int} size - The size of the hash table.
         *  @return {unsigned int} - A prime number at least as large as size.
         */

        static unsigned int getPrime(int size);
};

#endif //_HASH_H