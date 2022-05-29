#include "Graph.h"
void print_graph (Graph graph) {
    for (int i = 0; i < graph.size; ++i) {
        printf("%s ", graph.vertices_names[i]);
    }
    printf("\n");
    for (int i = 0; i < graph.size; ++i) {
        for (int j = 0; j < graph.size; ++j) {
            printf("%d", graph.matrix[i][j]);
            for (int s = 0; s < strlen(graph.vertices_names[j]); ++s) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
Graph add_vertice (Graph graph, char *name) {
    (graph.size)++;
    if (graph.vertices_names == NULL) {
        graph.vertices_names = calloc(1, sizeof(char*));
    } else {
        graph.vertices_names = realloc(graph.vertices_names, graph.size * sizeof(char*));
    }
    graph.vertices_names[(graph.size)-1] = name;
    if (graph.matrix == NULL) {
        graph.matrix = calloc(1, sizeof(int*));
        graph.matrix[0] = calloc(1, sizeof(int));
        graph.matrix[0][0] = 0;
    } else {
        graph.matrix = realloc(graph.matrix, graph.size * sizeof(int*));
        graph.matrix[(graph.size)-1] = calloc(graph.size, sizeof(int));
        for (int i = 0; i < (graph.size)-1; ++i) {
            graph.matrix[i] = realloc(graph.matrix[i], graph.size * sizeof(int));
        }
        for (int i = 0; i < (graph.size)-1; ++i) {
            graph.matrix[(graph.size)-1][i] = 0;
            graph.matrix[i][(graph.size)-1] = 0;
        }
    }
    return graph;
}
int add_edge (Graph *graph) {
    char *first, *second;
    int first_ind, second_ind;
    printf("Please, write name of the first vertice\n");
    first = readline(NULL);
    first_ind = find_index(*graph, first);
    if (first_ind == -1) {
        free(first);
        return 1;
    }
    printf("Please, write name of the second vertice\n");
    second = readline(NULL);
    second_ind = find_index(*graph, second);
    if (second_ind == -1) {
        free(second);
        return 1;
    }
    (*graph).matrix[first_ind][second_ind] = 1;
    free(first);
    free(second);
    return 0;
}
int delete_edge (Graph *graph) {
    char *first, *second;
    int first_ind, second_ind;
    printf("Please, write name of the first vertice\n");
    first = readline(NULL);
    first_ind = find_index(*graph, first);
    if (first_ind == -1) {
        return 1;
    }
    printf("Please, write name of the second vertice\n");
    second = readline(NULL);
    second_ind = find_index(*graph, second);
    if (second_ind == -1) {
        return 1;
    }
    (*graph).matrix[first_ind][second_ind] = 0;
    free(first);
    free(second);
    return 0;
}
int delete_verticile (Graph *graph) {
    printf("Please, write name of the deleting vertice\n");
    char *name = readline(NULL);
    char *buf_name = NULL;
    int ind = find_index(*graph, name);
    if (ind == -1) {
        return 1;
    }
    int *buf = NULL;
    for (int i = ind; i < ((*graph).size - 1); ++i) {
        buf = (*graph).matrix[i+1];
        (*graph).matrix[i+1] = (*graph).matrix[i];
        (*graph).matrix[i] = buf;
        buf_name = (*graph).vertices_names[i+1];
        (*graph).vertices_names[i+1] = (*graph).vertices_names[i];
        (*graph).vertices_names[i] = buf_name;
    }
    free(name);
    free((*graph).vertices_names[((*graph).size-1)]);
    free((*graph).matrix[((*graph).size-1)]) ;
    ((*graph).size)--;
    return 0;
}
int find_index (Graph graph, char *name) {
    for (int i = 0; i < graph.size; ++i) {
        if (strcmp(graph.vertices_names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
void free_matrix (Graph *graph) {
    for (int i = 0; i < (*graph).size; ++i) {
        free((*graph).matrix[i]);
    }
    free((*graph).matrix);
}
void free_names (Graph *graph) {
    for (int i = 0; i < (*graph).size; ++i) {
        free((*graph).vertices_names[i]);
    }
    free((*graph).vertices_names);
}
void DFS_visit (int **matrix, int size, int ind, int *time, int *time_of_begin, int *time_of_end, int *pred, int *color) {
    color[ind] = 1;
    (*time)++;
    time_of_begin[ind] = *time;
    for (int i = 0; i <size; ++i) {
        if (matrix[ind][i] == 1) {
            if (color[i] == 0) {
                pred[i] = ind;
                DFS_visit(matrix, size, i, time, time_of_begin, time_of_end, pred, color);
            }
        }
    }
    color[ind] = 2;
    (*time)++;
    time_of_end[ind] = *time;
}
int DFS_path (Graph graph, int start, int end) {
    int time = 0;
    int *time_of_begin = calloc(graph.size, sizeof(int));
    int *time_of_end = calloc(graph.size, sizeof(int));
    int *color = calloc(graph.size, sizeof(int));
    int *pred = calloc(graph.size, sizeof(int));
    for (int i = 0; i < graph.size; ++i) {
        color[i] = 0;
        pred[i] = -1;
    }
    for (int i = 0; i < graph.size; ++i) {
        if (color[i] == 0) {
            DFS_visit(graph.matrix, graph.size, i, &time, time_of_begin, time_of_end, pred, color);
        }
    }
    int tmp1 = end;
    int tmp2 = end;
    int k = 0;
    while (tmp1 != -1) {
        if (tmp1 == start) {
            int *mass = calloc(graph.size, sizeof(int));
            if ((start == end) && (graph.matrix[start][start] == 0)) {
                break;
            }
            while (tmp2 != pred[start]) {
                mass[k] = tmp2;
                tmp2 = pred[tmp2];
                k++;
            }
            printf("Path: ");
            for (int i =(k-1); i>=0; --i) {
                printf("%s ", graph.vertices_names[mass[i]]);
            }
            printf("\n");
            free(mass);
            free (time_of_begin);
            free (time_of_end);
            free (color);
            free (pred);
            return 0;
        }
        tmp1 = pred[tmp1];
    }
    free (time_of_begin);
    free (time_of_end);
    free (color);
    free (pred);
    return 1;
}
int Bellman_Ford_algorithm (Graph graph, int start, int end) {
    int *d = calloc(1, sizeof(int));
    int *pred = calloc(1, sizeof(int));
    for (int i = 0; i < graph.size; ++i) {
        d[i] = 1000000000;
        pred[i] = -1;
    }
    d[start] = 0;
    for (int k = 1; k < graph.size; ++k) {
        for (int i = 0; i < graph.size; ++i) {
            for (int j = 0 ; j < graph.size; ++j) {
                if (graph.matrix[i][j] == 1) {
                    if (d[j] > (d[i] + 1)) {
                        d[j] = d[i] + 1;
                        pred[j] = i;
                    }
                }
            }
        }
    }
    
    if ((d[end] != 1000000000) &&  (end != -1) && (start != -1)) {
        int temp = end;
        printf("Destinition from %s to %s is: %d\n", graph.vertices_names[start], graph.vertices_names[end], d[end]);
        printf("Path (from right to left): ");
        while (temp != -1) {
            printf("%s ", graph.vertices_names[temp]);
            temp = pred[temp];
        }
        printf("\n");
        free(d);
        free(pred);
        return 0;
    }
    free(d);
    free(pred);
    return 1;
}
void DFS_visit_for_topologic_sort (int **matrix, int size, int ind, int *time, int *time_of_begin, int *time_of_end, int *pred, int *color, List **head) {
    color[ind] = 1;
    (*time)++;
    time_of_begin[ind] = *time;
    for (int i = 0; i <size; ++i) {
        if (matrix[ind][i] == 1) {
            if (color[i] == 0) {
                pred[i] = ind;
                DFS_visit_for_topologic_sort(matrix, size, i, time, time_of_begin, time_of_end, pred, color, head);
            }
        }
    }
    color[ind] = 2;
    List *Ins = calloc(1, sizeof(List));
    Ins->ind = ind;
    Ins->next = *head;
    *head = Ins;
    (*time)++;
    time_of_end[ind] = *time;
}
void Topologic_sort (Graph graph) {
    List *head = NULL;
    int time = 0;
    int *time_of_begin = calloc(graph.size, sizeof(int));
    int *time_of_end = calloc(graph.size, sizeof(int));
    int *color = calloc(graph.size, sizeof(int));
    int *pred = calloc(graph.size, sizeof(int));
    for (int i = 0; i < graph.size; ++i) {
        color[i] = 0;
        pred[i] = -1;
    }
    for (int i = 0; i < graph.size; ++i) {
        if (color[i] == 0) {
            DFS_visit_for_topologic_sort(graph.matrix, graph.size, i, &time, time_of_begin, time_of_end, pred, color, &head);
        }
    }
    List *ptr = head;
    while (ptr != NULL) {
        printf("%s ", graph.vertices_names[ptr->ind]);
        ptr = ptr->next;
    }
    printf("\n");
    
    ptr = head;
    while (head != NULL) {
        ptr = ptr->next;
        free(head);
        head = ptr;
    }
    free (time_of_begin);
    free (time_of_end);
    free (color);
    free (pred);
}
int cycles_check (Graph graph) {
    int time = 0;
    int *time_of_begin = calloc(graph.size, sizeof(int));
    int *time_of_end = calloc(graph.size, sizeof(int));
    int *color = calloc(graph.size, sizeof(int));
    int *pred = calloc(graph.size, sizeof(int));
    for (int i = 0; i < graph.size; ++i) {
        color[i] = 0;
        pred[i] = -1;
    }
    for (int i = 0; i < graph.size; ++i) {
        if (color[i] == 0) {
            DFS_visit (graph.matrix, graph.size, i, &time, time_of_begin, time_of_end, pred, color);
        }
    }
    int temp = 0;
    for (int i = 0; i < graph.size; ++i) {
        temp = pred[i];
        if (graph.matrix[i][i] == 1) {
            free (time_of_begin);
            free (time_of_end);
            free (color);
            free (pred);
            return 1;
        }
        while (temp != -1) {
            if (graph.matrix[i][temp] == 1) {
                free (time_of_begin);
                free (time_of_end);
                free (color);
                free (pred);
                return 1;
            }
            temp = pred[temp];
        }
    }
    free (time_of_begin);
    free (time_of_end);
    free (color);
    free (pred);
    return 0;
}
