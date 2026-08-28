def dfs(graph, start):
    visited = [False] * len(graph)
    stack = [start]

    while stack:
        current = stack.pop()

        if visited[current]:
            continue

        visited[current] = True

        print(current, end=" ")

        # Push neighbors in reverse order so they are
        # visited in adjacency-list order.
        for neighbor in reversed(graph[current]):
            if not visited[neighbor]:
                stack.append(neighbor)

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

dfs(graph, start)