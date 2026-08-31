#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <string>
#include <functional>

using namespace std;

struct Activity
{
    int start;
    int finish;
};

int activitySelection(vector<Activity> activities)
{
    if (activities.empty())
    {
        return 0;
    }

    sort(
        activities.begin(),
        activities.end(),
        [](const Activity& a, const Activity& b)
        {
            return a.finish < b.finish;
        }
    );

    int selected = 1;
    int lastFinish = activities[0].finish;

    for (size_t i = 1; i < activities.size(); i++)
    {
        if (activities[i].start >= lastFinish)
        {
            selected++;
            lastFinish = activities[i].finish;
        }
    }

    return selected;
}

struct Item
{
    double value;
    double weight;
};

double fractionalKnapsack(
    vector<Item> items,
    double capacity
)
{
    sort(
        items.begin(),
        items.end(),
        [](const Item& a, const Item& b)
        {
            return (a.value / a.weight) >
                   (b.value / b.weight);
        }
    );

    double totalValue = 0.0;

    for (const Item& item : items)
    {
        if (capacity <= 0)
        {
            break;
        }

        if (item.weight <= capacity)
        {
            totalValue += item.value;
            capacity -= item.weight;
        }
        else
        {
            double fraction =
                capacity / item.weight;

            totalValue += item.value * fraction;
            capacity = 0;
        }
    }

    return totalValue;
}

struct Job
{
    char id;
    int deadline;
    int profit;
};

pair<vector<Job>, int> jobSequencing(
    vector<Job> jobs
)
{
    sort(
        jobs.begin(),
        jobs.end(),
        [](const Job& a, const Job& b)
        {
            return a.profit > b.profit;
        }
    );

    int maxDeadline = 0;

    for (const Job& job : jobs)
    {
        maxDeadline =
            max(maxDeadline, job.deadline);
    }

    vector<Job> slots(maxDeadline);
    vector<bool> occupied(maxDeadline, false);

    vector<Job> selected;
    int totalProfit = 0;

    for (const Job& job : jobs)
    {
        for (int slot = job.deadline - 1;
             slot >= 0;
             slot--)
        {
            if (!occupied[slot])
            {
                occupied[slot] = true;
                slots[slot] = job;

                selected.push_back(job);
                totalProfit += job.profit;

                break;
            }
        }
    }

    return {selected, totalProfit};
}

struct HuffmanNode
{
    char character;
    int frequency;

    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(
        char character,
        int frequency
    )
        : character(character),
          frequency(frequency),
          left(nullptr),
          right(nullptr)
    {
    }
};

struct CompareHuffman
{
    bool operator()(
        const HuffmanNode* a,
        const HuffmanNode* b
    ) const
    {
        return a->frequency > b->frequency;
    }
};

void generateHuffmanCodes(
    HuffmanNode* root,
    const string& code,
    vector<pair<char, string>>& codes
)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left == nullptr &&
        root->right == nullptr)
    {
        codes.push_back({
            root->character,
            code.empty() ? "0" : code
        });

        return;
    }

    generateHuffmanCodes(
        root->left,
        code + "0",
        codes
    );

    generateHuffmanCodes(
        root->right,
        code + "1",
        codes
    );
}

