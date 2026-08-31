#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define INF INT_MAX

typedef struct Edge
{
    int source;
    int destination;
    int weight;
} Edge;

typedef struct Graph
{
    int vertices;
    int directed;
    int **matrix;
} Graph;

Graph *create_graph(int vertices, int directed)
{
    Graph *graph = malloc(sizeof(Graph));

    if (graph == NULL)
    {
        return NULL;
    }

    graph->vertices = vertices;
    graph->directed = directed;

    graph->matrix = malloc(
        vertices * sizeof(int *)
    );

    if (graph->matrix == NULL)
    {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < vertices; i++)
    {
        graph->matrix[i] = malloc(
            vertices * sizeof(int)
        );

        if (graph->matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(graph->matrix[j]);
            }

            free(graph->matrix);
            free(graph);

            return NULL;
        }

        for (int j = 0; j < vertices; j++)
        {
            graph->matrix[i][j] = INF;
        }

        graph->matrix[i][i] = 0;
    }

    return graph;
}

void add_edge(
    Graph *graph,
    int source,
    int destination,
    int weight
)
{
    graph->matrix[source][destination] = weight;

    if (!graph->directed)
    {
        graph->matrix[destination][source] = weight;
    }
}

void destroy_graph(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        free(graph->matrix[i]);
    }

    free(graph->matrix);
    free(graph);
}

