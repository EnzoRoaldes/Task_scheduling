#include <stdio.h>
#include <stdlib.h>

#include "node.h" 
#include "heap.h"
#include "graph.h"


int read_file(char *file, graph *g) {

    /* ouverture de file */
    FILE *f = fopen(file, "r");

    if (f == NULL) {
        fclose(f);
        return EXIT_FAILURE;
    }

    int nb_node = -1;
    int nb_dep = -1;
    int tot_parents= -1;
    double exe_time = -1.;

    /* lecture ligne 1 */
    if (fscanf(f, "%d %d", &nb_node, &nb_dep) == EOF) {
        fclose(f);
        return EXIT_FAILURE;
    } 



    /* création de g->t_node (initialisé à 0) */
    g->tot_parents = nb_dep;
    g->nb_node = nb_node;
    g->t_node = (node *)calloc(nb_node, sizeof(node));

    if (g->t_node == NULL) {
        fclose(f);
        return EXIT_FAILURE;
    }

    g->t_parent = (int *)calloc(nb_dep, sizeof(int));

    if (g->t_parent == NULL) {
        fclose(f);
        fini_graph(g); // tout libérer
        return EXIT_FAILURE;
    }

    int cpt = 0;
    
    /* lecture de tous les noeuds */
    for (int i = 0; i < nb_node; ++i) {
        fscanf(f, ""); /* for the jump line */

        fscanf(f, "%d %lf", &tot_parents, &exe_time);
        //printf("i = %d\t%d, %lf\n", i, nb_parent, exe_time);
        (g->t_node[i]).exe_time = exe_time;
        (g->t_node[i]).pos = cpt;

        for (int j = 0; j < tot_parents ; ++j) {
            fscanf(f, "%d", &g->t_parent[cpt]);
            ( g->t_node[i] ).nb_parent += 1;
            ( g->t_node[g->t_parent[cpt++]] ).nb_child += 1;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}


int fini_graph(graph *g) {

    if (g == NULL) return EXIT_SUCCESS;

    if (g->t_node != NULL) {
        free(g->t_node);
    }

    if (g->t_parent != NULL) {
        free(g->t_parent);
    }

    return EXIT_SUCCESS;
}


void print_graph(graph *g) {
    for (int i = 0; i < g->nb_node; ++i) {
        print_node(g->t_node[i], i);
    }
}


int *DFS(graph *g) {
    int *res = (int *)calloc(g->nb_node, sizeof(int));
    int cpt = 0;
    priority_queue *q = find_no_dep(g);
    priority_data v;
    
    while (q->size > 0) {
        priority_queue_print(q);
        v = priority_queue_pop(q);
        new_dep(v.id, q, g);
        (g->t_node[v.id]).status = 2;
        //printf("cpt = %d\n", cpt);
        res[cpt++] = v.id;
    }
    return res;
}


void new_dep(int indice, priority_queue *q, graph *g) {
    int nb_parent = 0;
    for (int i = 0 ; i < g->nb_node; ++i) {
        if ((g->t_node[i]).status != 0) {
            //printf("status %d = %d\n", i, (g->t_node[i]).status);
            continue;
        }

        nb_parent = (i == g->nb_node-1) 
                    ?  g->tot_parents - (g->t_node[i]).pos 
                    : (g->t_node[i+1]).pos - (g->t_node[i]).pos;
        //printf("nbparent de %d : %d\n", i, nb_parent);
        
        
        for (int j = 0 ; j < nb_parent; ++j) {
            if (g->t_parent[(g->t_node[i]).pos + j] == indice)
                (g->t_node[i]).nb_parent -= 1;
        }
        if ((g->t_node[i]).nb_parent == 0) {
            priority_queue_push(q, i, (g->t_node[i]).exe_time);
            (g->t_node[i]).status = 1;
        }
    }
    
}
    

priority_queue *find_no_dep(graph *g) {
    priority_queue *q = malloc(sizeof(priority_queue));
    priority_queue_init(q, g->nb_node);
    int next_pos = 0;

        
    for (int i = 0; i < g->nb_node; ++i) {
        next_pos = (i == g->nb_node-1) 
                        ?  g->tot_parents
                        : (g->t_node[i+1]).pos;

        if ((g->t_node[i]).pos == next_pos) {
            float val = (g->t_node[i]).exe_time;
            // voir pour une gestion de l'ordre
            priority_queue_push(q, i, val);
            (g->t_node[i]).status = 1;
        }
    }

    return q;
}