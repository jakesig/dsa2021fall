/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  graph.cpp
 *
 *  Description goes here.
 */

#include <string>
#include <list>
#include <fstream>
#include "hash.h"
#include "heap.h"
#include "graph.h"

using namespace std;

graph::graph(int capacity){

}

void graph::readFile(ifstream& inFile) {
    string read;
    string component;
    vector<string> processed;

    while (getline(inFile, read)) {
        int pos = read.find(" ");

        while (pos < read.length()) {
            component = read.substr(0, pos);
            processed.push_back(component);
            read.erase(0, pos + 1);
            pos = read.find(" ");
        }

        insert(processed);
    }
}

void graph::insert(vector<string> processedLine) {
    vertex *start;
    vertex *end;
    vertex::edge startToEnd{};

    for (int i = 0; i < 2; ++i) {
        if (!mapping->contains(processedLine[i])) {
            vertex *temp;
            temp->id = processedLine[i];
            temp->known = false;
            temp->cost = 0;
            data.push_back(*temp);
            mapping->insert(processedLine[i], temp);
        }
        else {
            auto *temp = (vertex *) mapping->getPointer(processedLine[i]);

            if (i == 0)
                start = temp;

            if (i == 1)
                end = temp;
        }
    }

    startToEnd.next = end;
    startToEnd.cost = stoi(processedLine[2]);
    start -> adjacencyList.push_back(startToEnd);
}

void graph::dijkstra(vertex *start) {

}
