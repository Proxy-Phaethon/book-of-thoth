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
    node->next = graph->adjacency_list[from];
    graph->adjacency_list[from] = node;
}

void bfs(Graph *graph, int start)
{
    int *visited = calloc(graph->vertices, sizeof(int));
    int *queue = malloc(graph->vertices * sizeof(int));

    if (visited == NULL || queue == NULL)
    {
        free(visited);
        free(queue);
        return;
    }

    int front = 0;
    int rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear)
    {
        int current = queue[front++];

        printf("%d ", current);

        Node *neighbor = graph->adjacency_list[current];

        while (neighbor != NULL)
        {
            int vertex = neighbor->vertex;

            if (!visited[vertex])
            {
                visited[vertex] = 1;
                queue[rear++] = vertex;
            }

            neighbor = neighbor->next;
        }
    }

    printf("\n");

    free(visited);
    free(queue);
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
     * 0 ─── 1 ─── 3
     * │     │
     * │     └─── 4
     * │         │
     * 2 ────────┘
     * │
     * 5
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

    bfs(graph, 0);

    free_graph(graph);

    return 0;
}