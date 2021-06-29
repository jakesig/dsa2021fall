#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string getFileName() {
    string fileDir;
    cout << " file name: ";
    getline(cin,fileDir);
    return fileDir;
}

void readDictionary(ifstream& dictFile) {
    string read;

    while (getline(dictFile, read)) {
        //cout << "PROCESSED: " << read << "\n";
    }

    dictFile.close();
}

void readFile(ifstream& inFile, ofstream& outFile) {
    string read;

    /** Main loop for reading each line of the input file.
     */

    while (getline(inFile, read)) {
        //cout << "PROCESSED: " << read << "\n";
    }

    inFile.close();
    outFile.close();
}


int main() {
    ofstream outFile;
    ifstream inFile;
    ifstream dictFile;

    cout << "Output";
    outFile.open(getFileName());
    cout << "Input";
    inFile.open(getFileName());
    cout << "Dictionary";
    dictFile.open(getFileName());

    readDictionary(dictFile);
    readFile(inFile, outFile);
}
