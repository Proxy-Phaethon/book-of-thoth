#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int start;
    int finish;
} Activity;

void sort_activities(Activity *activities, int count)
{
    for (int i = 1; i < count; i++)
    {
        Activity key = activities[i];
        int j = i - 1;

        while (j >= 0 &&
               activities[j].finish > key.finish)
        {
            activities[j + 1] = activities[j];
            j--;
        }

        activities[j + 1] = key;
    }
}

int activity_selection(
    Activity *activities,
    int count
)
{
    if (count == 0)
    {
        return 0;
    }

    sort_activities(activities, count);

    int selected = 1;
    int last_finish = activities[0].finish;

    for (int i = 1; i < count; i++)
    {
        if (activities[i].start >= last_finish)
        {
            selected++;
            last_finish = activities[i].finish;
        }
    }

    return selected;
}

typedef struct
{
    double value;
    double weight;
} Item;

double item_ratio(Item item)
{
    return item.value / item.weight;
}

void sort_items(Item *items, int count)
{
    for (int i = 1; i < count; i++)
    {
        Item key = items[i];
        int j = i - 1;

        while (j >= 0 &&
               item_ratio(items[j]) <
               item_ratio(key))
        {
            items[j + 1] = items[j];
            j--;
        }

        items[j + 1] = key;
    }
}

double fractional_knapsack(
    Item *items,
    int count,
    double capacity
)
{
    sort_items(items, count);

    double total_value = 0.0;

    for (int i = 0; i < count; i++)
    {
        if (capacity <= 0)
        {
            break;
        }

        if (items[i].weight <= capacity)
        {
            total_value += items[i].value;
            capacity -= items[i].weight;
        }
        else
        {
            double fraction =
                capacity / items[i].weight;

            total_value +=
                items[i].value * fraction;

            capacity = 0;
        }
    }

    return total_value;
}

typedef struct
{
    char id;
    int deadline;
    int profit;
} Job;

void sort_jobs(Job *jobs, int count)
{
    for (int i = 1; i < count; i++)
    {
        Job key = jobs[i];
        int j = i - 1;

        while (j >= 0 &&
               jobs[j].profit < key.profit)
        {
            jobs[j + 1] = jobs[j];
            j--;
        }

        jobs[j + 1] = key;
    }
}

int job_sequencing(
    Job *jobs,
    int count,
    Job *selected
)
{
    if (count == 0)
    {
        return 0;
    }

    sort_jobs(jobs, count);

    int max_deadline = 0;

    for (int i = 0; i < count; i++)
    {
        if (jobs[i].deadline > max_deadline)
        {
            max_deadline = jobs[i].deadline;
        }
    }

    Job *slots =
        malloc(max_deadline * sizeof(Job));

    int *occupied =
        calloc(max_deadline, sizeof(int));

    if (slots == NULL || occupied == NULL)
    {
        free(slots);
        free(occupied);
        return 0;
    }

    int selected_count = 0;

    for (int i = 0; i < count; i++)
    {
        for (int slot = jobs[i].deadline - 1;
             slot >= 0;
             slot--)
        {
            if (!occupied[slot])
            {
                occupied[slot] = 1;
                slots[slot] = jobs[i];

                selected[selected_count++] =
                    jobs[i];

                break;
            }
        }
    }

    free(slots);
    free(occupied);

    return selected_count;
}

typedef struct HuffmanNode
{
    char character;
    int frequency;

    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

HuffmanNode *create_huffman_node(
    char character,
    int frequency
)
{
    HuffmanNode *node =
        malloc(sizeof(HuffmanNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void swap_nodes(
    HuffmanNode **a,
    HuffmanNode **b
)
{
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(
    HuffmanNode **heap,
    int size,
    int index
)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size &&
        heap[left]->frequency <
        heap[smallest]->frequency)
    {
        smallest = left;
    }

    if (right < size &&
        heap[right]->frequency <
        heap[smallest]->frequency)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap_nodes(
            &heap[index],
            &heap[smallest]
        );

        heapify(
            heap,
            size,
            smallest
        );
    }
}

void heap_insert(
    HuffmanNode **heap,
    int *size,
    HuffmanNode *node
)
{
    int index = (*size)++;

    heap[index] = node;

    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (heap[parent]->frequency <=
            heap[index]->frequency)
        {
            break;
        }

        swap_nodes(
            &heap[parent],
            &heap[index]
        );

        index = parent;
    }
}

HuffmanNode *heap_extract_min(
    HuffmanNode **heap,
    int *size
)
{
    if (*size == 0)
    {
        return NULL;
    }

    HuffmanNode *minimum = heap[0];

    heap[0] = heap[--(*size)];

    if (*size > 0)
    {
        heapify(heap, *size, 0);
    }

    return minimum;
}

void print_huffman_codes(
    HuffmanNode *root,
    int *code,
    int depth
)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL &&
        root->right == NULL)
    {
        printf("%c: ", root->character);

        for (int i = 0; i < depth; i++)
        {
            printf("%d", code[i]);
        }

        printf("\n");
        return;
    }

    code[depth] = 0;

    print_huffman_codes(
        root->left,
        code,
        depth + 1
    );

    code[depth] = 1;

    print_huffman_codes(
        root->right,
        code,
        depth + 1
    );
}

