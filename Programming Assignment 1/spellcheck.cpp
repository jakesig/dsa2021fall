/** Jacob Sigman
 *  Programming Assignment 1
 *  Professor Sable
 *  spellcheck.cpp
 *
 *  This code implements spellchecks a document, outputting
 *  to an output file, prompting for a dictionary, input file,
 *  and output file.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "hash.h"

using namespace std;

string getFileName();
vector<string> split(string str, string delim);
void readDictionary(ifstream& dictFile, hashTable *dict);
void spellCheck(ifstream& inFile, ofstream& outFile, hashTable *dict);

/** getFileName(): Returns file name that the user inputs.
 *
 *  @return {string} - The name of the file that the user inputted.
 */

string getFileName() {
    string fileDir;
    cout << " file name: ";
    getline(cin,fileDir);
    return fileDir;
}

/** split(): Returns a vector of strings divided by specified
 *  characters in assignment description.
 *
 *  @param {string} str - The string to split up.
 *  @return {vector<string>} - The vector output of the divided string.
 */

vector<string> split(string str) {
    vector<string> split;
    string word = "";
    bool hasDigit = false;

    /** Parse the line, removing any characters considered word separators.
    */

    for (char c : str) {

        if (isalpha(c) || c == '\'' || c == '-')
            word += c;

        else if (!isdigit(c) && !word.empty()) {
            if (!hasDigit)
                split.push_back(word);
            word.clear();
            hasDigit = false;
        }

        if (isdigit(c))
            hasDigit = true;

    }

    return split;
}

/** readDictionary(): Reads dictionary from file, inserting words into a hash table.
 *
 *  @param {string} dictFile - The name of the dictionary file.
 *  @param {string} dict - The hash table for the dictionary.
 */

void readDictionary(ifstream& dictFile, hashTable *dict) {
    string read;

    while (getline(dictFile, read)) {
        transform(read.begin(), read.end(), read.begin(), [](char c){ return tolower(c); });
        dict -> insert(read);
    }

    dictFile.close();
}

/** spellCheck(): Checks given text file, using provided dictionary.
 *
 *  @param inFile - File to check.
 *  @param outFile - File to output results to.
 *  @param dict - Dictionary for checking.
 */

void spellCheck(ifstream& inFile, ofstream& outFile, hashTable *dict) {
    string read;
    vector<string> processed;
    vector<string> words;
    int line = 0;

    while (getline(inFile, read)) {
        line++;
        if (read.empty())
            continue;

        transform(read.begin(), read.end(), read.begin(), [](char c){ return tolower(c); });
        words = split(read + " ");

        for (const string& word : words) {
            if (word.length() > 20)
                outFile << "Long word at line " << line << ", starts: " << word.substr(0,20) << "\n";

            else if (!(dict -> contains(word)))
                outFile << "Unknown word at line " << line << ": " << word << "\n";
        }
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
    time = ((double)(final-initial)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << time << "\n";

    cout << "Input";
    inFile.open(getFileName());
    cout << "Output";
    outFile.open(getFileName());

    initial = clock();
    spellCheck(inFile, outFile, dict);
    final = clock();
    time = ((double)(final-initial)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << time << "\n";
}
