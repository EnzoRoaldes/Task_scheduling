#include <stdio.h>
#include <stdlib.h>
#include "../include/node.h"

void print_node(node n, int *t_parent, int i)
{
    printf("Node %d\n\tpos: %d\n\tnb_child: %d\n\tnb_parent: %d\n\texe_time: %lf\n", i, n.pos, n.nb_child, n.nb_parent, n.exe_time);
    printf("\tList parents :\n\t\t[ ");
    for (int j = 0; j < n.nb_parent; ++j) {
        printf("%d ", t_parent[n.pos + j]);
    }
    printf("]\n\n");
}