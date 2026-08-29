#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

class Graph
{
private:
    std::unordered_map<int, std::vector<int>> adjacency;

    void dfs_recursive(
        int vertex,
        std::unordered_set<int>& visited
    ) const
    {
        visited.insert(vertex);

        std::cout << vertex << " ";

        for (int neighbor : adjacency.at(vertex))
        {
            if (visited.find(neighbor) == visited.end())
            {
                dfs_recursive(neighbor, visited);
            }
        }
    }

public:
    void addVertex(int vertex)
    {
        if (adjacency.find(vertex) == adjacency.end())
        {
            adjacency[vertex] = {};
        }
    }

    void addEdge(int source, int destination)
    {
        if (adjacency.find(source) == adjacency.end() ||
            adjacency.find(destination) == adjacency.end())
        {
            return;
        }

        if (!containsEdge(source, destination))
        {
            adjacency[source].push_back(destination);

            if (source != destination)
            {
                adjacency[destination].push_back(source);
            }
        }
    }

    void removeEdge(int source, int destination)
    {
        if (adjacency.find(source) == adjacency.end() ||
            adjacency.find(destination) == adjacency.end())
        {
            return;
        }

        auto& sourceList = adjacency[source];

        sourceList.erase(
            std::remove(
                sourceList.begin(),
                sourceList.end(),
                destination
            ),
            sourceList.end()
        );

        if (source != destination)
        {
            auto& destinationList = adjacency[destination];

            destinationList.erase(
                std::remove(
                    destinationList.begin(),
                    destinationList.end(),
                    source
                ),
                destinationList.end()
            );
        }
    }

    bool containsEdge(int source, int destination) const
    {
        auto sourceVertex = adjacency.find(source);

        if (sourceVertex == adjacency.end())
        {
            return false;
        }

        const auto& neighbors = sourceVertex->second;

        return std::find(
            neighbors.begin(),
            neighbors.end(),
            destination
        ) != neighbors.end();
    }

    void bfs(int start) const
    {
        if (adjacency.find(start) == adjacency.end())
        {
            return;
        }

        std::queue<int> queue;
        std::unordered_set<int> visited;

        queue.push(start);
        visited.insert(start);

        while (!queue.empty())
        {
            int vertex = queue.front();
            queue.pop();

            std::cout << vertex << " ";

            for (int neighbor : adjacency.at(vertex))
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }

        std::cout << "\n";
    }

    void dfs(int start) const
    {
        if (adjacency.find(start) == adjacency.end())
        {
            return;
        }

        std::unordered_set<int> visited;

        dfs_recursive(start, visited);

        std::cout << "\n";
    }
};

int main()
{
    Graph graph;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    std::cout << "BFS: ";
    graph.bfs(1);

    std::cout << "DFS: ";
    graph.dfs(1);

    std::cout << "Edge 1-3: "
              << (graph.containsEdge(1, 3) ? "true" : "false")
              << "\n";

    graph.removeEdge(1, 3);

    std::cout << "Edge 1-3 after removal: "
              << (graph.containsEdge(1, 3) ? "true" : "false")
              << "\n";

    return 0;
}