HuffmanNode *build_huffman_tree(
    const char *characters,
    const int *frequencies,
    int count
)
{
    if (count == 0)
    {
        return NULL;
    }

    HuffmanNode **heap =
        malloc(count * 2 * sizeof(HuffmanNode *));

    if (heap == NULL)
    {
        return NULL;
    }

    int size = 0;

    for (int i = 0; i < count; i++)
    {
        HuffmanNode *node =
            create_huffman_node(
                characters[i],
                frequencies[i]
            );

        if (node == NULL)
        {
            free(heap);
            return NULL;
        }

        heap_insert(&heap[0], &size, node);
    }

    while (size > 1)
    {
        HuffmanNode *left =
            heap_extract_min(&heap[0], &size);

        HuffmanNode *right =
            heap_extract_min(&heap[0], &size);

        HuffmanNode *parent =
            create_huffman_node(
                '\0',
                left->frequency +
                right->frequency
            );

        parent->left = left;
        parent->right = right;

        heap_insert(
            &heap[0],
            &size,
            parent
        );
    }

    HuffmanNode *root =
        heap_extract_min(&heap[0], &size);

    free(heap);

    return root;
}

void free_huffman_tree(HuffmanNode *root)
{
    if (root == NULL)
    {
        return;
    }

    free_huffman_tree(root->left);
    free_huffman_tree(root->right);

    free(root);
}

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct
{
    int source;
    int destination;
    int weight;
} Edge;

typedef struct
{
    int vertices;
    int adjacency[MAX_VERTICES][MAX_VERTICES];
} Graph;

/* ==================================================
 * 5. Kruskal's Algorithm
 * ================================================== */

void sort_edges(
    Edge *edges,
    int count
)
{
    for (int i = 1; i < count; i++)
    {
        Edge key = edges[i];
        int j = i - 1;

        while (j >= 0 &&
               edges[j].weight > key.weight)
        {
            edges[j + 1] = edges[j];
            j--;
        }

        edges[j + 1] = key;
    }
}

int find_parent(
    int *parent,
    int vertex
)
{
    if (parent[vertex] != vertex)
    {
        parent[vertex] =
            find_parent(
                parent,
                parent[vertex]
            );
    }

    return parent[vertex];
}

void union_sets(
    int *parent,
    int *rank,
    int a,
    int b
)
{
    int root_a =
        find_parent(parent, a);

    int root_b =
        find_parent(parent, b);

    if (root_a == root_b)
    {
        return;
    }

    if (rank[root_a] < rank[root_b])
    {
        parent[root_a] = root_b;
    }
    else if (rank[root_a] > rank[root_b])
    {
        parent[root_b] = root_a;
    }
    else
    {
        parent[root_b] = root_a;
        rank[root_a]++;
    }
}

int kruskal_mst(
    Edge *edges,
    int vertex_count,
    int edge_count,
    Edge *mst
)
{
    sort_edges(edges, edge_count);

    int *parent =
        malloc(vertex_count * sizeof(int));

    int *rank =
        calloc(vertex_count, sizeof(int));

    if (parent == NULL || rank == NULL)
    {
        free(parent);
        free(rank);
        return 0;
    }

    for (int i = 0; i < vertex_count; i++)
    {
        parent[i] = i;
    }

    int mst_count = 0;

    for (int i = 0;
         i < edge_count &&
         mst_count < vertex_count - 1;
         i++)
    {
        Edge edge = edges[i];

        int source_root =
            find_parent(
                parent,
                edge.source
            );

        int destination_root =
            find_parent(
                parent,
                edge.destination
            );

        if (source_root != destination_root)
        {
            mst[mst_count++] = edge;

            union_sets(
                parent,
                rank,
                edge.source,
                edge.destination
            );
        }
    }

    free(parent);
    free(rank);

    return mst_count;
}