vector<pair<char, string>> huffmanCodes(
    const vector<char>& characters,
    const vector<int>& frequencies
)
{
    priority_queue<
        HuffmanNode*,
        vector<HuffmanNode*>,
        CompareHuffman
    > minHeap;

    for (size_t i = 0;
         i < characters.size();
         i++)
    {
        minHeap.push(
            new HuffmanNode(
                characters[i],
                frequencies[i]
            )
        );
    }

    while (minHeap.size() > 1)
    {
        HuffmanNode* left =
            minHeap.top();

        minHeap.pop();

        HuffmanNode* right =
            minHeap.top();

        minHeap.pop();

        HuffmanNode* parent =
            new HuffmanNode(
                '\0',
                left->frequency +
                right->frequency
            );

        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    HuffmanNode* root = minHeap.top();

    vector<pair<char, string>> codes;

    generateHuffmanCodes(
        root,
        "",
        codes
    );

    function<void(HuffmanNode*)> cleanup =
        [&](HuffmanNode* node)
        {
            if (node == nullptr)
            {
                return;
            }

            cleanup(node->left);
            cleanup(node->right);

            delete node;
        };

    cleanup(root);

    return codes;
}

struct Edge
{
    int source;
    int destination;
    int weight;
};

struct Graph
{
    int vertices;
    vector<vector<pair<int, int>>> adjacency;
};

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    explicit DisjointSet(int size)
        : parent(size),
          rank(size, 0)
    {
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    int find(int vertex)
    {
        if (parent[vertex] != vertex)
        {
            parent[vertex] =
                find(parent[vertex]);
        }

        return parent[vertex];
    }

    void unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
        {
            return;
        }

        if (rank[rootA] < rank[rootB])
        {
            parent[rootA] = rootB;
        }
        else if (rank[rootA] > rank[rootB])
        {
            parent[rootB] = rootA;
        }
        else
        {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
};

vector<Edge> kruskalMST(
    int vertexCount,
    vector<Edge> edges
)
{
    sort(
        edges.begin(),
        edges.end(),
        [](const Edge& a, const Edge& b)
        {
            return a.weight < b.weight;
        }
    );

    DisjointSet sets(vertexCount);

    vector<Edge> mst;

    for (const Edge& edge : edges)
    {
        if (sets.find(edge.source) !=
            sets.find(edge.destination))
        {
            mst.push_back(edge);

            sets.unite(
                edge.source,
                edge.destination
            );

            if (mst.size() ==
                static_cast<size_t>(vertexCount - 1))
            {
                break;
            }
        }
    }

    return mst;
}

vector<Edge> primMST(
    const Graph& graph,
    int start
)
{
    const int INF =
        numeric_limits<int>::max();

    vector<int> key(
        graph.vertices,
        INF
    );

    vector<int> parent(
        graph.vertices,
        -1
    );

    vector<bool> included(
        graph.vertices,
        false
    );

    key[start] = 0;

    vector<Edge> mst;

    for (int count = 0;
         count < graph.vertices;
         count++)
    {
        int vertex = -1;
        int minimum = INF;

        for (int v = 0;
             v < graph.vertices;
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

        included[vertex] = true;

        if (parent[vertex] != -1)
        {
            mst.push_back({
                parent[vertex],
                vertex,
                key[vertex]
            });
        }

        for (const auto& edge :
             graph.adjacency[vertex])
        {
            int neighbour = edge.first;
            int weight = edge.second;

            if (!included[neighbour] &&
                weight < key[neighbour])
            {
                key[neighbour] = weight;
                parent[neighbour] = vertex;
            }
        }
    }

    return mst;
}

vector<int> dijkstra(
    const Graph& graph,
    int source
)
{
    const int INF =
        numeric_limits<int>::max();

    vector<int> distances(
        graph.vertices,
        INF
    );

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > minHeap;

    distances[source] = 0;

    minHeap.push({
        0,
        source
    });

    while (!minHeap.empty())
    {
        int distance =
            minHeap.top().first;

        int vertex =
            minHeap.top().second;

        minHeap.pop();

        if (distance != distances[vertex])
        {
            continue;
        }

        for (const auto& edge :
             graph.adjacency[vertex])
        {
            int neighbour = edge.first;
            int weight = edge.second;

            if (weight < 0)
            {
                continue;
            }

            int newDistance =
                distance + weight;

            if (newDistance <
                distances[neighbour])
            {
                distances[neighbour] =
                    newDistance;

                minHeap.push({
                    newDistance,
                    neighbour
                });
            }
        }
    }

    return distances;
}

void printMST(
    const vector<Edge>& mst
)
{
    int totalWeight = 0;

    for (const Edge& edge : mst)
    {
        cout
            << edge.source
            << " -- "
            << edge.destination
            << " ("
            << edge.weight
            << ")\n";

        totalWeight += edge.weight;
    }

    cout
        << "Total weight: "
        << totalWeight
        << '\n';
}

int main()
{

    vector<Activity> activities = {
        {1, 3},
        {2, 4},
        {3, 5},
        {5, 7},
        {8, 9},
        {5, 9}
    };

    cout
        << "Activity Selection: "
        << activitySelection(activities)
        << " activities\n";

    vector<Item> items = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    cout
        << "Fractional Knapsack: "
        << fractionalKnapsack(items, 50)
        << '\n';

    vector<Job> jobs = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    auto jobResult =
        jobSequencing(jobs);

    cout << "Job Sequencing: ";

    for (const Job& job :
         jobResult.first)
    {
        cout << job.id << ' ';
    }

    cout
        << "\nTotal profit: "
        << jobResult.second
        << '\n';

    vector<char> characters = {
        'A', 'B', 'C',
        'D', 'E', 'F'
    };

    vector<int> frequencies = {
        5, 9, 12,
        13, 16, 45
    };

    auto codes =
        huffmanCodes(
            characters,
            frequencies
        );

    cout << "Huffman Codes:\n";

    for (const auto& code : codes)
    {
        cout
            << code.first
            << ": "
            << code.second
            << '\n';
    }

    const int vertexCount = 6;

    vector<Edge> edges = {
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

    vector<Edge> kruskalResult =
        kruskalMST(
            vertexCount,
            edges
        );

    cout << "\nKruskal MST:\n";

    printMST(kruskalResult);

    Graph graph;

    graph.vertices = vertexCount;

    graph.adjacency.resize(
        vertexCount
    );

    auto addUndirectedEdge =
        [&](int source,
            int destination,
            int weight)
        {
            graph.adjacency[source].push_back({
                destination,
                weight
            });

            graph.adjacency[destination].push_back({
                source,
                weight
            });
        };

    addUndirectedEdge(0, 1, 4);
    addUndirectedEdge(0, 2, 2);
    addUndirectedEdge(1, 2, 1);
    addUndirectedEdge(1, 3, 5);
    addUndirectedEdge(2, 3, 8);
    addUndirectedEdge(2, 4, 10);
    addUndirectedEdge(3, 4, 2);
    addUndirectedEdge(3, 5, 6);
    addUndirectedEdge(4, 5, 3);

    vector<Edge> primResult =
        primMST(
            graph,
            0
        );

    cout << "\nPrim MST:\n";

    printMST(primResult);

    vector<int> distances =
        dijkstra(
            graph,
            0
        );

    cout
        << "\nDijkstra from vertex 0:\n";

    for (int i = 0;
         i < vertexCount;
         i++)
    {
        cout
            << i
            << ": ";

        if (distances[i] ==
            numeric_limits<int>::max())
        {
            cout << "unreachable";
        }
        else
        {
            cout << distances[i];
        }

        cout << '\n';
    }

    return 0;
}