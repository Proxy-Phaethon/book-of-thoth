#include <iostream>
#include <vector>
#include <stack>

void dfs(const std::vector<std::vector<int>>& graph, int start)
{
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;

    stack.push(start);

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        if (visited[current])
        {
            continue;
        }

        visited[current] = true;

        std::cout << current << " ";

        /*
         * Push neighbors in reverse order so that
         * they are visited in adjacency-list order.
         */
        for (auto it = graph[current].rbegin();
             it != graph[current].rend();
             ++it)
        {
            if (!visited[*it])
            {
                stack.push(*it);
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

    dfs(graph, start);

    return 0;
}