/** Jacob Sigman
 *  Programming Assignment 4
 *  Professor Sable
 *  main.cpp
 *
 *  This file contains the functions and code needed to run the
 *  isMerge function from the isMerge.h and isMerge.cpp
 *  files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "merge.h"

using namespace std;

string getFileName();
void readFile(ifstream& inFile, ofstream& outFile);

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

/** readFile(): Checks given text file for merges as specified in program description.
 *
 *  @param inFile - File containing words for merges.
 *  @param outFile - File to output results to.
 */

void readFile(ifstream& inFile, ofstream& outFile) {
    string read, component;
    vector<string> processed;

    getline(inFile, read);

    while (!inFile.eof()) {

        /** Break each line into three components using the processed vector.
         */

        for (int i = 0; i < 3; i++) {
            processed.push_back(read.substr(0, read.find('\r')));
            getline(inFile, read);
        }

        /** If it's a merge, write to the output file the merged string
         *  with the characters from the first string as uppercase.
         */

        if (isMergeDynamic(processed[0], processed[1], processed[2]))
            outFile << outputMerge(processed[0], processed[1], processed[2]) << "\n";

        /** Otherwise, write to the output file that it is not a merge.
         */

        else
            outFile << "*** NOT A MERGE ***\n";

        processed.clear();
    }

    inFile.close();
    outFile.close();
}


int main() {
    ifstream inFile;
    ofstream outFile;
    clock_t initial;
    clock_t final;
    double time;

    cout << "Input";
    inFile.open(getFileName());
    cout << "Output";
    outFile.open(getFileName());

    readFile(inFile, outFile);
}
