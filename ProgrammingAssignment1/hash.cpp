#include <vector>
#include <string>
#include "hash.h"

hashTable::hashTable(int size) {
    this -> capacity = size;
}

int hashTable::insert(const std::string &key, void *pv) {
    data[hash(key)].key = key;
}

bool hashTable::contains(const std::string &key) {

}

void * hashTable::getPointer(const std::string &key, bool *b) {

}

int hashTable::setPointer(const std::string &key, void *pv) {

}

bool hashTable::remove(const std::string &key) {

}

int hashTable::hash(const std::string &key) {

}

int hashTable::findPos(const std::string &key) {

}

bool hashTable::rehash() {

}

unsigned int hashTable::getPrime(int size) {

}

