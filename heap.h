#ifndef HEAP_H
#define HEAP_H


typedef struct priority_data {
    int id;
    float val;
} priority_data;


typedef struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;
    int *pos_in_heap;
} priority_queue;


void priority_queue_fini(priority_queue *q);


void priority_queue_print(priority_queue *q);


int priority_queue_init(priority_queue *q, int max_id);


int priority_queue_push(priority_queue *q, int id, float val);


priority_data priority_queue_pop(priority_queue *q);

#endif