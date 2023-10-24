#include <stdio.h>
#include <stdlib.h>

#include "V1.h"


int init_node(node *n, int nb_dep, int exe_time) {

    if (n == NULL) {
        return EXIT_FAILURE;
    }

    n->nb_dep = nb_dep;
    n->exe_time = exe_time;
    n->status = 0;
    n->t_dep = (node *)malloc(sizeof(node)*nb_dep);

    if (n->t_dep == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


void fini_node(node *n) {

    if (n != NULL) {
        free(n->t_dep);
    }

    free(n);
}


int build_node_table(node_table *t) {

    if (t == NULL) {
        return EXIT_FAILURE;
    }

    t->nb_node = 0;
    t->nodes = malloc(sizeof(node)*t->nb_node);

    if (t->nodes == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


void fini_node_table(node_table *t) {

    if (t != NULL) {
        free(t->nodes);
    }

    free(t);
}


int push_node_table(node_table *t, node *n);


int find_node_table(node_table *t, node *n);


node pop_node_table(node_table *t);


void DFS(node_table *t);


node *find_no_dep(node_table *t);