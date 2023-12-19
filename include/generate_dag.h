#ifndef GENERATE_DAG_H
#define GENERATE_DAG_H

/*  Generates a directed acyclic graph and writes it
 *  in "nodes/nodes_X.txt" with 'X' the number of nodes
 */
void generate_dag(int nodes, int max_dependencies, float max_execution_time);

#endif