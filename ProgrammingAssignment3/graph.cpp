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
#include <iostream>
#include "hash.h"
#include "heap.h"
#include "graph.h"

using namespace std;

/** graph(): Constructor for the Graph.
 */

graph::graph(){
    mapping = new hashTable(1000000);
}

/** readFile(): Reads file and creates corresponding graph.
 *
 *  @param {ifstream&} inFile - The file being read.
 */

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

        processed.push_back(read.substr(0, read.find("\r")));

        insert(processed);
        processed.clear();
    }

    inFile.close();
}

/** insert(): Inserts edge using the two vertices and a distance stored in a vector.
 *
 *  @param {vector<string>} processedLine - The information of the edge to be inserted.
 */

void graph::insert(vector<string> processedLine) {
    vertex *start;
    vertex *end;
    vertex::edge startToEnd{};

    /** For loop that runs twice, for each vertex provided in each line
     *  of the input file. Initializes a new vertex if vertex is not
     *  already in the hash table. Inserts an edge if both vertices exist.
     */

    for (int i = 0; i < 2; ++i) {

        /** Initialize a new vertex if it is not in the hash table.
         */

        if (!mapping -> contains(processedLine[i])) {
            vertex *temp = new vertex;
            temp -> id = processedLine[i];
            temp -> known = false;
            temp -> distance = INT16_MAX;
            temp -> adjacencyList = {};
            data.push_back(*temp);
            mapping -> insert(processedLine[i], temp);
        }

        else {
            auto *temp = (vertex *) mapping -> getPointer(processedLine[i]);

            /** The first run is for the starting vertex, and the second run
             *  is for the ending vertex. So set them accordingly.
             */

            if (i == 0)
                start = temp;
            if (i == 1)
                end = temp;
        }
    }

    /** Check that both vertices exist using the contains() function,
     *  then insert a new edge.
     */

    if (mapping -> contains(processedLine[0]) && mapping -> contains(processedLine[1])) {
        startToEnd.next = end;
        startToEnd.cost = stoi(processedLine[2]);
        start -> adjacencyList.push_back(startToEnd);
   }

}

/** dijkstra(): Performs Dijkstra's algorithm given a starting vertex.
 *
 *  @param {string} startID - The ID of the starting vertex.
 */

void graph::dijkstra(string &startID) {

    /** A variable that keeps track of the vertex being removed from the heap along with
     *  the heap itself.
     */

    vertex *removedVertex;
    heap *dijkstraHeap = new heap(data.size());
    vertex *start = static_cast<vertex *>(mapping->getPointer(startID));
    start -> distance = 0;
    start -> previous = start;

    /** Load the heap with all the vertices stored in the list
     *  in the graph.
     */

    for (vertex v : data)
        dijkstraHeap -> insert(v.id, v.distance, &v);

    /** Constantly deleteMin from the heap, checking if there is a smaller distance.
     *  If there is, alter the distance of the next vertex accordingly.
     */

    while (dijkstraHeap -> deleteMin(nullptr, nullptr, &removedVertex) != 1) {
        removedVertex -> known = true;
        for (vertex::edge e : removedVertex -> adjacencyList) {
            if (!e.next -> known && (e.cost + removedVertex -> distance) < (e.next -> distance)) {
                e.next -> distance = e.cost + removedVertex -> distance;
                dijkstraHeap -> setKey(e.next -> id, e.cost + removedVertex -> distance);
                e.next -> previous = removedVertex;
            }
        }
    }
}

/** writeToFile(): Writes the output of Dijkstra's algorithm to specified
 *  output file.
 *
 *  @param {string} startID - The ID of the starting vertex.
 *  @param {ofstream&} outFile - The file to output to.
 */

void graph::writeToFile(std::string startID, std::ofstream &outFile) {
    string toWrite = "";
    vertex thisVertex;
    string path = "";

    for (vertex v : data) {
        thisVertex = v;
        path = v.id;

        toWrite += v.id + ": ";

        if (v.distance == INT16_MAX)
            toWrite += "NO PATH\n";

        else {
            toWrite += to_string(v.distance) + " [";

            while (thisVertex.id != startID) {
                thisVertex = *thisVertex.previous;
                path = thisVertex.id + ", " + path;
            }

            toWrite += path + "]\n";
        }
    }

    outFile << toWrite;

    outFile.close();
}
