#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct
{
    Node **adjacency_list;
    int vertices;
} Graph;

Graph *create_graph(int vertices)
{
    Graph *graph = malloc(sizeof(Graph));

    if (graph == NULL)
    {
        return NULL;
    }

    graph->vertices = vertices;
    graph->adjacency_list = calloc(vertices, sizeof(Node *));

    if (graph->adjacency_list == NULL)
    {
        free(graph);
        return NULL;
    }

    return graph;
}

void add_edge(Graph *graph, int from, int to)
{
    Node *node = malloc(sizeof(Node));

    if (node == NULL)
    {
        return;
    }

    node->vertex = to;
    node->next = NULL;

    if (graph->adjacency_list[from] == NULL)
    {
        graph->adjacency_list[from] = node;
        return;
    }

    Node *current = graph->adjacency_list[from];

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = node;
}

void dfs(Graph *graph, int start)
{
    int *visited = calloc(graph->vertices, sizeof(int));
    int *stack = malloc(graph->vertices * sizeof(int));

    if (visited == NULL || stack == NULL)
    {
        free(visited);
        free(stack);
        return;
    }

    int top = 0;

    stack[top++] = start;

    while (top > 0)
    {
        int current = stack[--top];

        if (visited[current])
        {
            continue;
        }

        visited[current] = 1;

        printf("%d ", current);

        /*
         * Push neighbors in reverse order so that
         * they are visited in adjacency-list order.
         */
        Node *neighbor = graph->adjacency_list[current];

        int *neighbors = malloc(graph->vertices * sizeof(int));
        int count = 0;

        while (neighbor != NULL)
        {
            neighbors[count++] = neighbor->vertex;
            neighbor = neighbor->next;
        }

        for (int i = count - 1; i >= 0; i--)
        {
            if (!visited[neighbors[i]])
            {
                stack[top++] = neighbors[i];
            }
        }

        free(neighbors);
    }

    printf("\n");

    free(visited);
    free(stack);
}

void free_graph(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        Node *current = graph->adjacency_list[i];

        while (current != NULL)
        {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }

    free(graph->adjacency_list);
    free(graph);
}

int main(void)
{
    Graph *graph = create_graph(6);

    if (graph == NULL)
    {
        return 1;
    }

    /*
     * Graph:
     *
     *        0
     *       / \
     *      1   2
     *     / \   \
     *    3   4   5
     *         \ /
     *          ─
     */

    add_edge(graph, 0, 1);
    add_edge(graph, 1, 0);

    add_edge(graph, 0, 2);
    add_edge(graph, 2, 0);

    add_edge(graph, 1, 3);
    add_edge(graph, 3, 1);

    add_edge(graph, 1, 4);
    add_edge(graph, 4, 1);

    add_edge(graph, 2, 5);
    add_edge(graph, 5, 2);

    add_edge(graph, 4, 5);
    add_edge(graph, 5, 4);

    dfs(graph, 0);

    free_graph(graph);

    return 0;
}