typedef struct Queue
{
    int *data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue *create_queue(int capacity)
{
    Queue *queue = malloc(sizeof(Queue));

    if (queue == NULL)
    {
        return NULL;
    }

    queue->data = malloc(
        capacity * sizeof(int)
    );

    if (queue->data == NULL)
    {
        free(queue);
        return NULL;
    }

    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;

    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (queue->rear < queue->capacity)
    {
        queue->data[queue->rear++] = value;
    }
}

int dequeue(Queue *queue)
{
    if (queue->front >= queue->rear)
    {
        return -1;
    }

    return queue->data[queue->front++];
}

bool queue_empty(Queue *queue)
{
    return queue->front >= queue->rear;
}

void destroy_queue(Queue *queue)
{
    if (queue == NULL)
    {
        return;
    }

    free(queue->data);
    free(queue);
}

int connected_components(Graph *graph)
{
    int n = graph->vertices;

    bool *visited = calloc(
        n,
        sizeof(bool)
    );

    if (visited == NULL)
    {
        return -1;
    }

    int components = 0;

    for (int start = 0; start < n; start++)
    {
        if (visited[start])
        {
            continue;
        }

        components++;

        Queue *queue = create_queue(n);

        if (queue == NULL)
        {
            free(visited);
            return -1;
        }

        visited[start] = true;
        enqueue(queue, start);

        while (!queue_empty(queue))
        {
            int current = dequeue(queue);

            for (int neighbor = 0;
                 neighbor < n;
                 neighbor++)
            {
                if (
                    graph->matrix[current][neighbor] != INF &&
                    current != neighbor &&
                    !visited[neighbor]
                )
                {
                    visited[neighbor] = true;
                    enqueue(queue, neighbor);
                }
            }
        }

        destroy_queue(queue);
    }

    free(visited);

    return components;
}

bool has_cycle_undirected_dfs(
    Graph *graph,
    int current,
    int parent,
    bool *visited
)
{
    visited[current] = true;

    for (int neighbor = 0;
         neighbor < graph->vertices;
         neighbor++)
    {
        if (
            neighbor == current ||
            graph->matrix[current][neighbor] == INF
        )
        {
            continue;
        }

        if (!visited[neighbor])
        {
            if (
                has_cycle_undirected_dfs(
                    graph,
                    neighbor,
                    current,
                    visited
                )
            )
            {
                return true;
            }
        }
        else if (neighbor != parent)
        {
            return true;
        }
    }

    return false;
}

bool has_cycle_undirected(Graph *graph)
{
    bool *visited = calloc(
        graph->vertices,
        sizeof(bool)
    );

    if (visited == NULL)
    {
        return false;
    }

    for (int i = 0;
         i < graph->vertices;
         i++)
    {
        if (!visited[i])
        {
            if (
                has_cycle_undirected_dfs(
                    graph,
                    i,
                    -1,
                    visited
                )
            )
            {
                free(visited);
                return true;
            }
        }
    }

    free(visited);

    return false;
}

bool has_cycle_directed_dfs(
    Graph *graph,
    int current,
    bool *visited,
    bool *recursion_stack
)
{
    visited[current] = true;
    recursion_stack[current] = true;

    for (int neighbor = 0;
         neighbor < graph->vertices;
         neighbor++)
    {
        if (
            graph->matrix[current][neighbor] == INF ||
            current == neighbor
        )
        {
            continue;
        }

        if (!visited[neighbor])
        {
            if (
                has_cycle_directed_dfs(
                    graph,
                    neighbor,
                    visited,
                    recursion_stack
                )
            )
            {
                return true;
            }
        }
        else if (recursion_stack[neighbor])
        {
            return true;
        }
    }

    recursion_stack[current] = false;

    return false;
}

bool has_cycle_directed(Graph *graph)
{
    bool *visited = calloc(
        graph->vertices,
        sizeof(bool)
    );

    bool *recursion_stack = calloc(
        graph->vertices,
        sizeof(bool)
    );

    if (
        visited == NULL ||
        recursion_stack == NULL
    )
    {
        free(visited);
        free(recursion_stack);
        return false;
    }

    for (int i = 0;
         i < graph->vertices;
         i++)
    {
        if (!visited[i])
        {
            if (
                has_cycle_directed_dfs(
                    graph,
                    i,
                    visited,
                    recursion_stack
                )
            )
            {
                free(visited);
                free(recursion_stack);
                return true;
            }
        }
    }

    free(visited);
    free(recursion_stack);

    return false;
}

bool topological_dfs(
    Graph *graph,
    int current,
    int *state,
    int *result,
    int *index
)
{

    state[current] = 1;

    for (int neighbor = 0;
         neighbor < graph->vertices;
         neighbor++)
    {
        if (
            graph->matrix[current][neighbor] == INF ||
            current == neighbor
        )
        {
            continue;
        }

        if (state[neighbor] == 1)
        {
            return false;
        }

        if (state[neighbor] == 0)
        {
            if (
                !topological_dfs(
                    graph,
                    neighbor,
                    state,
                    result,
                    index
                )
            )
            {
                return false;
            }
        }
    }

    state[current] = 2;

    result[(*index)--] = current;

    return true;
}

bool topological_sort_dfs(
    Graph *graph,
    int *result
)
{
    int n = graph->vertices;

    int *state = calloc(
        n,
        sizeof(int)
    );

    if (state == NULL)
    {
        return false;
    }

    int index = n - 1;

    for (int i = 0; i < n; i++)
    {
        if (state[i] == 0)
        {
            if (
                !topological_dfs(
                    graph,
                    i,
                    state,
                    result,
                    &index
                )
            )
            {
                free(state);
                return false;
            }
        }
    }

    free(state);

    return true;
}

bool topological_sort_kahn(
    Graph *graph,
    int *result
)
{
    int n = graph->vertices;

    int *indegree = calloc(
        n,
        sizeof(int)
    );

    if (indegree == NULL)
    {
        return false;
    }

    for (int source = 0;
         source < n;
         source++)
    {
        for (int destination = 0;
             destination < n;
             destination++)
        {
            if (
                graph->matrix[source][destination] != INF &&
                source != destination
            )
            {
                indegree[destination]++;
            }
        }
    }

    Queue *queue = create_queue(n);

    if (queue == NULL)
    {
        free(indegree);
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            enqueue(queue, i);
        }
    }

    int count = 0;

    while (!queue_empty(queue))
    {
        int current = dequeue(queue);

        result[count++] = current;

        for (int neighbor = 0;
             neighbor < n;
             neighbor++)
        {
            if (
                graph->matrix[current][neighbor] != INF &&
                current != neighbor
            )
            {
                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                {
                    enqueue(queue, neighbor);
                }
            }
        }
    }

    destroy_queue(queue);
    free(indegree);

    return count == n;
}

typedef struct HeapNode
{
    int vertex;
    int distance;
} HeapNode;

