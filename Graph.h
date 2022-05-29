#ifndef Graph_h
#define Graph_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readline/readline.h"
typedef struct Graph {
    int **matrix;
    char **vertices_names;
    int size;
}Graph;
typedef struct List {
    int ind;
    struct List *next;
}List;
void print_graph (Graph graph);
Graph add_vertice (Graph graph, char *name);
int find_index (Graph graph, char *name);
int add_edge (Graph *graph);
int delete_edge (Graph *graph);
int delete_verticile (Graph *graph);
void free_matrix (Graph *graph);
void free_names (Graph *graph);
void DFS_visit (int **matrix, int size, int ind, int *time, int *time_of_begin, int *time_of_end, int *pred, int *color);
int DFS_path (Graph graph, int start, int end);
int Bellman_Ford_algorithm (Graph graph, int start, int end);
void Topologic_sort (Graph graph);
void DFS_visit_for_topologic_sort (int **matrix, int size, int ind, int *time, int *time_of_begin, int *time_of_end, int *pred, int *color, List **head);
int cycles_check (Graph graph);
#endif
