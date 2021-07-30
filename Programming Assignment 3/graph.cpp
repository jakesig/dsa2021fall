/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  graph.cpp
 *
 *  This code implements a graph and Dijkstra's algorithm,
 *  containing all the implemented functions from the
 *  graph.h file.
 */

#include <string>
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
        int pos = read.find(' ');

        /** Break each line into three components using the processed vector.
         *  processed[0] will store the starting vertex, processed[1] will store
         *  the ending vertex, and processed[2] will store the distance between
         *  the two.
         */
        
        while (pos < read.length()) {
            component = read.substr(0, pos);
            processed.push_back(component);
            read.erase(0, pos + 1);
            pos = read.find(' ');
        }

        processed.push_back(read.substr(0, read.find('\r')));

        /** Insert an edge into the graph using the two vertices and distance
         *  stored in the processed vector. After inserting, clear the processed
         *  vector to repeat the tokenization.
         */

        insert(processed[0], processed[1], processed[2]);
        processed.clear();
    }

    inFile.close();
}

/** insert(): Inserts an edge using the two vertices and a distance.
 *
 *  @param {string} v1 - The starting vertex.
 *  @param {string} v2 - The ending vertex.
 *  @param {string} distance - The distance.
 */

void graph::insert(string v1, string v2, string distance) {

    /** The new vertices, and the new edge.
     */

    vertex start, end;
    vertex::edge startToEnd{};

    /** Initialize a new starting vertex if it is not in the hash table.
     */

    if (!mapping -> contains(v1)) {
        start.id = v1;
        start.distance = INT16_MAX;
        data.push_back(start);
        mapping -> insert(v1, &data.back());
    }

    /** Initialize a new end vertex if it is not in the hash table.
     */

    if (!mapping -> contains(v2)) {
        end.id = v2;
        end.distance = INT16_MAX;
        data.push_back(end);
        mapping -> insert(v2, &data.back());
    }

    /** Obtain pointers to the new vertices.
     */

    auto *pv1 = static_cast<vertex *> (mapping -> getPointer(v1));
    auto *pv2 = static_cast<vertex *> (mapping -> getPointer(v2));

    /** Create edge from new vertices.
     */

    startToEnd.next = pv2;
    startToEnd.cost = stoi(distance);
    pv1 -> adjacencyList.push_back(startToEnd);
}

/** dijkstra(): Performs Dijkstra's algorithm given a starting vertex.
 *
 *  @param {string} startID - The ID of the starting vertex.
 */

void graph::dijkstra(string &startID) {
    vertex *removedVertex;
    heap *dijkstraHeap = new heap(data.size());

    /** Important to change the distance in the start vertex to 0, since
     *  the node you're starting from doesn't have any distance to the
     *  node you're starting from.
     */

    auto *start = static_cast<vertex *> (mapping -> getPointer(startID));
    start -> distance = 0;
    start -> previous = start;

    /** Load the heap with all the vertices stored in the list in the graph.
     */

    for (auto &it : data)
        dijkstraHeap -> insert(it.id, it.distance, &it);

    /** Constantly deleteMin from the heap, checking if there is a smaller distance.
     *  If there is, alter the distance of the next vertex accordingly.
     */

    while (dijkstraHeap -> deleteMin(nullptr, nullptr, &removedVertex) != 1) {

        /** The vertex taken off the heap is now known, so change the known variable
         *  to true to prevent any further alteration of the vertex.
         */

        removedVertex -> known = true;

        /** Now parse through the adjacency list, looking for unknown vertices and shorter
         *  distances. Keep track of the previous vertex by using the previous variable,
         *  so a path can be figured out later.
         */

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
    string toWrite;
    string path;
    vertex thisVertex;

    /** Parse through each vertex in data. Keep track of the shortest
     *  path using the previous variable in each vertex.
     */

    for (const vertex &v : data) {
        thisVertex = v;
        path = v.id;

        /** Start by writing the ID of the vertex.
         */

        toWrite += v.id + ": ";

        /** If the distance was not changed from infinity,
         *  then write "NO PATH".
         */

        if (v.distance == INT16_MAX)
            toWrite += "NO PATH\n";

        /** Otherwise, determine shortest path (and distance)
         *  and write the sequence of vertices.
         */

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