typedef struct MinHeap
{
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap *create_min_heap(int capacity)
{
    MinHeap *heap = malloc(
        sizeof(MinHeap)
    );

    if (heap == NULL)
    {
        return NULL;
    }

    heap->data = malloc(
        capacity * sizeof(HeapNode)
    );

    if (heap->data == NULL)
    {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void heap_swap(
    HeapNode *a,
    HeapNode *b
)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(
    MinHeap *heap,
    int vertex,
    int distance
)
{
    if (heap->size >= heap->capacity)
    {
        return;
    }

    int index = heap->size++;

    heap->data[index].vertex = vertex;
    heap->data[index].distance = distance;

    while (index > 0)
    {
        int parent =
            (index - 1) / 2;

        if (
            heap->data[parent].distance <=
            heap->data[index].distance
        )
        {
            break;
        }

        heap_swap(
            &heap->data[parent],
            &heap->data[index]
        );

        index = parent;
    }
}

HeapNode heap_pop(MinHeap *heap)
{
    HeapNode empty = {
        -1,
        INF
    };

    if (heap->size == 0)
    {
        return empty;
    }

    HeapNode result =
        heap->data[0];

    heap->size--;

    if (heap->size > 0)
    {
        heap->data[0] =
            heap->data[heap->size];

        int index = 0;

        while (true)
        {
            int left =
                index * 2 + 1;

            int right =
                index * 2 + 2;

            int smallest = index;

            if (
                left < heap->size &&
                heap->data[left].distance <
                heap->data[smallest].distance
            )
            {
                smallest = left;
            }

            if (
                right < heap->size &&
                heap->data[right].distance <
                heap->data[smallest].distance
            )
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }

            heap_swap(
                &heap->data[index],
                &heap->data[smallest]
            );

            index = smallest;
        }
    }

    return result;
}

void destroy_min_heap(MinHeap *heap)
{
    if (heap == NULL)
    {
        return;
    }

    free(heap->data);
    free(heap);
}

void dijkstra(
    Graph *graph,
    int source,
    int *distance
)
{
    int n = graph->vertices;

    bool *visited = calloc(
        n,
        sizeof(bool)
    );

    MinHeap *heap =
        create_min_heap(n * n);

    if (
        visited == NULL ||
        heap == NULL
    )
    {
        free(visited);
        destroy_min_heap(heap);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
    }

    distance[source] = 0;

    heap_push(heap, source, 0);

    while (heap->size > 0)
    {
        HeapNode node =
            heap_pop(heap);

        int current = node.vertex;

        if (visited[current])
        {
            continue;
        }

        visited[current] = true;

        for (int neighbor = 0;
             neighbor < n;
             neighbor++)
        {
            int weight =
                graph->matrix[current][neighbor];

            if (
                weight == INF ||
                current == neighbor
            )
            {
                continue;
            }

            if (weight < 0)
            {
                continue;
            }

            if (
                distance[current] != INF &&
                distance[current] + weight <
                distance[neighbor]
            )
            {
                distance[neighbor] =
                    distance[current] + weight;

                heap_push(
                    heap,
                    neighbor,
                    distance[neighbor]
                );
            }
        }
    }

    free(visited);
    destroy_min_heap(heap);
}

bool bellman_ford(
    Graph *graph,
    int source,
    int *distance
)
{
    int n = graph->vertices;

    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
    }

    distance[source] = 0;

    for (int iteration = 0;
         iteration < n - 1;
         iteration++)
    {
        bool changed = false;

        for (int u = 0; u < n; u++)
        {
            if (distance[u] == INF)
            {
                continue;
            }

            for (int v = 0; v < n; v++)
            {
                int weight =
                    graph->matrix[u][v];

                if (
                    weight == INF ||
                    u == v
                )
                {
                    continue;
                }

                if (
                    distance[u] + weight <
                    distance[v]
                )
                {
                    distance[v] =
                        distance[u] + weight;

                    changed = true;
                }
            }
        }

        if (!changed)
        {
            break;
        }
    }

    for (int u = 0; u < n; u++)
    {
        if (distance[u] == INF)
        {
            continue;
        }

        for (int v = 0; v < n; v++)
        {
            int weight =
                graph->matrix[u][v];

            if (
                weight == INF ||
                u == v
            )
            {
                continue;
            }

            if (
                distance[u] + weight <
                distance[v]
            )
            {
                return false;
            }
        }
    }

    return true;
}

void floyd_warshall(
    Graph *graph,
    int **distance
)
{
    int n = graph->vertices;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] =
                graph->matrix[i][j];
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (distance[i][k] == INF)
            {
                continue;
            }

            for (int j = 0; j < n; j++)
            {
                if (distance[k][j] == INF)
                {
                    continue;
                }

                if (
                    distance[i][k] +
                    distance[k][j] <
                    distance[i][j]
                )
                {
                    distance[i][j] =
                        distance[i][k] +
                        distance[k][j];
                }
            }
        }
    }
}