int prim_mst(
    const Graph *graph,
    int start,
    Edge *mst
)
{
    int key[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int included[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->vertices; i++)
    {
        key[i] = INF;
        parent[i] = -1;
    }

    key[start] = 0;

    int mst_count = 0;

    for (int i = 0;
         i < graph->vertices;
         i++)
    {
        int minimum = INF;
        int vertex = -1;

        for (int v = 0;
             v < graph->vertices;
             v++)
        {
            if (!included[v] &&
                key[v] < minimum)
            {
                minimum = key[v];
                vertex = v;
            }
        }

        if (vertex == -1)
        {
            break;
        }

        included[vertex] = 1;

        if (parent[vertex] != -1)
        {
            mst[mst_count].source =
                parent[vertex];

            mst[mst_count].destination =
                vertex;

            mst[mst_count].weight =
                key[vertex];

            mst_count++;
        }

        for (int v = 0;
             v < graph->vertices;
             v++)
        {
            int weight =
                graph->adjacency[vertex][v];

            if (weight != 0 &&
                !included[v] &&
                weight < key[v])
            {
                key[v] = weight;
                parent[v] = vertex;
            }
        }
    }

    return mst_count;
}

void dijkstra(
    const Graph *graph,
    int source,
    int *distances
)
{
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->vertices; i++)
    {
        distances[i] = INF;
    }

    distances[source] = 0;

    for (int count = 0;
         count < graph->vertices;
         count++)
    {
        int minimum = INF;
        int vertex = -1;

        for (int v = 0;
             v < graph->vertices;
             v++)
        {
            if (!visited[v] &&
                distances[v] < minimum)
            {
                minimum = distances[v];
                vertex = v;
            }
        }

        if (vertex == -1)
        {
            break;
        }

        visited[vertex] = 1;

        for (int v = 0;
             v < graph->vertices;
             v++)
        {
            int weight =
                graph->adjacency[vertex][v];

            if (weight > 0 &&
                !visited[v] &&
                distances[vertex] != INF &&
                distances[vertex] + weight <
                distances[v])
            {
                distances[v] =
                    distances[vertex] + weight;
            }
        }
    }
}

void print_mst(
    const Edge *mst,
    int count
)
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        printf(
            "%d -- %d  (%d)\n",
            mst[i].source,
            mst[i].destination,
            mst[i].weight
        );

        total += mst[i].weight;
    }

    printf("Total weight: %d\n", total);
}

int main(void)
{

    Activity activities[] = {
        {1, 3},
        {2, 4},
        {3, 5},
        {5, 7},
        {8, 9},
        {5, 9}
    };

    int activity_count =
        sizeof(activities) /
        sizeof(activities[0]);

    printf(
        "Activity Selection: %d activities\n",
        activity_selection(
            activities,
            activity_count
        )
    );

    Item items[] = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    int item_count =
        sizeof(items) /
        sizeof(items[0]);

    printf(
        "Fractional Knapsack: %.2f\n",
        fractional_knapsack(
            items,
            item_count,
            50
        )
    );

    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int job_count =
        sizeof(jobs) /
        sizeof(jobs[0]);

    Job selected[5];

    int selected_count =
        job_sequencing(
            jobs,
            job_count,
            selected
        );

    int total_profit = 0;

    printf("Job Sequencing:\n");

    for (int i = 0;
         i < selected_count;
         i++)
    {
        printf(
            "%c ",
            selected[i].id
        );

        total_profit +=
            selected[i].profit;
    }

    printf(
        "\nTotal profit: %d\n",
        total_profit
    );

    const char characters[] = {
        'A', 'B', 'C',
        'D', 'E', 'F'
    };

    const int frequencies[] = {
        5, 9, 12,
        13, 16, 45
    };

    int character_count =
        sizeof(characters) /
        sizeof(characters[0]);

    HuffmanNode *root =
        build_huffman_tree(
            characters,
            frequencies,
            character_count
        );

    printf("Huffman Codes:\n");

    int code[100];

    print_huffman_codes(
        root,
        code,
        0
    );

    free_huffman_tree(root);

    Edge edges[] = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 1},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    int edge_count =
        sizeof(edges) /
        sizeof(edges[0]);

    int vertex_count = 6;

    Edge kruskal_result[MAX_VERTICES];

    int kruskal_count =
        kruskal_mst(
            edges,
            vertex_count,
            edge_count,
            kruskal_result
        );

    printf("\nKruskal MST:\n");

    print_mst(
        kruskal_result,
        kruskal_count
    );

    Graph graph = {
        .vertices = 6,
        .adjacency = {0}
    };

    graph.adjacency[0][1] = 4;
    graph.adjacency[1][0] = 4;

    graph.adjacency[0][2] = 2;
    graph.adjacency[2][0] = 2;

    graph.adjacency[1][2] = 1;
    graph.adjacency[2][1] = 1;

    graph.adjacency[1][3] = 5;
    graph.adjacency[3][1] = 5;

    graph.adjacency[2][3] = 8;
    graph.adjacency[3][2] = 8;

    graph.adjacency[2][4] = 10;
    graph.adjacency[4][2] = 10;

    graph.adjacency[3][4] = 2;
    graph.adjacency[4][3] = 2;

    graph.adjacency[3][5] = 6;
    graph.adjacency[5][3] = 6;

    graph.adjacency[4][5] = 3;
    graph.adjacency[5][4] = 3;

    Edge prim_result[MAX_VERTICES];

    int prim_count =
        prim_mst(
            &graph,
            0,
            prim_result
        );

    printf("\nPrim MST:\n");

    print_mst(
        prim_result,
        prim_count
    );

    int distances[MAX_VERTICES];

    dijkstra(
        &graph,
        0,
        distances
    );

    printf("\nDijkstra from vertex 0:\n");

    for (int i = 0;
         i < graph.vertices;
         i++)
    {
        if (distances[i] == INF)
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
                distances[i]
            );
        }
    }

    return 0;
}