#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <limits.h>
#include <iostream>
using namespace std;

class Graph {
public:
    int size;
    int adj[100][100] = {0}; // komsuluk bilgisi
    Graph(int s);
    Graph( );
    void addEdge(int src, int des, int cost); // kenar ekleme
    int dijkstra(int src, int des); // dijakstra mantigi ile iki nokta arasindaki en kisa mesafe
};


#endif // GRAPH_H_INCLUDED