bool has_negative_cycle(
    Graph *graph
)
{
    int n = graph->vertices;

    int **distance = malloc(
        n * sizeof(int *)
    );

    if (distance == NULL)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        distance[i] = malloc(
            n * sizeof(int)
        );

        if (distance[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(distance[j]);
            }

            free(distance);
            return false;
        }
    }

    floyd_warshall(
        graph,
        distance
    );

    bool negative_cycle = false;

    for (int i = 0; i < n; i++)
    {
        if (distance[i][i] < 0)
        {
            negative_cycle = true;
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        free(distance[i]);
    }

    free(distance);

    return negative_cycle;
}

int prim_mst(
    Graph *graph,
    Edge *mst
)
{
    int n = graph->vertices;

    int *key = malloc(
        n * sizeof(int)
    );

    int *parent = malloc(
        n * sizeof(int)
    );

    bool *in_mst = calloc(
        n,
        sizeof(bool)
    );

    if (
        key == NULL ||
        parent == NULL ||
        in_mst == NULL
    )
    {
        free(key);
        free(parent);
        free(in_mst);
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        key[i] = INF;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0;
         count < n;
         count++)
    {
        int current = -1;

        for (int v = 0; v < n; v++)
        {
            if (
                !in_mst[v] &&
                (current == -1 ||
                 key[v] < key[current])
            )
            {
                current = v;
            }
        }

        if (
            current == -1 ||
            key[current] == INF
        )
        {
            free(key);
            free(parent);
            free(in_mst);
            return -1;
        }

        in_mst[current] = true;

        for (int neighbor = 0;
             neighbor < n;
             neighbor++)
        {
            int weight =
                graph->matrix[current][neighbor];

            if (
                weight != INF &&
                current != neighbor &&
                !in_mst[neighbor] &&
                weight < key[neighbor]
            )
            {
                key[neighbor] = weight;
                parent[neighbor] = current;
            }
        }
    }

    for (int v = 1; v < n; v++)
    {
        mst[v - 1].source =
            parent[v];

        mst[v - 1].destination =
            v;

        mst[v - 1].weight =
            key[v];
    }

    free(key);
    free(parent);
    free(in_mst);

    return n - 1;
}

typedef struct DisjointSet
{
    int *parent;
    int *rank;
    int size;
} DisjointSet;

DisjointSet *create_disjoint_set(int size)
{
    DisjointSet *set = malloc(
        sizeof(DisjointSet)
    );

    if (set == NULL)
    {
        return NULL;
    }

    set->parent = malloc(
        size * sizeof(int)
    );

    set->rank = calloc(
        size,
        sizeof(int)
    );

    if (
        set->parent == NULL ||
        set->rank == NULL
    )
    {
        free(set->parent);
        free(set->rank);
        free(set);
        return NULL;
    }

    set->size = size;

    for (int i = 0; i < size; i++)
    {
        set->parent[i] = i;
    }

    return set;
}

int find_set(
    DisjointSet *set,
    int value
)
{
    if (set->parent[value] != value)
    {
        set->parent[value] =
            find_set(
                set,
                set->parent[value]
            );
    }

    return set->parent[value];
}

void union_sets(
    DisjointSet *set,
    int a,
    int b
)
{
    a = find_set(set, a);
    b = find_set(set, b);

    if (a == b)
    {
        return;
    }

    if (set->rank[a] <
        set->rank[b])
    {
        set->parent[a] = b;
    }
    else if (
        set->rank[a] >
        set->rank[b]
    )
    {
        set->parent[b] = a;
    }
    else
    {
        set->parent[b] = a;
        set->rank[a]++;
    }
}

void destroy_disjoint_set(
    DisjointSet *set
)
{
    if (set == NULL)
    {
        return;
    }

    free(set->parent);
    free(set->rank);
    free(set);
}

int compare_edges(
    const void *a,
    const void *b
)
{
    const Edge *edge_a = a;
    const Edge *edge_b = b;

    return edge_a->weight -
           edge_b->weight;
}

