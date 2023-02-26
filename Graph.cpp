#include "Graph.h"

Graph::Graph(int s) : size(s) { }

Graph::Graph( ) { }

void Graph::addEdge(int src, int des, int cost){
        adj[src][des] = cost;
    }

int Graph::dijkstra(int src, int des)
    {
        int dist[size];
        bool visit[size];
        for (int i = 0; i < size; i++){
            dist[i] = INT_MAX;
            visit[i] = false;
        }
        dist[src] = 0;
        for (int i = 0; i < size - 1; i++) {
            int u;
            int min = INT_MAX;
            for (int v = 0; v < size; v++)
                if (visit[v] == false && dist[v] <= min){
                    min = dist[v];
                    u = v;
                }
            visit[u] = true;
            for (int v = 0; v < size; v++)
                if (!visit[v] && adj[u][v] && dist[u] + adj[u][v] < dist[v]){
                    dist[v] = dist[u] + adj[u][v];
                }
        }
        return dist[des];
    }
