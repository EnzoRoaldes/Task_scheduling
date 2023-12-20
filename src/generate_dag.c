#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../include/generate_dag.h"

void generate_dag(int nodes, int max_dependencies, float max_execution_time) {
    char filename[32];
    sprintf(filename, "tasks/tasks_%d.txt", nodes);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int total_dependencies = 0;

    // Write the total number of nodes and dependencies on the first line
    fprintf(file, "%d %d            ", nodes, total_dependencies);

    for (int node = 0; node < nodes; ++node) {
        int num_dependencies = (node == 0) ? 0 
                                           : rand() % ((node > max_dependencies) ? max_dependencies : node);
        float execution_time = (rand()% 100*max_execution_time + 1)/100;

        // Allocate an array to store dependencies
        int *dependencies = malloc(num_dependencies * sizeof(int));

        // Check for circular dependency, self-dependency, and duplicate dependencies
        for (int i = 0; i < num_dependencies; ++i) {
            int test;
            do {
                test = 0;
                int new = rand() % node + 1;
                for (int j = 0; j < i; ++j) {
                    if (new == dependencies[i]) {
                        test = 1;
                        break;
                    }
                }
                dependencies[i] = new;
            } while (dependencies[i] == node || dependencies[i] > node || test);
        }

        // Update the total number of dependencies
        total_dependencies += num_dependencies;

        // Write to the file
        fprintf(file, "\n%d %.2f\n", num_dependencies, execution_time);
        for (int i = 0; i < num_dependencies; ++i) {
            fprintf(file, "%d\n", dependencies[i]);
        }

        free(dependencies);
    }

    // Move to the beginning of the file to update the total number of dependencies
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d %d", nodes, total_dependencies);
    fclose(file);
}