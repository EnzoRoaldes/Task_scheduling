#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph {
    int nb_node;        /*  total number of node in the graph */
    int tot_parents;    /*  total number of dependencies in the graph */
    node *t_node;       /*  list of all the nodes */
    int *t_parent;      /*  list of the dependencies of each node 
                         *  (starting with dependencies of 0)
                         */
} graph;



/**  Translate a text file with specific format into a graph
 *  The format is discribed in the README
 *  @param details True if the user wants to print details 
 *  about the task file / False otherwise
 */
int read_file(char *file, graph *g, int details);


/*  Free all the datas inside of the graph but not the graph itself
 */
int fini_graph(graph *g);


/*  Allows to print the nodes of the graph with every information needed
 */
void print_graph(graph *g);


/*  Compute the DFS of the graph to find the best task execution order
 *  Return the ordered list of tasks
 */
int *DFS(graph *g);


/*  Compute the new dependencies of the remaining tasks
 *  Find the tasks in the graph that no longer have dependency
 *  And push them in the priority queue
 */
void new_dep(int indice, priority_queue *q, graph *g);


/*  Find the tasks in the graph that have no dependency
 */
priority_queue *find_no_dep(graph *g);



#endif