#ifndef STACK_H
#define STACK_H

typedef struct stack_node{
    stack_node *next;
    int value; 
}stack_node;

typedef struct stack{
    stack_node *head;
    int size;
}stack;


stack *stack_init();


void stack_push(stack *s, int value);


int stack_pop(stack *s);


int stack_is_empty(stack *s);


void stack_fini(stack *s);

#endif