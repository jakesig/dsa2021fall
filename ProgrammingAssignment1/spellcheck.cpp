#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "hash.h"

using namespace std;

string getFileName() {
    string fileDir;
    cout << " file name: ";
    getline(cin,fileDir);
    return fileDir;
}

void readDictionary(ifstream& dictFile, hashTable *dict) {
    string read;

    while (getline(dictFile, read)) {
        transform(read.begin(), read.end(), read.begin(), [](char c){ return tolower(c); });
        dict -> insert(read);
    }

    dictFile.close();
}

void spellCheck(ifstream& inFile, ofstream& outFile) {
    string read;

    /** Main loop for reading each line of the input file.
     */

    while (getline(inFile, read)) {
        //cout << "PROCESSED: " << read << "\n";
        transform(read.begin(), read.end(), read.begin(), [](char c){ return tolower(c); });

    }

    inFile.close();
    outFile.close();
}


int main() {
    ifstream dictFile;
    ifstream inFile;
    ofstream outFile;
    clock_t initial;
    clock_t final;
    double time;
    auto *dict = new hashTable(1000);

    cout << "Dictionary";
    dictFile.open(getFileName());
    initial = clock();
    readDictionary(dictFile, dict);
    final = clock();
    time = ((double)(final-initial))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << time << "\n";

    cout << "Input";
    inFile.open(getFileName());
    cout << "Output";
    outFile.open(getFileName());

    spellCheck(inFile, outFile);
}