int kruskal_mst(
    Graph *graph,
    Edge *mst
)
{
    int n = graph->vertices;

    int max_edges =
        n * (n - 1) / 2;

    Edge *edges = malloc(
        max_edges * sizeof(Edge)
    );

    if (edges == NULL)
    {
        return -1;
    }

    int edge_count = 0;

    for (int u = 0; u < n; u++)
    {
        for (int v = u + 1;
             v < n;
             v++)
        {
            if (
                graph->matrix[u][v] != INF
            )
            {
                edges[edge_count].source = u;
                edges[edge_count].destination = v;
                edges[edge_count].weight =
                    graph->matrix[u][v];

                edge_count++;
            }
        }
    }

    qsort(
        edges,
        edge_count,
        sizeof(Edge),
        compare_edges
    );

    DisjointSet *set =
        create_disjoint_set(n);

    if (set == NULL)
    {
        free(edges);
        return -1;
    }

    int selected = 0;

    for (int i = 0;
         i < edge_count &&
         selected < n - 1;
         i++)
    {
        Edge edge = edges[i];

        if (
            find_set(
                set,
                edge.source
            ) !=
            find_set(
                set,
                edge.destination
            )
        )
        {
            mst[selected++] = edge;

            union_sets(
                set,
                edge.source,
                edge.destination
            );
        }
    }

    destroy_disjoint_set(set);
    free(edges);

    return selected == n - 1
        ? selected
        : -1;
}

void fill_order(
    Graph *graph,
    int current,
    bool *visited,
    int *stack,
    int *top
)
{
    visited[current] = true;

    for (int neighbor = 0;
         neighbor < graph->vertices;
         neighbor++)
    {
        if (
            graph->matrix[current][neighbor] != INF &&
            current != neighbor &&
            !visited[neighbor]
        )
        {
            fill_order(
                graph,
                neighbor,
                visited,
                stack,
                top
            );
        }
    }

    stack[(*top)++] = current;
}

Graph *transpose_graph(Graph *graph)
{
    Graph *transpose =
        create_graph(
            graph->vertices,
            1
        );

    if (transpose == NULL)
    {
        return NULL;
    }

    for (int i = 0;
         i < graph->vertices;
         i++)
    {
        for (int j = 0;
             j < graph->vertices;
             j++)
        {
            if (
                graph->matrix[i][j] != INF &&
                i != j
            )
            {
                add_edge(
                    transpose,
                    j,
                    i,
                    graph->matrix[i][j]
                );
            }
        }
    }

    return transpose;
}

void collect_component(
    Graph *graph,
    int current,
    bool *visited,
    int *component,
    int *size
)
{
    visited[current] = true;

    component[(*size)++] = current;

    for (int neighbor = 0;
         neighbor < graph->vertices;
         neighbor++)
    {
        if (
            graph->matrix[current][neighbor] != INF &&
            current != neighbor &&
            !visited[neighbor]
        )
        {
            collect_component(
                graph,
                neighbor,
                visited,
                component,
                size
            );
        }
    }
}

int strongly_connected_components(
    Graph *graph,
    int **components,
    int *component_sizes
)
{
    int n = graph->vertices;

    bool *visited = calloc(
        n,
        sizeof(bool)
    );

    int *stack = malloc(
        n * sizeof(int)
    );

    if (
        visited == NULL ||
        stack == NULL
    )
    {
        free(visited);
        free(stack);
        return -1;
    }

    int top = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            fill_order(
                graph,
                i,
                visited,
                stack,
                &top
            );
        }
    }

    Graph *transpose =
        transpose_graph(graph);

    if (transpose == NULL)
    {
        free(visited);
        free(stack);
        return -1;
    }

    memset(
        visited,
        0,
        n * sizeof(bool)
    );

    int count = 0;

    while (top > 0)
    {
        int vertex =
            stack[--top];

        if (!visited[vertex])
        {
            int size = 0;

            collect_component(
                transpose,
                vertex,
                visited,
                components[count],
                &size
            );

            component_sizes[count] =
                size;

            count++;
        }
    }

    destroy_graph(transpose);
    free(visited);
    free(stack);

    return count;
}

typedef struct Point
{
    int row;
    int column;
} Point;

int manhattan_distance(
    Point a,
    Point b
)
{
    int row_difference =
        abs(a.row - b.row);

    int column_difference =
        abs(a.column - b.column);

    return row_difference +
           column_difference;
}

bool valid_cell(
    int **grid,
    int rows,
    int columns,
    int row,
    int column
)
{
    return (
        row >= 0 &&
        row < rows &&
        column >= 0 &&
        column < columns &&
        grid[row][column] == 0
    );
}

