#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <functional>
#include <cmath>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge
{
    int source;
    int destination;
    int weight;
};

class Graph
{
public:
    int vertices;
    bool directed;
    vector<vector<pair<int, int>>> adjacency;

    Graph(int vertices, bool directed = false)
        : vertices(vertices),
          directed(directed),
          adjacency(vertices)
    {
    }

    void addEdge(int source, int destination, int weight = 1)
    {
        adjacency[source].push_back(
            {destination, weight}
        );

        if (!directed)
        {
            adjacency[destination].push_back(
                {source, weight}
            );
        }
    }
};

int connectedComponents(const Graph& graph)
{
    vector<bool> visited(graph.vertices, false);
    int components = 0;

    for (int start = 0; start < graph.vertices; start++)
    {
        if (visited[start])
        {
            continue;
        }

        components++;

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (const auto& [neighbor, weight] :
                 graph.adjacency[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    return components;
}

bool hasCycleUndirectedDFS(
    const Graph& graph,
    int current,
    int parent,
    vector<bool>& visited
)
{
    visited[current] = true;

    for (const auto& [neighbor, weight] :
         graph.adjacency[current])
    {
        if (!visited[neighbor])
        {
            if (hasCycleUndirectedDFS(
                    graph,
                    neighbor,
                    current,
                    visited))
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

bool hasCycleUndirected(const Graph& graph)
{
    vector<bool> visited(graph.vertices, false);

    for (int i = 0; i < graph.vertices; i++)
    {
        if (!visited[i])
        {
            if (hasCycleUndirectedDFS(
                    graph,
                    i,
                    -1,
                    visited))
            {
                return true;
            }
        }
    }

    return false;
}

bool hasCycleDirectedDFS(
    const Graph& graph,
    int current,
    vector<int>& state
)
{

    state[current] = 1;

    for (const auto& [neighbor, weight] :
         graph.adjacency[current])
    {
        if (state[neighbor] == 1)
        {
            return true;
        }

        if (state[neighbor] == 0)
        {
            if (hasCycleDirectedDFS(
                    graph,
                    neighbor,
                    state))
            {
                return true;
            }
        }
    }

    state[current] = 2;

    return false;
}

bool hasCycleDirected(const Graph& graph)
{
    vector<int> state(graph.vertices, 0);

    for (int i = 0; i < graph.vertices; i++)
    {
        if (state[i] == 0)
        {
            if (hasCycleDirectedDFS(
                    graph,
                    i,
                    state))
            {
                return true;
            }
        }
    }

    return false;
}

bool topologicalDFS(
    const Graph& graph,
    int current,
    vector<int>& state,
    vector<int>& result
)
{
    state[current] = 1;

    for (const auto& [neighbor, weight] :
         graph.adjacency[current])
    {
        if (state[neighbor] == 1)
        {
            return false;
        }

        if (state[neighbor] == 0)
        {
            if (!topologicalDFS(
                    graph,
                    neighbor,
                    state,
                    result))
            {
                return false;
            }
        }
    }

    state[current] = 2;
    result.push_back(current);

    return true;
}

bool topologicalSortDFS(
    const Graph& graph,
    vector<int>& result
)
{
    vector<int> state(graph.vertices, 0);

    for (int i = 0; i < graph.vertices; i++)
    {
        if (state[i] == 0)
        {
            if (!topologicalDFS(
                    graph,
                    i,
                    state,
                    result))
            {
                return false;
            }
        }
    }

    reverse(result.begin(), result.end());

    return true;
}

bool topologicalSortKahn(
    const Graph& graph,
    vector<int>& result
)
{
    vector<int> indegree(graph.vertices, 0);

    for (int vertex = 0;
         vertex < graph.vertices;
         vertex++)
    {
        for (const auto& [neighbor, weight] :
             graph.adjacency[vertex])
        {
            indegree[neighbor]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < graph.vertices; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        result.push_back(current);

        for (const auto& [neighbor, weight] :
             graph.adjacency[current])
        {
            indegree[neighbor]--;

            if (indegree[neighbor] == 0)
            {
                q.push(neighbor);
            }
        }
    }

    return result.size() == graph.vertices;
}

vector<int> dijkstra(
    const Graph& graph,
    int source
)
{
    vector<int> distance(
        graph.vertices,
        INF
    );

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    distance[source] = 0;

    pq.push({0, source});

    while (!pq.empty())
    {
        auto [currentDistance, current] =
            pq.top();

        pq.pop();

        if (currentDistance != distance[current])
        {
            continue;
        }

        for (const auto& [neighbor, weight] :
             graph.adjacency[current])
        {
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

                pq.push({
                    distance[neighbor],
                    neighbor
                });
            }
        }
    }

    return distance;
}

pair<vector<int>, bool> bellmanFord(
    const Graph& graph,
    int source
)
{
    vector<int> distance(
        graph.vertices,
        INF
    );

    distance[source] = 0;

    vector<Edge> edges;

    for (int u = 0;
         u < graph.vertices;
         u++)
    {
        for (const auto& [v, weight] :
             graph.adjacency[u])
        {
            edges.push_back({
                u,
                v,
                weight
            });
        }
    }

    for (int i = 0;
         i < graph.vertices - 1;
         i++)
    {
        bool changed = false;

        for (const Edge& edge : edges)
        {
            if (distance[edge.source] == INF)
            {
                continue;
            }

            if (
                distance[edge.source] +
                edge.weight <
                distance[edge.destination]
            )
            {
                distance[edge.destination] =
                    distance[edge.source] +
                    edge.weight;

                changed = true;
            }
        }

        if (!changed)
        {
            break;
        }
    }

    for (const Edge& edge : edges)
    {
        if (distance[edge.source] == INF)
        {
            continue;
        }

        if (
            distance[edge.source] +
            edge.weight <
            distance[edge.destination]
        )
        {
            return {distance, true};
        }
    }

    return {distance, false};
}

vector<vector<int>> floydWarshall(
    const Graph& graph
)
{
    int n = graph.vertices;

    vector<vector<int>> distance(
        n,
        vector<int>(n, INF)
    );

    for (int i = 0; i < n; i++)
    {
        distance[i][i] = 0;
    }

    for (int u = 0; u < n; u++)
    {
        for (const auto& [v, weight] :
             graph.adjacency[u])
        {
            distance[u][v] =
                min(
                    distance[u][v],
                    weight
                );
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

    return distance;
}

bool hasNegativeCycle(
    const vector<vector<int>>& distance
)
{
    for (int i = 0;
         i < static_cast<int>(distance.size());
         i++)
    {
        if (distance[i][i] < 0)
        {
            return true;
        }
    }

    return false;
}

pair<vector<Edge>, int> primMST(
    const Graph& graph
)
{
    int n = graph.vertices;

    vector<int> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    key[0] = 0;
    pq.push({0, 0});

    vector<Edge> mst;
    int totalWeight = 0;

    while (!pq.empty())
    {
        auto [weight, current] =
            pq.top();

        pq.pop();

        if (inMST[current])
        {
            continue;
        }

        inMST[current] = true;

        if (parent[current] != -1)
        {
            mst.push_back({
                parent[current],
                current,
                weight
            });

            totalWeight += weight;
        }

        for (const auto& [neighbor, edgeWeight] :
             graph.adjacency[current])
        {
            if (
                !inMST[neighbor] &&
                edgeWeight < key[neighbor]
            )
            {
                key[neighbor] = edgeWeight;
                parent[neighbor] = current;

                pq.push({
                    edgeWeight,
                    neighbor
                });
            }
        }
    }

    if (mst.size() !=
        static_cast<size_t>(n - 1))
    {
        return {{}, 0};
    }

    return {mst, totalWeight};
}

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

    int find(int value)
    {
        if (parent[value] != value)
        {
            parent[value] =
                find(parent[value]);
        }

        return parent[value];
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return;
        }

        if (rank[a] < rank[b])
        {
            swap(a, b);
        }

        parent[b] = a;

        if (rank[a] == rank[b])
        {
            rank[a]++;
        }
    }
};

pair<vector<Edge>, int> kruskalMST(
    const Graph& graph
)
{
    vector<Edge> edges;

    for (int u = 0;
         u < graph.vertices;
         u++)
    {
        for (const auto& [v, weight] :
             graph.adjacency[u])
        {
            if (graph.directed || u < v)
            {
                edges.push_back({
                    u,
                    v,
                    weight
                });
            }
        }
    }

    sort(
        edges.begin(),
        edges.end(),
        [](const Edge& a, const Edge& b)
        {
            return a.weight < b.weight;
        }
    );

    DisjointSet set(graph.vertices);

    vector<Edge> mst;
    int totalWeight = 0;

    for (const Edge& edge : edges)
    {
        if (
            set.find(edge.source) !=
            set.find(edge.destination)
        )
        {
            set.unite(
                edge.source,
                edge.destination
            );

            mst.push_back(edge);
            totalWeight += edge.weight;

            if (
                mst.size() ==
                static_cast<size_t>(
                    graph.vertices - 1
                )
            )
            {
                break;
            }
        }
    }

    if (
        mst.size() !=
        static_cast<size_t>(
            graph.vertices - 1
        )
    )
    {
        return {{}, 0};
    }

    return {mst, totalWeight};
}

void fillOrder(
    const Graph& graph,
    int current,
    vector<bool>& visited,
    stack<int>& order
)
{
    visited[current] = true;

    for (const auto& [neighbor, weight] :
         graph.adjacency[current])
    {
        if (!visited[neighbor])
        {
            fillOrder(
                graph,
                neighbor,
                visited,
                order
            );
        }
    }

    order.push(current);
}

Graph transposeGraph(const Graph& graph)
{
    Graph transpose(
        graph.vertices,
        true
    );

    for (int u = 0;
         u < graph.vertices;
         u++)
    {
        for (const auto& [v, weight] :
             graph.adjacency[u])
        {
            transpose.addEdge(
                v,
                u,
                weight
            );
        }
    }

    return transpose;
}

void collectComponent(
    const Graph& graph,
    int current,
    vector<bool>& visited,
    vector<int>& component
)
{
    visited[current] = true;

    component.push_back(current);

    for (const auto& [neighbor, weight] :
         graph.adjacency[current])
    {
        if (!visited[neighbor])
        {
            collectComponent(
                graph,
                neighbor,
                visited,
                component
            );
        }
    }
}

vector<vector<int>> stronglyConnectedComponents(
    const Graph& graph
)
{
    vector<bool> visited(
        graph.vertices,
        false
    );

    stack<int> order;

    for (int i = 0;
         i < graph.vertices;
         i++)
    {
        if (!visited[i])
        {
            fillOrder(
                graph,
                i,
                visited,
                order
            );
        }
    }

    Graph transpose =
        transposeGraph(graph);

    fill(
        visited.begin(),
        visited.end(),
        false
    );

    vector<vector<int>> components;

    while (!order.empty())
    {
        int current = order.top();
        order.pop();

        if (!visited[current])
        {
            vector<int> component;

            collectComponent(
                transpose,
                current,
                visited,
                component
            );

            components.push_back(
                component
            );
        }
    }

    return components;
}

struct Point
{
    int row;
    int column;

    bool operator==(const Point& other) const
    {
        return row == other.row &&
               column == other.column;
    }

    bool operator!=(const Point& other) const
    {
        return !(*this == other);
    }
};

int manhattanDistance(
    Point a,
    Point b
)
{
    return abs(a.row - b.row) +
           abs(a.column - b.column);
}

bool validCell(
    const vector<vector<int>>& grid,
    Point point
)
{
    return (
        point.row >= 0 &&
        point.row <
            static_cast<int>(grid.size()) &&
        point.column >= 0 &&
        point.column <
            static_cast<int>(grid[0].size()) &&
        grid[point.row][point.column] == 0
    );
}

vector<Point> aStar(
    const vector<vector<int>>& grid,
    Point start,
    Point goal
)
{
    int rows = grid.size();
    int columns = grid[0].size();

    vector<vector<int>> gCost(
        rows,
        vector<int>(columns, INF)
    );

    vector<vector<Point>> parent(
        rows,
        vector<Point>(
            columns,
            {-1, -1}
        )
    );

    vector<vector<bool>> closed(
        rows,
        vector<bool>(
            columns,
            false
        )
    );

    using Node = tuple<int, int, int>;

    priority_queue<
        Node,
        vector<Node>,
        greater<Node>
    > open;

    gCost[start.row][start.column] = 0;

    open.push({
        manhattanDistance(start, goal),
        start.row,
        start.column
    });

    int directions[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    while (!open.empty())
    {
        auto [
            f,
            row,
            column
        ] = open.top();

        open.pop();

        Point current{
            row,
            column
        };

        if (closed[row][column])
        {
            continue;
        }

        closed[row][column] = true;

        if (current == goal)
        {
            vector<Point> path;

            while (!(current == start))
            {
                path.push_back(current);

                current =
                    parent[
                        current.row
                    ][
                        current.column
                    ];
            }

            path.push_back(start);

            reverse(
                path.begin(),
                path.end()
            );

            return path;
        }

        for (auto& direction : directions)
        {
            Point neighbor{
                row + direction[0],
                column + direction[1]
            };

            if (!validCell(grid, neighbor))
            {
                continue;
            }

            if (
                closed[
                    neighbor.row
                ][
                    neighbor.column
                ]
            )
            {
                continue;
            }

            int newG =
                gCost[row][column] + 1;

            if (
                newG <
                gCost[
                    neighbor.row
                ][
                    neighbor.column
                ]
            )
            {
                gCost[
                    neighbor.row
                ][
                    neighbor.column
                ] = newG;

                parent[
                    neighbor.row
                ][
                    neighbor.column
                ] = current;

                int h =
                    manhattanDistance(
                        neighbor,
                        goal
                    );

                open.push({
                    newG + h,
                    neighbor.row,
                    neighbor.column
                });
            }
        }
    }

    return {};
}

void printDistances(
    const vector<int>& distances
)
{
    for (int i = 0;
         i < static_cast<int>(distances.size());
         i++)
    {
        cout << i << ": ";

        if (distances[i] == INF)
        {
            cout << "unreachable";
        }
        else
        {
            cout << distances[i];
        }

        cout << '\n';
    }
}

void printEdges(
    const vector<Edge>& edges,
    int totalWeight
)
{
    for (const Edge& edge : edges)
    {
        cout << edge.source
             << " -- "
             << edge.destination
             << " ("
             << edge.weight
             << ")\n";
    }

    cout << "Total weight: "
         << totalWeight
         << '\n';
}

void printOrder(
    const vector<int>& order
)
{
    for (size_t i = 0;
         i < order.size();
         i++)
    {
        cout << order[i];

        if (i + 1 < order.size())
        {
            cout << " -> ";
        }
    }

    cout << '\n';
}

int main()
{

    Graph componentsGraph(6);

    componentsGraph.addEdge(0, 1);
    componentsGraph.addEdge(1, 2);
    componentsGraph.addEdge(3, 4);
    componentsGraph.addEdge(4, 5);

    cout << "Connected Components: "
         << connectedComponents(
                componentsGraph
            )
         << '\n';

    Graph cycleGraph(3);

    cycleGraph.addEdge(0, 1);
    cycleGraph.addEdge(1, 2);
    cycleGraph.addEdge(2, 0);

    cout << "Undirected Cycle: "
         << (
                hasCycleUndirected(
                    cycleGraph
                )
                    ? "true"
                    : "false"
            )
         << '\n';

    Graph directedCycle(3, true);

    directedCycle.addEdge(0, 1);
    directedCycle.addEdge(1, 2);
    directedCycle.addEdge(2, 0);

    cout << "Directed Cycle: "
         << (
                hasCycleDirected(
                    directedCycle
                )
                    ? "true"
                    : "false"
            )
         << '\n';

    Graph dag(6, true);

    dag.addEdge(5, 0);
    dag.addEdge(5, 2);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);

    vector<int> order;

    cout << "\nTopological Sort (DFS): ";

    if (topologicalSortDFS(dag, order))
    {
        printOrder(order);
    }
    else
    {
        cout << "Cycle detected\n";
    }

    order.clear();

    cout << "Topological Sort (Kahn): ";

    if (topologicalSortKahn(dag, order))
    {
        printOrder(order);
    }
    else
    {
        cout << "Cycle detected\n";
    }

    Graph weighted(6, true);

    weighted.addEdge(0, 1, 4);
    weighted.addEdge(0, 2, 2);
    weighted.addEdge(1, 2, 1);
    weighted.addEdge(1, 3, 5);
    weighted.addEdge(2, 3, 8);
    weighted.addEdge(2, 4, 10);
    weighted.addEdge(3, 4, 2);
    weighted.addEdge(3, 5, 6);
    weighted.addEdge(4, 5, 3);

    vector<int> distances =
        dijkstra(
            weighted,
            0
        );

    cout << "\nDijkstra from vertex 0:\n";

    printDistances(distances);

    Graph bellman(5, true);

    bellman.addEdge(0, 1, 6);
    bellman.addEdge(0, 2, 7);
    bellman.addEdge(1, 2, 8);
    bellman.addEdge(1, 3, 5);
    bellman.addEdge(1, 4, -4);
    bellman.addEdge(2, 3, -3);
    bellman.addEdge(2, 4, 9);
    bellman.addEdge(3, 1, -2);
    bellman.addEdge(4, 0, 2);
    bellman.addEdge(4, 3, 7);

    auto [
        bellmanDistances,
        negativeCycle
    ] = bellmanFord(
        bellman,
        0
    );

    cout << "\nBellman-Ford from vertex 0:\n";

    printDistances(
        bellmanDistances
    );

    cout << "Negative cycle: "
         << (
                negativeCycle
                    ? "true"
                    : "false"
            )
         << '\n';

    auto allPairs =
        floydWarshall(weighted);

    cout << "\nFloyd-Warshall:\n";

    for (const auto& row : allPairs)
    {
        for (int distance : row)
        {
            if (distance == INF)
            {
                cout << "INF ";
            }
            else
            {
                cout << distance << ' ';
            }
        }

        cout << '\n';
    }

    cout << "Negative cycle: "
         << (
                hasNegativeCycle(
                    allPairs
                )
                    ? "true"
                    : "false"
            )
         << '\n';

    Graph mstGraph(6);

    mstGraph.addEdge(0, 1, 4);
    mstGraph.addEdge(0, 2, 2);
    mstGraph.addEdge(1, 2, 1);
    mstGraph.addEdge(1, 3, 5);
    mstGraph.addEdge(2, 3, 8);
    mstGraph.addEdge(2, 4, 10);
    mstGraph.addEdge(3, 4, 2);
    mstGraph.addEdge(3, 5, 6);
    mstGraph.addEdge(4, 5, 3);

    auto [
        primResult,
        primWeight
    ] = primMST(mstGraph);

    cout << "\nPrim MST:\n";

    printEdges(
        primResult,
        primWeight
    );

    auto [
        kruskalResult,
        kruskalWeight
    ] = kruskalMST(mstGraph);

    cout << "\nKruskal MST:\n";

    printEdges(
        kruskalResult,
        kruskalWeight
    );

    Graph sccGraph(5, true);

    sccGraph.addEdge(0, 1);
    sccGraph.addEdge(1, 2);
    sccGraph.addEdge(2, 0);
    sccGraph.addEdge(1, 3);
    sccGraph.addEdge(3, 4);
    sccGraph.addEdge(4, 3);

    auto components =
        stronglyConnectedComponents(
            sccGraph
        );

    cout << "\nStrongly Connected Components:\n";

    for (size_t i = 0;
         i < components.size();
         i++)
    {
        cout << "Component "
             << i + 1
             << ": ";

        for (int vertex : components[i])
        {
            cout << vertex << ' ';
        }

        cout << '\n';
    }

    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}
    };

    Point start{0, 0};
    Point goal{4, 5};

    vector<Point> path =
        aStar(
            grid,
            start,
            goal
        );

    cout << "\nA* Path:\n";

    if (path.empty())
    {
        cout << "No path exists.\n";
    }
    else
    {
        for (const Point& point : path)
        {
            cout << '('
                 << point.row
                 << ", "
                 << point.column
                 << ")";

            if (point != path.back())
            {
                cout << " -> ";
            }
        }

        cout << '\n';
    }

    return 0;
}