/** Jacob Sigman
 *  Programming Assignment 3
 *  Professor Sable
 *  graph.h
 *
 *  Description goes here.
 */

#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include <fstream>
#include "hash.h"
#include "heap.h"

class graph {

    public:

        /** graph(): Constructor for the Graph.
         */

        graph();

        /** readFile(): Reads file and creates corresponding graph.
         *
         *  @param {ifstream&} inFile - The file being read.
         */

        void readFile(std::ifstream& inFile);

        /** insert(): Inserts an edge using the two vertices and a distance.
         *
         *  @param {string} v1 - The starting vertex.
         *  @param {string} v2 - The ending vertex.
         *  @param {string} distance - The distance.
         */

        void insert(std::string v1, std::string v2, std::string distance);

        /** dijkstra(): Performs Dijkstra's algorithm given a starting vertex.
         *
         *  @param {string} startID - The ID of the starting vertex.
         */

        void dijkstra(std::string &startID);

        /** writeToFile(): Writes the output of Dijkstra's algorithm to specified
         *  output file.
         *
         *  @param {string} startID - The ID of the starting vertex.
         *  @param {ofstream&} outFile - The file to output to.
         */

        void writeToFile(std::string startID, std::ofstream& outFile);

    private:

        /** vertex subclass
         */

        struct vertex {

            /** edge subclass
             */

            struct edge {

                /** Public variables for edge:
                 *  next - A pointer to the next vertex.
                 *  cost - The cost of the edge.
                 */

                vertex* next;
                int cost;
            };

            /** Public variables for vertex:
             *  adjacencyList - A list of all connected edges.
             *  known - Boolean used for Dijkstra's Algorithm.
             *  distance - Calculated distance stored in vertex for Dijkstra's Algorithm.
             *  id - A string associated with the vertex.
             *  previous - Pointer to the previous vertex.
             */

            std::vector<edge> adjacencyList;
            bool known;
            int distance;
            std::string id;
            vertex* previous;
        };

        /** Private variables for graph:
         *  data - List of vertices.
         *  mapping - A hash table for the IDs of each vertex and the pointers to said vertices.
         */

        std::list<vertex> data;
        hashTable* mapping;

};


#endif //_GRAPH_H
