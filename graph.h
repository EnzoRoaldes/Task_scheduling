#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph {
    int nb_node;
    int tot_parents;
    node *t_node;
    int *t_parent;
} graph;



int read_file(char *file, graph *g);


int fini_graph(graph *g);


void print_graph(graph *g);


int *DFS(graph *g);


void new_dep(int indice, priority_queue *q, graph *g);


priority_queue *find_no_dep(graph *g); // renvoie les noeuds sans dépendances




#endif