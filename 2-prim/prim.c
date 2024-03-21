#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../util/heap/heap.h"

#define WEIGHT_INFINITY INT_MAX

void initialize_graph(int V, int graph[V][V]) {
    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            graph[i][j] = WEIGHT_INFINITY;
        }
    }
}

void initialize_visited(int V, int visited[V]) {
    for (int i=0; i<V; i++) {
        visited[i] = 0;
    }
}

void initialize_distances(int V, int distances[V]) {
    for (int i=0; i<V; i++) {
        distances[i] = WEIGHT_INFINITY;
    }
}

void initialize_parents(int V, int parents[V]) {
    for (int i=0; i<V; i++) {
        parents[i] = -1;
    }
}

void prim(int V, int graph[V][V], int src) {
    int visited[V];
    initialize_visited(V, visited);

    int distances[V];
    initialize_distances(V, distances);

    int parents[V];
    initialize_parents(V, parents);

    heap_t *queue = heap_create(V);

    distances[src] = 0;
    visited[src] = 1;
    heap_enqueue(queue, distance_create(src, 0));

    while (!heap_is_empty(queue)) {
        distance_t *d = heap_dequeue(queue);

        int u = d->to_vertex;
        visited[u] = 1;

        for (int i=0; i<V; i++) {
            if (graph[u][i] == WEIGHT_INFINITY) continue;

            if (!visited[i] && graph[u][i] < distances[i]) {
                distances[i] = graph[u][i];
                parents[i] = u;
                heap_enqueue(queue, distance_create(i, distances[i]));
            }
        }
    }
    
    printf("(from:weight) -");
    for (int i=0; i<V; i++) {
        if (i == src) printf(" (NULL:0)");
        else printf(" (%d:%d)", parents[i]+1, distances[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int V, E;
    scanf("%d %d", &V, &E);

    int graph[V][V];
    initialize_graph(V, graph);

    for (int i=0; i<E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        graph[--u][--v] = w;
        graph[v][u] = w;
    }

    prim(V, graph, 0);

    return 0;
}
