#include <stdio.h> 
#include <stdlib.h> 

void make_set(int parent[], int rank[], int n) { 
    for (int i=0; i<n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int edge_comparator(const void* p1, const void* p2) { 
    const int *e1 = p1;
    const int *e2 = p2;

    return e1[2] - e2[2];
}

int find_parent(int parent[], int component) { 
    if (parent[component] == component) {
        return component;
    }
    parent[component] = find_parent(parent, parent[component]);
    return parent[component];
}

void union_set(int u, int v, int parent[], int rank[], int n) {
    u = find_parent(parent, u);
    v = find_parent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

int kruskal(int n, int edge[n][3]) {
    int parent[n];
    int rank[n];
    int min_cost = 0;

    make_set(parent, rank, n);

    qsort(edge, n, sizeof(edge[0]), edge_comparator);

    printf("(from,to) = weight\n");

    for (int i=0; i<n; i++) {
        int u = find_parent(parent, edge[i][0]);
        int v = find_parent(parent, edge[i][1]);
        int w = edge[i][2];

        if (u != v) {
            union_set(u, v, parent, rank, n);
            min_cost += w;
            printf("(%d,%d) = %d\n", edge[i][0]+1, edge[i][1]+1, w);
        }
    }

    return min_cost;
}

int main(int argc, char const *argv[]) { 
    int V, E;
    scanf("%d %d", &V, &E);

    int edge[E][3];

    for (int i=0; i<E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        edge[i][0] = u-1;
        edge[i][1] = v-1;
        edge[i][2] = w;
    }

    int min_cost = kruskal(E, edge);
    printf("min_cost = %d\n", min_cost);

    return 0;
}
