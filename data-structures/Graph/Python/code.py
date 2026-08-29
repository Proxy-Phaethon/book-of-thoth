from collections import deque


class Graph:
    def __init__(self):
        self.adjacency = {}

    def add_vertex(self, vertex):
        if vertex not in self.adjacency:
            self.adjacency[vertex] = []

    def add_edge(self, source, destination):
        if (
            source not in self.adjacency
            or destination not in self.adjacency
        ):
            return

        if destination not in self.adjacency[source]:
            self.adjacency[source].append(destination)

            if source != destination:
                self.adjacency[destination].append(source)

    def remove_edge(self, source, destination):
        if (
            source not in self.adjacency
            or destination not in self.adjacency
        ):
            return

        if destination in self.adjacency[source]:
            self.adjacency[source].remove(destination)

        if source in self.adjacency[destination]:
            self.adjacency[destination].remove(source)

    def contains_edge(self, source, destination):
        if source not in self.adjacency:
            return False

        return destination in self.adjacency[source]

    def bfs(self, start):
        if start not in self.adjacency:
            return

        queue = deque([start])
        visited = {start}

        while queue:
            vertex = queue.popleft()

            print(vertex, end=" ")

            for neighbor in self.adjacency[vertex]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        print()

    def dfs(self, start):
        if start not in self.adjacency:
            return

        visited = set()

        self._dfs_recursive(start, visited)

        print()

    def _dfs_recursive(self, vertex, visited):
        visited.add(vertex)

        print(vertex, end=" ")

        for neighbor in self.adjacency[vertex]:
            if neighbor not in visited:
                self._dfs_recursive(neighbor, visited)


graph = Graph()

graph.add_vertex(1)
graph.add_vertex(2)
graph.add_vertex(3)
graph.add_vertex(4)
graph.add_vertex(5)

graph.add_edge(1, 2)
graph.add_edge(1, 3)
graph.add_edge(2, 4)
graph.add_edge(3, 5)
graph.add_edge(4, 5)

print("BFS:", end=" ")
graph.bfs(1)

print("DFS:", end=" ")
graph.dfs(1)

print(
    "Edge 1-3:",
    "true" if graph.contains_edge(1, 3) else "false"
)

graph.remove_edge(1, 3)

print(
    "Edge 1-3 after removal:",
    "true" if graph.contains_edge(1, 3) else "false"
)