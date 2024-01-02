#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#include "../include/node.h"
#include "../include/heap.h"
#include "../include/graph.h"
#include "../include/generate_dag.h"

#define VALID "\x1B[32mVALID\033[0m"
#define INVALID "\x1B[31mINVALID\033[0m"


int check_clear_dep(int node, int nb_parent, graph *g, int *statuses) {
    int dep_cleared = 1;
    for (int j = 0; j < nb_parent; ++j) {
        if (statuses[g->t_parent[(g->t_node[node]).pos + j]] != 2) {
            dep_cleared = 0;
            break;
        }
    }
    return dep_cleared;
}


void simu_node(int node, graph *g, int *statuses, int *exe_order, int *cpt) {
    while (statuses[node] == 0) {
        int nb_parent = (node == g->nb_node - 1)
                            ? g->tot_parents - (g->t_node[node]).pos
                            : (g->t_node[node + 1]).pos - (g->t_node[node]).pos;
        int dep_cleared = check_clear_dep(node, nb_parent, g, statuses);

        if (dep_cleared) statuses[node] = 1;
    }

    usleep(1000000 * (g->t_node[node]).exe_time);

    #pragma omp critical
    {
        exe_order[(*cpt)++] = node;
    }

    statuses[node] = 2;
}


/* Simulates the execution of the tasks written in res 
 * and stores their order of completion in exe_order
 */
int simu(int* res, graph *g, int *exe_order) {
    int *statuses = (int *)calloc(g->nb_node, sizeof(int));
    if (statuses == NULL) {
        perror("simu: malloc statuses");
        return EXIT_FAILURE;
    }

    int cpt = 0;

    #pragma omp parallel for shared(statuses, exe_order, cpt) schedule(dynamic)
    for (int i = 0; i < g->nb_node; ++i) {
        simu_node(res[i], g, statuses, exe_order, &cpt);
    }

    free(statuses);
    return EXIT_SUCCESS;
}


int simu_seq(int* res, graph *g) {

    double cpt = 0;

    for (int i = 0; i < g->nb_node; ++i) {
        cpt += (g->t_node[res[i]]).exe_time;
    }

    return cpt;
}


/* Checks thats the execution order is coherent with
 * regards to the dependencies between the tasks
 */
int check_parent_present(int *exe_order, int i, int parent) {
    for (int k = 0; k < i; k++) {
        if (exe_order[k] == parent) {
            return 1; // Parent is present
        }
    }
    return 0; // Parent is not present
}


void check_validity(graph *g, int *exe_order) {
    char *color = VALID;

    for (int i = 0; i < g->nb_node; ++i) {
        int nb_parent = (exe_order[i] == g->nb_node-1) 
                    ?  g->tot_parents - (g->t_node[exe_order[i]]).pos 
                    : (g->t_node[exe_order[i]+1]).pos - (g->t_node[exe_order[i]]).pos;
        
        for (int j = 0; j < nb_parent; ++j) {
            int pos_parent = (g->t_node[exe_order[i]]).pos + j;

            if (!check_parent_present(exe_order, i, g->t_parent[pos_parent])) {
                color = INVALID;
            }
        }
    }

    printf("Check schedule validity: %s\n", color);
}


/** Launches the simulation of the execution of the tasks
 * and calculates its runtime
 * @param details True if the user wants to print details 
 * about the task file/ False otherwise
 */
int *execute_task_scheduling(int *res, graph *g, int simulate) {

    int *exe_order = (int *)calloc(g->nb_node, sizeof(int));
    
    if (exe_order == NULL) {
        free(res);
        fini_graph(g);
        free(g);
        perror("main : calloc exe_order");
        return NULL;
    }
    
    if (simulate) {
        double start = omp_get_wtime();
        simu(res, g, exe_order);
        double end   = omp_get_wtime();

        printf("Parallel execution duration = %.1fs\n", (double)(end - start));
    }
    
    double exe_time = simu_seq(res, g);
    printf("Sequential execution duration = %.1fs\n", exe_time);

    for (int i = 0; i < g->nb_node; ++i) {
        exe_order[i] = res[i];
    }
    
    free(res);
    return exe_order;
}


/* Prints the order in which the tasks have been
 * carried out
 */
void print_exe_order(int *exe_order, int nb_node) {
    printf("Execution order :\n [ ");
    for (int i = 0; i < nb_node; ++i) {
        printf("%d ", exe_order[i]);
    }
    printf("]\n");
}


int main(int argc, char **argv) {

    char answer[32];
    char filename[64];
    int nb_task = 0;
    int test = 0;
    int test_tasks[3] = {5,7,9};
    int nb_files = 3;
    int *exe_order;
    int details = 0;
    graph *g = malloc(sizeof(graph));
    
    if (argc == 1) {
        printf("Test on provided examples [y/n] ?\nOtherwise create your own set of tasks\n");
        scanf("%s", answer);

        if (answer[0] == 'n') {

            int max_dependencies;
            float max_execution_time;

            printf("Enter the number of tasks to schedule : ");
            scanf("%d", &nb_task);

            printf("Enter the maximum number of dependencies per task: ");
            scanf("%d", &max_dependencies);

            printf("Enter the maximum execution time in sec for a task: ");
            scanf("%f", &max_execution_time);

            generate_dag(nb_task, max_dependencies, max_execution_time);
            sprintf(filename, "tasks/tasks_%d.txt", nb_task); 
            nb_files = 1;
        }
        else test = 1;
    } else {
        sprintf(filename, "%s", argv[1]);
        nb_files = 1;
    }

    
    printf("Do you want to print more details about the content of the tasks ? [y/n]\n");
    printf("These details will only be printed for files of less than 10 tasks.\n");
    scanf("%s", answer);
    
    if (answer[0] == 'y')
        details = 1;
    
    
    printf("Do you want to simulate the execution (get the time in sec) ? [y/n] \n");
    scanf("%s", answer);

    int simu = 0;
    if (answer[0] == 'y') 
        simu = 1;


    for (int i = 0; i < nb_files; ++i) {
        
        if (argc > 1)  {
            read_file(filename, g, details);
            nb_task = g->nb_node;
        } if (test) {
            nb_task = test_tasks[i];
            printf("\nTest on %d tasks : \n", nb_task);
            sprintf(filename, "tasks/tasks_%d_test.txt", nb_task);
            read_file(filename, g, details);
        } else {
            printf("\nTest on %d tasks : \n", nb_task);
            sprintf(filename, "tasks/tasks_%d.txt", nb_task);
            read_file(filename, g, details);
        }

        int *res = DFS(g);
    
        exe_order = execute_task_scheduling(res, g, simu);
        print_exe_order(exe_order, g->nb_node);
        check_validity(g, exe_order);
        fini_graph(g);
        printf("\n######################################\n");
    }
    
    free(exe_order);
    free(g);
    return 0;
}