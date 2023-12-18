#include <stdlib.h>
#include <stdio.h>

#include "stack.h"


stack *stack_init() {
    stack *s = malloc(sizeof(stack));
    s->head = NULL;
    s->size = 0;
    return s;
}


void stack_push(stack *s, int value) {
    stack_node *node = malloc(sizeof(stack_node));   
    node->value = value;
    node->next = s->head;
    s->head = node;
    s->size += 1;
}


int stack_pop(stack *s) {
    assert(!stack_is_empty(s));
    int value = s->head->value;
    stack_node *cur_head = s->head;
    s->head = s->head->next;
    free(cur_head);
    s->size -= 1;
    return value;
}


int stack_is_empty(stack *s) {
    return (s->head == NULL);
}


void stack_fini(stack *s) {
    while (s->size > 0) {
        int dummy = stack_pop(s);
    }
    free(s);
}