#include <stdio.h>
#include <stdlib.h>

#include "heap.h"



static void swap(priority_queue *q, int pos1 , int pos2) {
    /* swaps the two nodes (at respective position pos1, pos2) in q
     */

    if (pos1 < 0 || pos2 < 0 || pos1 > q->size || pos2 > q->size) {
        printf("swap error : pos1/pos2 wrong value");
        return;
    }

    /* swap pos in pos_in_heap */
    q->pos_in_heap[q->heap[pos1].id] = pos2;
    q->pos_in_heap[q->heap[pos2].id] = pos1;

    /* swap values in hipe */
    priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;
}


static void sift_up(priority_queue *q, int pos) {
    /* move up the node at position pos in q
     * until the properties of the heap are satisfied
     */

    if (pos < 0 || pos > q->size) {
        printf("sift_up error : pos wrong value");
        return;
    }

    while ( pos > 0 && q->heap[pos].val > q->heap[(pos-1)/2].val) {
        swap(q, pos, (pos-1)/2);
        pos = (pos-1)/2;
    }
}


static void sift_down(priority_queue *q, int pos) {
    /* move down the node at position pos in q
     * until the properties of the heap are satisfied
     */

    if (pos < 0 || pos > q->size) {
        printf("sift_down error : pos wrong value");
        return;
    }

    int l_son = 2*pos+1;
    int r_son = l_son+1; 
    
    while ( ( l_son < q->size && q->heap[pos].val < q->heap[l_son].val ) ||
            ( r_son < q->size && q->heap[pos].val < q->heap[r_son].val ) ) {
        
        if ( ( r_son < q->size && q->heap[pos].val < q->heap[r_son].val ) &&
           ( q->heap[r_son].val > q->heap[l_son].val ) ) {

            swap(q, pos, r_son);
            pos = r_son;
        }

        else {

            swap(q, pos, l_son);
            pos = l_son;
        }

        l_son = 2*pos+1;
        r_son = l_son+1;
    }
}


void priority_queue_fini(priority_queue *q) {
    /* free all the queue q 
     */

    /* free datas */
    while (q->size != 0) {
        priority_queue_pop(q);
    }

    free(q->pos_in_heap);
    free(q);
}


void priority_queue_print(priority_queue *q) {
    /* print the elements of the queue q in the format of a binary tree
     * and also the pos_in_heap
     */

    /* print the pos_in_heap */
    printf("[ ");

    for (int i = 0; i < q->capacity; ++i) {
        printf("%d ", q->pos_in_heap[i]);
    }

    printf("]\n");


    /* print the heap */
    if (q->size == 0) {
        printf("Empty queue\n\n");
        return;
    }

    
    int cpt = 0;

    printf("[ ");

    for (int i = 0; i < q->size; ++i) {

        if (i == 0) {
            printf("[ ");
        }

        printf("%.2lf ", q->heap[i].val);
        
        if ((i+2)%(1 << cpt) == 0) {  /* 1<<cpt = 2^cpt */

            if (i+1 < q->size) {
                printf("]\n  [ ");
            }
            else {
                printf("] ");
            }
            cpt++;
        }

        else if (i+1 < q->size) {
            printf("  ");
        }

        else {
            printf("] ");
        }
    }

    printf("]\n\n");
}


int priority_queue_init(priority_queue *q, int max_id) {
    /* initialize with default values the queue q 
     * and a capacity of max_id
     */

    if (q == NULL) {
        printf("init error : q not malloc\n");
        return EXIT_FAILURE;
    }

    q->heap = malloc(sizeof(priority_data)*max_id);
    q->capacity = max_id;
    q->size = 0;
    q->pos_in_heap = malloc(sizeof(int)*max_id);
    
    for (int i = 0; i < max_id; i++) {
        q->pos_in_heap[i] = -1;
    }

    return EXIT_SUCCESS;
}


int priority_queue_push(priority_queue *q, int id, float val) {
    /* push a node with parameters id and val into the queue q
     * such that the properties of the heap are style verified
     */

    /* verify id */
    if (id < 0 || id > q->capacity -1) {
        printf("push error : wrong id\n");
        return EXIT_FAILURE;
    }

    /* create element */
    priority_data new;
    new.id = id;
    new.val = val;

    /* add element at the bottom */
    q->heap[q->size] = new;

    /* fill pos_in_heap */
    q->pos_in_heap[id] = q->size;

    /* increment the size */
    q->size++;

    /* sift up new */
    sift_up(q, q->size-1); 
     
    return EXIT_SUCCESS;
}


priority_data priority_queue_pop(priority_queue *q) {
    /* extract and return the first element of the queue
     * such that the properties of the heap are style verified
     */

    /* verify size */
    if (q->size == 0) {
        printf("init error : q empty\n");
        exit(0);
    }

    priority_data first = q->heap[0];

    /* swap with last element */
    swap(q, 0, q->size-1);

    /* put the default value in pos_in_heap */
    q->pos_in_heap[first.id] = -1;

    /* decrement the size */
    q->size--;

    /* sift down last */
    sift_down(q, 0);

    return first;
}