void print_path(
    Point **parent,
    Point start,
    Point goal,
    int rows,
    int columns
)
{
    char **path = malloc(
        rows * sizeof(char *)
    );

    if (path == NULL)
    {
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        path[i] = malloc(
            columns * sizeof(char)
        );

        if (path[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(path[j]);
            }

            free(path);
            return;
        }

        for (int j = 0; j < columns; j++)
        {
            path[i][j] = '.';
        }
    }

    Point current = goal;

    while (
        current.row != start.row ||
        current.column != start.column
    )
    {
        path[current.row][current.column] = '*';

        Point previous =
            parent[current.row][current.column];

        if (
            previous.row == -1 ||
            previous.column == -1
        )
        {
            break;
        }

        current = previous;
    }

    path[start.row][start.column] = 'S';
    path[goal.row][goal.column] = 'G';

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf(
                "%c ",
                path[i][j]
            );
        }

        printf("\n");
    }

    for (int i = 0; i < rows; i++)
    {
        free(path[i]);
    }

    free(path);
}

bool a_star(
    int **grid,
    int rows,
    int columns,
    Point start,
    Point goal
)
{
    int **g_cost = malloc(
        rows * sizeof(int *)
    );

    Point **parent = malloc(
        rows * sizeof(Point *)
    );

    bool **closed = malloc(
        rows * sizeof(bool *)
    );

    if (
        g_cost == NULL ||
        parent == NULL ||
        closed == NULL
    )
    {
        free(g_cost);
        free(parent);
        free(closed);
        return false;
    }

    for (int i = 0; i < rows; i++)
    {
        g_cost[i] = malloc(
            columns * sizeof(int)
        );

        parent[i] = malloc(
            columns * sizeof(Point)
        );

        closed[i] = calloc(
            columns,
            sizeof(bool)
        );

        if (
            g_cost[i] == NULL ||
            parent[i] == NULL ||
            closed[i] == NULL
        )
        {
            for (int j = 0; j <= i; j++)
            {
                free(g_cost[j]);
                free(parent[j]);
                free(closed[j]);
            }

            free(g_cost);
            free(parent);
            free(closed);

            return false;
        }

        for (int j = 0; j < columns; j++)
        {
            g_cost[i][j] = INF;

            parent[i][j].row = -1;
            parent[i][j].column = -1;
        }
    }

    int max_nodes =
        rows * columns;

    Point *open = malloc(
        max_nodes * sizeof(Point)
    );

    if (open == NULL)
    {
        for (int i = 0; i < rows; i++)
        {
            free(g_cost[i]);
            free(parent[i]);
            free(closed[i]);
        }

        free(g_cost);
        free(parent);
        free(closed);

        return false;
    }

    int open_size = 0;

    g_cost[start.row][start.column] = 0;

    open[open_size++] = start;

    int directions[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    bool found = false;

    while (open_size > 0)
    {

        int best_index = 0;

        int best_f =
            g_cost[
                open[0].row
            ][
                open[0].column
            ] +
            manhattan_distance(
                open[0],
                goal
            );

        for (int i = 1;
             i < open_size;
             i++)
        {
            int f =
                g_cost[
                    open[i].row
                ][
                    open[i].column
                ] +
                manhattan_distance(
                    open[i],
                    goal
                );

            if (f < best_f)
            {
                best_f = f;
                best_index = i;
            }
        }

        Point current =
            open[best_index];

        open[best_index] =
            open[--open_size];

        if (
            current.row == goal.row &&
            current.column == goal.column
        )
        {
            found = true;
            break;
        }

        if (closed[current.row][current.column])
        {
            continue;
        }

        closed[current.row][current.column] = true;

        for (int direction = 0;
             direction < 4;
             direction++)
        {
            int new_row =
                current.row +
                directions[direction][0];

            int new_column =
                current.column +
                directions[direction][1];

            if (
                !valid_cell(
                    grid,
                    rows,
                    columns,
                    new_row,
                    new_column
                )
            )
            {
                continue;
            }

            if (
                closed[new_row][new_column]
            )
            {
                continue;
            }

            int new_g =
                g_cost[current.row][current.column]
                + 1;

            if (
                new_g <
                g_cost[new_row][new_column]
            )
            {
                g_cost[new_row][new_column] =
                    new_g;

                parent[new_row][new_column] =
                    current;

                open[open_size++] = (
                    Point
                ){
                    new_row,
                    new_column
                };
            }
        }
    }

    if (found)
    {
        printf(
            "\nA* path:\n"
        );

        print_path(
            parent,
            start,
            goal,
            rows,
            columns
        );
    }

    for (int i = 0; i < rows; i++)
    {
        free(g_cost[i]);
        free(parent[i]);
        free(closed[i]);
    }

    free(g_cost);
    free(parent);
    free(closed);
    free(open);

    return found;
}

void print_distances(
    const int *distance,
    int size
)
{
    for (int i = 0; i < size; i++)
    {
        if (distance[i] == INF)
        {
            printf(
                "%d: unreachable\n",
                i
            );
        }
        else
        {
            printf(
                "%d: %d\n",
                i,
                distance[i]
            );
        }
    }
}

void print_edges(
    const Edge *edges,
    int count
)
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        printf(
            "%d -- %d (%d)\n",
            edges[i].source,
            edges[i].destination,
            edges[i].weight
        );

        total += edges[i].weight;
    }

    printf(
        "Total weight: %d\n",
        total
    );
}

