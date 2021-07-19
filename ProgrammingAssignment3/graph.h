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

    private:
        struct vertex {
            struct edge {
                vertex* next;
                int cost;
            };

            std::list<edge> adjacencyList;
            bool known;
            int cost;
            std::string id;
            vertex* previous;

            void insert(vertex* next, int cost);
        };

    public:
        graph(int capacity);
        void readFile(std::ifstream& inFile);
        void insert(std::vector<std::string> processedLine);
        void dijkstra(vertex* start);

        std::list<vertex> data;
        hashTable* mapping;

};


#endif //_GRAPH_H
