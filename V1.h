#ifndef V1_H
#define V1_H


typedef struct node {
    int status; /* 0 if not visited/ 1 if visited / 2 if ended */
    int nb_dep; /* number of dependancies */
    int *t_dep; /* dependancy table of size at most N-1
                 * all nodes that depend of the current one
                 */
    float exe_time; /* execution time of the node */
} node;


typedef struct node_table {
    int nb_node; /* number of nodes */
    node *nodes; /* array of all the nodes */
} node_table;


int init_node(node *n, int nb_dep, int exe_time);


void fini_node(node *n);





int build_node_table(node_table *t);


void fini_node_table(node_table *t);


int push_node_table(node_table *t, node *n);


int find_node_table(node_table *t, node *n);


node pop_node_table(node_table *t);


void DFS(node_table *t);


node *find_no_dep(node_table *t); // renvoie les noeuds sans dépendances




/* 
LIFO = find no dep (trouve les node sans pred)

for V in lifo : v.status = 1 (visité)

While LIFO not empty :

    visiter le premier u1

    V = succ(u1)

    for v in V : 

        if v.status != 0:
            LIFO.push v
            v.status = 1
        

    u1.status = 2 (terminé)

    supprimer les aretes entrantes e (ie les aretes e = (u1, v) des noeuds v qui dépendent de lui)



*/











#endif