#ifndef NODE_H
#define NODE_H

typedef struct node {
    int status;         /* 0 undiscovered/1 for discovered/2 for visited*/ 
    int pos;            /* position of its first dependency in t_parent*/  
    int nb_child;   
    int nb_parent;
    double exe_time;
} node;


void print_node(node n, int *parents ,int i);


#endif