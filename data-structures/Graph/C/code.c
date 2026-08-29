#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
    int vertex;
    struct Edge *next;
} Edge;

typedef struct Vertex
{
    int value;
    Edge *adjacency;
    struct Vertex *next;
} Vertex;

typedef struct Graph
{
    Vertex *vertices;
    int size;
} Graph;

Graph *create_graph(void)
{
    Graph *graph = malloc(sizeof(Graph));

    if (graph == NULL)
    {
        return NULL;
    }

    graph->vertices = NULL;
    graph->size = 0;

    return graph;
}

Vertex *find_vertex(const Graph *graph, int value)
{
    Vertex *current = graph->vertices;

    while (current != NULL)
    {
        if (current->value == value)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

Edge *find_edge(const Vertex *vertex, int destination)
{
    Edge *current = vertex->adjacency;

    while (current != NULL)
    {
        if (current->vertex == destination)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void add_vertex(Graph *graph, int vertex)
{
    if (find_vertex(graph, vertex) != NULL)
    {
        return;
    }

    Vertex *new_vertex = malloc(sizeof(Vertex));

    if (new_vertex == NULL)
    {
        return;
    }

    new_vertex->value = vertex;
    new_vertex->adjacency = NULL;

    new_vertex->next = graph->vertices;
    graph->vertices = new_vertex;

    graph->size++;
}

void add_edge(Graph *graph, int source, int destination)
{
    Vertex *source_vertex = find_vertex(graph, source);
    Vertex *destination_vertex = find_vertex(graph, destination);

    if (source_vertex == NULL || destination_vertex == NULL)
    {
        return;
    }

    if (find_edge(source_vertex, destination) != NULL)
    {
        return;
    }

    Edge *source_edge = malloc(sizeof(Edge));

    if (source_edge == NULL)
    {
        return;
    }

    source_edge->vertex = destination;
    source_edge->next = source_vertex->adjacency;
    source_vertex->adjacency = source_edge;

    if (source != destination)
    {
        Edge *destination_edge = malloc(sizeof(Edge));

        if (destination_edge == NULL)
        {
            source_vertex->adjacency = source_edge->next;
            free(source_edge);
            return;
        }

        destination_edge->vertex = source;
        destination_edge->next = destination_vertex->adjacency;
        destination_vertex->adjacency = destination_edge;
    }
}

void remove_edge(Graph *graph, int source, int destination)
{
    Vertex *source_vertex = find_vertex(graph, source);
    Vertex *destination_vertex = find_vertex(graph, destination);

    if (source_vertex == NULL || destination_vertex == NULL)
    {
        return;
    }

    Edge *current = source_vertex->adjacency;
    Edge *previous = NULL;

    while (current != NULL)
    {
        if (current->vertex == destination)
        {
            if (previous == NULL)
            {
                source_vertex->adjacency = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            break;
        }

        previous = current;
        current = current->next;
    }

    if (source == destination)
    {
        return;
    }

    current = destination_vertex->adjacency;
    previous = NULL;

    while (current != NULL)
    {
        if (current->vertex == source)
        {
            if (previous == NULL)
            {
                destination_vertex->adjacency = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            break;
        }

        previous = current;
        current = current->next;
    }
}

int contains_edge(
    const Graph *graph,
    int source,
    int destination
)
{
    Vertex *source_vertex = find_vertex(graph, source);

    if (source_vertex == NULL)
    {
        return 0;
    }

    return find_edge(source_vertex, destination) != NULL;
}

int vertex_index(const Graph *graph, int value)
{
    Vertex *current = graph->vertices;
    int index = 0;

    while (current != NULL)
    {
        if (current->value == value)
        {
            return index;
        }

        current = current->next;
        index++;
    }

    return -1;
}

Vertex *vertex_at(const Graph *graph, int index)
{
    Vertex *current = graph->vertices;

    for (int i = 0; current != NULL && i < index; i++)
    {
        current = current->next;
    }

    return current;
}

void bfs(const Graph *graph, int start)
{
    Vertex *start_vertex = find_vertex(graph, start);

    if (start_vertex == NULL)
    {
        return;
    }

    int *queue = malloc(graph->size * sizeof(int));
    int *visited = calloc(graph->size, sizeof(int));

    if (queue == NULL || visited == NULL)
    {
        free(queue);
        free(visited);
        return;
    }

    int front = 0;
    int rear = 0;

    int start_index = vertex_index(graph, start);

    queue[rear++] = start;
    visited[start_index] = 1;

    while (front < rear)
    {
        int current_value = queue[front++];

        printf("%d ", current_value);

        Vertex *current_vertex =
            find_vertex(graph, current_value);

        Edge *edge = current_vertex->adjacency;

        while (edge != NULL)
        {
            int index = vertex_index(graph, edge->vertex);

            if (index != -1 && !visited[index])
            {
                visited[index] = 1;
                queue[rear++] = edge->vertex;
            }

            edge = edge->next;
        }
    }

    printf("\n");

    free(queue);
    free(visited);
}

void dfs_recursive(
    const Graph *graph,
    int current,
    int *visited
)
{
    int index = vertex_index(graph, current);

    if (index == -1 || visited[index])
    {
        return;
    }

    visited[index] = 1;

    printf("%d ", current);

    Vertex *vertex = find_vertex(graph, current);
    Edge *edge = vertex->adjacency;

    while (edge != NULL)
    {
        dfs_recursive(graph, edge->vertex, visited);

        edge = edge->next;
    }
}

void dfs(const Graph *graph, int start)
{
    if (find_vertex(graph, start) == NULL)
    {
        return;
    }

    int *visited = calloc(graph->size, sizeof(int));

    if (visited == NULL)
    {
        return;
    }

    dfs_recursive(graph, start, visited);

    printf("\n");

    free(visited);
}

void free_graph(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }

    Vertex *vertex = graph->vertices;

    while (vertex != NULL)
    {
        Vertex *next_vertex = vertex->next;

        Edge *edge = vertex->adjacency;

        while (edge != NULL)
        {
            Edge *next_edge = edge->next;

            free(edge);

            edge = next_edge;
        }

        free(vertex);

        vertex = next_vertex;
    }

    free(graph);
}

int main(void)
{
    Graph *graph = create_graph();

    if (graph == NULL)
    {
        return 1;
    }

    add_vertex(graph, 1);
    add_vertex(graph, 2);
    add_vertex(graph, 3);
    add_vertex(graph, 4);
    add_vertex(graph, 5);

    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 5);

    printf("BFS: ");
    bfs(graph, 1);

    printf("DFS: ");
    dfs(graph, 1);

    printf(
        "Edge 1-3: %s\n",
        contains_edge(graph, 1, 3)
            ? "true"
            : "false"
    );

    remove_edge(graph, 1, 3);

    printf(
        "Edge 1-3 after removal: %s\n",
        contains_edge(graph, 1, 3)
            ? "true"
            : "false"
    );

    free_graph(graph);

    return 0;
}