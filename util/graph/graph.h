#ifndef GRAPH_H
#define GRAPH_H

typedef struct _graph graph_t;
typedef struct _adj_list adj_list_t;


struct _graph {
    int v;
    int *visited;
    adj_list_t *adj_list;
};

struct _adj_list {
    int src;
    int weight;
    adj_list_t *next;
};

#endif
