#include <iostream>
#include <vector>
#include <queue>

void bfs(const std::vector<std::vector<int>>& graph, int start)
{
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        std::cout << current << " ";

        for (int neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    std::cout << "\n";
}

int main()
{
    std::vector<std::vector<int>> graph =
    {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };

    int start = 0;

    bfs(graph, start);

    return 0;
}