void print_order(
    const int *order,
    int size
)
{
    for (int i = 0; i < size; i++)
    {
        printf(
            "%d",
            order[i]
        );

        if (i < size - 1)
        {
            printf(" -> ");
        }
    }

    printf("\n");
}

int main(void)
{

    Graph *components_graph =
        create_graph(6, 0);

    add_edge(
        components_graph,
        0, 1, 1
    );

    add_edge(
        components_graph,
        1, 2, 1
    );

    add_edge(
        components_graph,
        3, 4, 1
    );

    add_edge(
        components_graph,
        4, 5, 1
    );

    printf(
        "Connected Components: %d\n",
        connected_components(
            components_graph
        )
    );

    destroy_graph(
        components_graph
    );

    Graph *cycle_graph =
        create_graph(3, 0);

    add_edge(
        cycle_graph,
        0, 1, 1
    );

    add_edge(
        cycle_graph,
        1, 2, 1
    );

    add_edge(
        cycle_graph,
        2, 0, 1
    );

    printf(
        "Undirected Cycle: %s\n",
        has_cycle_undirected(
            cycle_graph
        )
            ? "true"
            : "false"
    );

    destroy_graph(
        cycle_graph
    );

    Graph *directed_cycle =
        create_graph(3, 1);

    add_edge(
        directed_cycle,
        0, 1, 1
    );

    add_edge(
        directed_cycle,
        1, 2, 1
    );

    add_edge(
        directed_cycle,
        2, 0, 1
    );

    printf(
        "Directed Cycle: %s\n",
        has_cycle_directed(
            directed_cycle
        )
            ? "true"
            : "false"
    );

    destroy_graph(
        directed_cycle
    );

    Graph *dag =
        create_graph(6, 1);

    add_edge(dag, 5, 0, 1);
    add_edge(dag, 5, 2, 1);
    add_edge(dag, 4, 0, 1);
    add_edge(dag, 4, 1, 1);
    add_edge(dag, 2, 3, 1);
    add_edge(dag, 3, 1, 1);

    int order[6];

    printf(
        "\nTopological Sort (DFS): "
    );

    if (
        topological_sort_dfs(
            dag,
            order
        )
    )
    {
        print_order(
            order,
            6
        );
    }
    else
    {
        printf(
            "Cycle detected\n"
        );
    }

    printf(
        "Topological Sort (Kahn): "
    );

    if (
        topological_sort_kahn(
            dag,
            order
        )
    )
    {
        print_order(
            order,
            6
        );
    }
    else
    {
        printf(
            "Cycle detected\n"
        );
    }

    destroy_graph(dag);

    Graph *weighted =
        create_graph(6, 1);

    add_edge(weighted, 0, 1, 4);
    add_edge(weighted, 0, 2, 2);
    add_edge(weighted, 1, 2, 1);
    add_edge(weighted, 1, 3, 5);
    add_edge(weighted, 2, 3, 8);
    add_edge(weighted, 2, 4, 10);
    add_edge(weighted, 3, 4, 2);
    add_edge(weighted, 3, 5, 6);
    add_edge(weighted, 4, 5, 3);

    int distances[6];

    dijkstra(
        weighted,
        0,
        distances
    );

    printf(
        "\nDijkstra from vertex 0:\n"
    );

    print_distances(
        distances,
        6
    );

    Graph *bellman =
        create_graph(5, 1);

    add_edge(
        bellman,
        0, 1, 6
    );

    add_edge(
        bellman,
        0, 2, 7
    );

    add_edge(
        bellman,
        1, 2, 8
    );

    add_edge(
        bellman,
        1, 3, 5
    );

    add_edge(
        bellman,
        1, 4, -4
    );

    add_edge(
        bellman,
        2, 3, -3
    );

    add_edge(
        bellman,
        2, 4, 9
    );

    add_edge(
        bellman,
        3, 1, -2
    );

    add_edge(
        bellman,
        4, 0, 2
    );

    add_edge(
        bellman,
        4, 3, 7
    );

    int bellman_distances[5];

    bool no_negative_cycle =
        bellman_ford(
            bellman,
            0,
            bellman_distances
        );

    printf(
        "\nBellman-Ford from vertex 0:\n"
    );

    print_distances(
        bellman_distances,
        5
    );

    printf(
        "Negative cycle: %s\n",
        no_negative_cycle
            ? "false"
            : "true"
    );

    destroy_graph(bellman);

    int n = weighted->vertices;

    int **all_pairs = malloc(
        n * sizeof(int *)
    );

    for (int i = 0; i < n; i++)
    {
        all_pairs[i] = malloc(
            n * sizeof(int)
        );
    }

    floyd_warshall(
        weighted,
        all_pairs
    );

    printf(
        "\nFloyd-Warshall:\n"
    );

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (all_pairs[i][j] == INF)
            {
                printf(
                    "INF "
                );
            }
            else
            {
                printf(
                    "%d ",
                    all_pairs[i][j]
                );
            }
        }

        printf("\n");
    }

    printf(
        "Negative cycle: %s\n",
        has_negative_cycle(weighted)
            ? "true"
            : "false"
    );

    for (int i = 0; i < n; i++)
    {
        free(all_pairs[i]);
    }

    free(all_pairs);

    Graph *mst_graph =
        create_graph(6, 0);

    add_edge(mst_graph, 0, 1, 4);
    add_edge(mst_graph, 0, 2, 2);
    add_edge(mst_graph, 1, 2, 1);
    add_edge(mst_graph, 1, 3, 5);
    add_edge(mst_graph, 2, 3, 8);
    add_edge(mst_graph, 2, 4, 10);
    add_edge(mst_graph, 3, 4, 2);
    add_edge(mst_graph, 3, 5, 6);
    add_edge(mst_graph, 4, 5, 3);

    Edge prim_result[5];

    int prim_count =
        prim_mst(
            mst_graph,
            prim_result
        );

    printf(
        "\nPrim MST:\n"
    );

    if (prim_count > 0)
    {
        print_edges(
            prim_result,
            prim_count
        );
    }

    Edge kruskal_result[5];

    int kruskal_count =
        kruskal_mst(
            mst_graph,
            kruskal_result
        );

    printf(
        "\nKruskal MST:\n"
    );

    if (kruskal_count > 0)
    {
        print_edges(
            kruskal_result,
            kruskal_count
        );
    }

    destroy_graph(
        mst_graph
    );

    destroy_graph(
        weighted
    );

    Graph *scc_graph =
        create_graph(5, 1);

    add_edge(scc_graph, 0, 1, 1);
    add_edge(scc_graph, 1, 2, 1);
    add_edge(scc_graph, 2, 0, 1);
    add_edge(scc_graph, 1, 3, 1);
    add_edge(scc_graph, 3, 4, 1);
    add_edge(scc_graph, 4, 3, 1);

    int **components = malloc(
        5 * sizeof(int *)
    );

    int component_sizes[5];

    for (int i = 0; i < 5; i++)
    {
        components[i] = malloc(
            5 * sizeof(int)
        );
    }

    int component_count =
        strongly_connected_components(
            scc_graph,
            components,
            component_sizes
        );

    printf(
        "\nStrongly Connected Components:\n"
    );

    for (int i = 0;
         i < component_count;
         i++)
    {
        printf(
            "Component %d: ",
            i + 1
        );

        for (int j = 0;
             j < component_sizes[i];
             j++)
        {
            printf(
                "%d ",
                components[i][j]
            );
        }

        printf("\n");
    }

    for (int i = 0; i < 5; i++)
    {
        free(components[i]);
    }

    free(components);

    destroy_graph(scc_graph);

    int rows = 5;
    int columns = 6;

    int grid_data[5][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}
    };

    int **grid = malloc(
        rows * sizeof(int *)
    );

    for (int i = 0; i < rows; i++)
    {
        grid[i] = malloc(
            columns * sizeof(int)
        );

        for (int j = 0; j < columns; j++)
        {
            grid[i][j] =
                grid_data[i][j];
        }
    }

    Point start = {
        0,
        0
    };

    Point goal = {
        4,
        5
    };

    printf(
        "\nA* Search:\n"
    );

    if (
        !a_star(
            grid,
            rows,
            columns,
            start,
            goal
        )
    )
    {
        printf(
            "No path exists.\n"
        );
    }

    for (int i = 0; i < rows; i++)
    {
        free(grid[i]);
    }

    free(grid);

    return 0;
}