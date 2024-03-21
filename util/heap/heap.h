#ifndef HEAP_H
#define HEAP_H

typedef struct _heap heap_t;

typedef struct _distance {
    int to_vertex;
    int value;
} distance_t;

distance_t* distance_create(int to_vertex, int value);

heap_t* heap_create(int capacity);

void heap_enqueue(heap_t *heap, distance_t *item);

distance_t* heap_dequeue(heap_t *heap);

int heap_is_empty(heap_t *heap);

#endif
