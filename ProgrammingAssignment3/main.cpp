/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  main.cpp
 *
 *  Description goes here.
 */

#include <string>
#include <iostream>
#include "graph.h"

using namespace std;

string getFileName() {
    string fileDir;
    cout << " file name: ";
    getline(cin,fileDir);
    return fileDir;
}

int main() {
    ifstream inFile;
    ofstream outFile;
    clock_t initial;
    clock_t final;
    double time;
    string start;
    graph *g = new graph();

    cout << "Input";
    inFile.open(getFileName());
    g -> readFile(inFile);

    cout << "Starting vertex: ";
    getline(cin, start);

    initial = clock();
    g -> dijkstra(start);
    final = clock();
    time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to run algorithm: " << time << "\n";

    cout << "Output";
    outFile.open(getFileName());
    g -> writeToFile(start, outFile);
}

