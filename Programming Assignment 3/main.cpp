/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  main.cpp
 *
 *  This code runs Dijkstra's algorithm,
 *  using all the code in the graph.h and
 *  graph.cpp files.
 */

#include <string>
#include <iostream>
#include "graph.h"

using namespace std;

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

    while (!(g -> hasVertex(start))) {
        cout << "Invalid vertex!\nStarting vertex: ";
        getline(cin, start);
    }

    initial = clock();
    g -> dijkstra(start);
    final = clock();
    time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to run algorithm: " << time << "\n";

    cout << "Output";
    outFile.open(getFileName());
    g -> writeToFile(start, outFile);
}

