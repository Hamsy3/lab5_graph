#include "menu.h"
#include "Graph.h"
int choice_action() {
    int choice_action = 0;
    printf("Please, choose action\n");
    printf ("0. Exit\n");
    printf ("1. Add vertice\n");
    printf ("2. Add edge\n");
    printf ("3. Delete vertice\n");
    printf ("4. Delete edge\n");
    printf ("5. Print Matrix\n");
    printf ("6. Depth-first search\n");
    printf ("7. Shortest path\n");
    printf ("8. Topologic sort\n");
    scanf ("%d", &choice_action);
    return choice_action;
}
int menu_action() {
    int choice = 0;
    choice = choice_action();
    if (choice<0 || choice>8) {
      do {
          choice = choice_action();
      } while (choice<0 || choice>8);
  }
  return choice;
}
int menu() {
    int choice = 0;
    Graph graph;
    graph.size = 0;
    graph.matrix = NULL;
    graph.vertices_names = NULL;
    do {
    choice = menu_action();
    switch (choice) {
        case 0:
            if (graph.matrix != NULL) {
                free_matrix(&graph);
            }
            if (graph.vertices_names != NULL) {
                free_names(&graph);
            }
            break;
        case 1: {
            char *name = NULL;
            int flag = 0;
            printf("Please, input name of vertice\n");
            name = readline(NULL);
            for (int i = 0; i < graph.size; ++i) {
                if (strcmp(name, graph.vertices_names[i]) == 0) {
                    flag = 1;
                }
            }
            if (flag == 1) {
                printf("Incorrect name\n");
                break;
            }
            graph = add_vertice(graph, name);
            break;
        }
        case 2: {
            if (add_edge(&graph) == 1) {
                printf("Vertice not found\n");
            }
            break;
        }
        case 3: {
            if (delete_verticile (&graph) == 1) {
                printf("Vertice not found\n");
            }
            break;
        }
        case 4:
            if (delete_edge(&graph) == 1) {
                printf("Vertice not found\n");
            }
            break;
        case 5: {
            if (graph.matrix == NULL) {
                printf("Graph is empty\n");
            } else {
                print_graph(graph);
            }
            break;
        }
        case 6: {
            printf("Please, input start\n");
            char *start = readline(NULL);
            int start_ind = find_index(graph, start);
            printf("Please, input end\n");
            char *end = readline(NULL);
            int end_ind = find_index(graph, end);
            if (DFS_path(graph, start_ind, end_ind) == 1) {
                printf("There is no path between %s and %s\n", start, end);
            }
            free(start);
            free(end);
            break;
        }
        case 7: {
            printf("Please, input start\n");
            char *start = readline(NULL);
            int start_ind = find_index(graph, start);
            printf("Please, input end\n");
            char *end = readline(NULL);
            int end_ind = find_index(graph, end);
            if (Bellman_Ford_algorithm(graph, start_ind, end_ind) == 1) {
                printf("There is no path between %s and %s\n", start, end);
            }
            free(start);
            free(end);
            break;
        }
        case 8:
            if (cycles_check(graph) == 1) {
                printf("Error, cycles\n");
            } else {
                Topologic_sort(graph);
            }
            break;
        default:
            break;
    }
    } while (choice != 0);
    return 0;
}
