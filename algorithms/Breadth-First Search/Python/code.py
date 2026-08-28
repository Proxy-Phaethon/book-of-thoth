from collections import deque


def bfs(graph, start):
    visited = [False] * len(graph)
    queue = deque()

    visited[start] = True
    queue.append(start)

    while queue:
        current = queue.popleft()

        print(current, end=" ")

        for neighbor in graph[current]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)

    print()


graph = [
    [1, 2],
    [0, 3, 4],
    [0, 5],
    [1],
    [1, 5],
    [2, 4]
]

start = 0

bfs(graph, start)