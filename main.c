#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "node.h"
#include "heap.h"
#include "graph.h"


int simu(int* res, graph *g) {
    int *statuses = (int *)calloc(g->nb_node, sizeof(int));
    if (statuses == NULL) {
        perror("simu : malloc statuses");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < g->nb_node; ++i) {
        while (statuses[i] == 0){
            int nb_parent = (i == g->nb_node-1) 
                    ?  g->tot_parents - (g->t_node[i]).pos 
                    : (g->t_node[i+1]).pos - (g->t_node[i]).pos;
            
            int dep_cleared = 1;
            for (int j = 0; j < nb_parent; ++j) {
                if (statuses[j] != 2) {
                    dep_cleared = 0;
                }
            }
            if (dep_cleared) statuses[i] = 1;
        }
        sleep( (g->t_node[i]).exe_time );
        statuses[i] = 2;
    }
    return EXIT_SUCCESS;
}


int main(int argc, char **argv) {

    /* test de la fonction read et print */
    graph *g = malloc(sizeof(graph));
    char *file = "nodes.txt";
    read_file(file, g);
    print_graph(g);

    int *res = DFS(g);

    printf("[ ");
    for (int i = 0; i < g->nb_node; ++i) {
        printf("%d ",res[i]);
    }
    printf("]\n");

    double start = omp_get_wtime();
    simu(res, g);
    double end   = omp_get_wtime();

    printf("total execution time = %lfs\n", end - start);

    return 0;
}