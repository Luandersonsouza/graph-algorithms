#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// stack definition

typedef struct _stack stack_t;

struct _stack {
    int n;
    int *items;
    int top;
};

// stack functions

stack_t *create_stack(int n) {
    stack_t *stack = (stack_t*) malloc(sizeof(stack_t));
    stack->n = n;
    stack->items = (int*) malloc(n * sizeof(int));
    stack->top = -1;

    return stack;
}

void push(stack_t *stack, int x) {
    if (stack->top >= stack->n - 1) {
        printf("stack overflow!");
    } else {
        stack->top++;
        stack->items[stack->top] = x;
    }
}

void pop(stack_t *stack) {
    if (stack->top <= -1) {
        printf("stack underflow!");
    } else {
        stack->top--;
    }
}

// graph definition

typedef struct _graph graph_t;
typedef struct _adj_list_node adj_list_node_t;
typedef struct _adj_list adj_list_t;

struct _graph {
    int v;
    int *visited;
    adj_list_t *adj_list;
};

struct _adj_list_node {
    int dest;
    int weight;
    adj_list_node_t *next;
};

struct _adj_list {
    adj_list_node_t *head;
};

// graph functions

graph_t *create_graph(int v) {
    graph_t *graph = (graph_t*) malloc(sizeof(graph_t));
    graph->v = v;
    graph->adj_list = (adj_list_t*) malloc(v * sizeof(adj_list_t));
    graph->visited = (int*) malloc(v * sizeof(int));

    for (int i=0; i<v; i++) {
        graph->adj_list[i].head = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

adj_list_node_t *new_adj_list_node(int dest, int weight) {
    adj_list_node_t *new_node = (adj_list_node_t*) malloc(sizeof(adj_list_node_t));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

void get_transpose(graph_t *gr, int src, int dest, int weight) {
    adj_list_node_t *new_node = new_adj_list_node(src, weight);
    new_node->next = gr->adj_list[dest].head;
    gr->adj_list[dest].head = new_node;
}

void add_edge(graph_t *graph, graph_t *gr, int src, int dest, int weight) {
    adj_list_node_t *new_node = new_adj_list_node(dest, weight);
    new_node->next = graph->adj_list[src].head;
    graph->adj_list[src].head = new_node;
    get_transpose(gr, src, dest, weight);
}

void print_graph(graph_t *graph) {
    for (int i=0; i<graph->v; i++) {
        adj_list_node_t *temp = graph->adj_list[i].head;
        while (temp) {
            printf("(%d -> %d(%d))\t", i, temp->dest, temp->weight);
            temp = temp->next;
        }
    }
}

void set_fill_order(graph_t *graph, int v, int visited[], stack_t *stack) {
    visited[v] = 1;
    adj_list_node_t *temp = graph->adj_list[v].head;
    
    while (temp) {
        if (!visited[temp->dest]) {
            set_fill_order(graph, temp->dest, visited, stack);
        }
        temp = temp->next;
    }
    push(stack, v);
}

void dfs(graph_t *gr, int v, int visited[]) {
    printf(" %d", v);
    
    visited[v] = 1;
    adj_list_node_t *temp = gr->adj_list[v].head;
    
    while (temp) {
        if (!visited[temp->dest]) {
            dfs(gr, temp->dest, visited);
        }
        temp = temp->next;
    }
}

// find strongly connected components

void kosaraju(graph_t *graph, graph_t *gr, int v) {
    stack_t *stack = create_stack(v);

    int visited[v];
    
    for (int i=0; i<v; i++)
        visited[i] = 0;
    
    for (int i=0; i<v; i++) {
        if (visited[i] == 0) {
            set_fill_order(graph, i, visited, stack);
        }
    }
    
    int count = 1;
    
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    
    while (stack->top != -1) {
        int v = stack->items[stack->top];
        pop(stack);
        
        if (visited[v] == 0) {
            printf("component %d:", count++);
            dfs(gr, v, visited);
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[]) {
	int V, E;
    scanf("%d %d", &V, &E);

    graph_t *graph = create_graph(V);
    graph_t *gr = create_graph(V);

    for (int i=0; i<E; i++) {
    	int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        add_edge(graph, gr, --u, --v, w);
    }
    
    kosaraju(graph, gr, V);
    return 0;
}
