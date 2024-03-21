#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct _heap {
    int capacity;
    int size;
    distance_t **data;
};

/* private functions */

int get_parent_index(int i);

int get_left_index(int i);

int get_right_index(int i);

void min_heapify(heap_t *queue, int i);

void swap(heap_t *heap, int a_index, int b_index);

/* implementations */

distance_t* distance_create(int to_vertex, int value) {
    distance_t *distance = (distance_t*) malloc(sizeof(distance_t));

    distance->to_vertex = to_vertex;
    distance->value = value;

    return distance;
}

heap_t* heap_create(int capacity) {
    heap_t *heap = (heap_t*) malloc(sizeof(heap_t));
    distance_t **data = (distance_t**) malloc(sizeof(distance_t*) * (capacity + 1)); // 1-based indexing
    
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = data;

    return heap;
}

void heap_enqueue(heap_t *heap, distance_t *item) {
    if (heap->size >= heap->capacity) {
        printf("Heap overflow!");
        exit(-1);
    }

    heap->data[++heap->size] = item;

    int key_index = heap->size;
    int parent_index = get_parent_index(heap->size);

    while (parent_index >= 1 && heap->data[key_index]->value < heap->data[parent_index]->value) {
        swap(heap, key_index, parent_index);
        key_index = parent_index;
        parent_index = get_parent_index(key_index);
    }
}

distance_t* heap_dequeue(heap_t *heap) {
    if (heap->size <= 0) {
        printf("Heap underflow!");
        exit(-1);
    }

    distance_t *item = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    min_heapify(heap, 1);

    return item;
}

int heap_is_empty(heap_t *heap) {
    return heap->size == 0;
}

int get_parent_index(int i) {
    return i/2;
}

int get_left_index(int i) {
    return 2*i;
}

int get_right_index(int i) {
    return 2*i + 1;
}

void min_heapify(heap_t *heap, int i) {
    int smallest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);
    
    if (left_index <= heap->size && heap->data[left_index]->value < heap->data[i]->value) {
        smallest = left_index;
    } else {
        smallest = i;
    }
    
    if (right_index <= heap->size && heap->data[right_index]->value < heap->data[smallest]->value) {
        smallest = right_index;
    }
    
    if (heap->data[i]->value != heap->data[smallest]->value) {
        swap(heap, i, smallest);
        min_heapify(heap, smallest);
    }
}

void swap(heap_t *heap, int a_index, int b_index) {
    distance_t *aux = heap->data[a_index];
    heap->data[a_index] = heap->data[b_index];
    heap->data[b_index] = aux;
}
