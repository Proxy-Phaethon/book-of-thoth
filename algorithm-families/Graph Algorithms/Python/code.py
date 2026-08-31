from collections import deque
import heapq


INF = float("inf")

class Graph:
    def __init__(self, vertices, directed=False):
        self.vertices = vertices
        self.directed = directed
        self.adjacency = [[] for _ in range(vertices)]

    def add_edge(self, source, destination, weight=1):
        self.adjacency[source].append(
            (destination, weight)
        )

        if not self.directed:
            self.adjacency[destination].append(
                (source, weight)
            )

def connected_components(graph):
    visited = [False] * graph.vertices
    components = 0

    for start in range(graph.vertices):
        if visited[start]:
            continue

        components += 1

        queue = deque([start])
        visited[start] = True

        while queue:
            current = queue.popleft()

            for neighbor, weight in graph.adjacency[current]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)

    return components

def has_cycle_undirected_dfs(
    graph,
    current,
    parent,
    visited
):
    visited[current] = True

    for neighbor, weight in graph.adjacency[current]:
        if not visited[neighbor]:
            if has_cycle_undirected_dfs(
                graph,
                neighbor,
                current,
                visited
            ):
                return True

        elif neighbor != parent:
            return True

    return False


def has_cycle_undirected(graph):
    visited = [False] * graph.vertices

    for vertex in range(graph.vertices):
        if not visited[vertex]:
            if has_cycle_undirected_dfs(
                graph,
                vertex,
                -1,
                visited
            ):
                return True

    return False

def has_cycle_directed_dfs(
    graph,
    current,
    state
):

    state[current] = 1

    for neighbor, weight in graph.adjacency[current]:
        if state[neighbor] == 1:
            return True

        if state[neighbor] == 0:
            if has_cycle_directed_dfs(
                graph,
                neighbor,
                state
            ):
                return True

    state[current] = 2

    return False


def has_cycle_directed(graph):
    state = [0] * graph.vertices

    for vertex in range(graph.vertices):
        if state[vertex] == 0:
            if has_cycle_directed_dfs(
                graph,
                vertex,
                state
            ):
                return True

    return False

def topological_dfs(
    graph,
    current,
    state,
    result
):
    state[current] = 1

    for neighbor, weight in graph.adjacency[current]:
        if state[neighbor] == 1:
            return False

        if state[neighbor] == 0:
            if not topological_dfs(
                graph,
                neighbor,
                state,
                result
            ):
                return False

    state[current] = 2
    result.append(current)

    return True


def topological_sort_dfs(graph):
    state = [0] * graph.vertices
    result = []

    for vertex in range(graph.vertices):
        if state[vertex] == 0:
            if not topological_dfs(
                graph,
                vertex,
                state,
                result
            ):
                return None

    result.reverse()

    return result

def topological_sort_kahn(graph):
    indegree = [0] * graph.vertices

    for vertex in range(graph.vertices):
        for neighbor, weight in graph.adjacency[vertex]:
            indegree[neighbor] += 1

    queue = deque()

    for vertex in range(graph.vertices):
        if indegree[vertex] == 0:
            queue.append(vertex)

    result = []

    while queue:
        current = queue.popleft()
        result.append(current)

        for neighbor, weight in graph.adjacency[current]:
            indegree[neighbor] -= 1

            if indegree[neighbor] == 0:
                queue.append(neighbor)

    if len(result) != graph.vertices:
        return None

    return result

def dijkstra(graph, source):
    distance = [INF] * graph.vertices
    distance[source] = 0

    priority_queue = [(0, source)]

    while priority_queue:
        current_distance, current = heapq.heappop(
            priority_queue
        )

        if current_distance != distance[current]:
            continue

        for neighbor, weight in graph.adjacency[current]:

            if weight < 0:
                continue

            new_distance = (
                distance[current] + weight
            )

            if new_distance < distance[neighbor]:
                distance[neighbor] = new_distance

                heapq.heappush(
                    priority_queue,
                    (new_distance, neighbor)
                )

    return distance

def bellman_ford(graph, source):
    distance = [INF] * graph.vertices
    distance[source] = 0

    edges = []

    for source_vertex in range(graph.vertices):
        for destination, weight in graph.adjacency[
            source_vertex
        ]:
            edges.append(
                (
                    source_vertex,
                    destination,
                    weight
                )
            )

    for _ in range(graph.vertices - 1):
        changed = False

        for source_vertex, destination, weight in edges:

            if distance[source_vertex] == INF:
                continue

            new_distance = (
                distance[source_vertex] + weight
            )

            if new_distance < distance[destination]:
                distance[destination] = new_distance
                changed = True

        if not changed:
            break

    for source_vertex, destination, weight in edges:

        if distance[source_vertex] == INF:
            continue

        if (
            distance[source_vertex] + weight
            < distance[destination]
        ):
            return distance, True

    return distance, False

def floyd_warshall(graph):
    n = graph.vertices

    distance = [
        [INF] * n
        for _ in range(n)
    ]

    for vertex in range(n):
        distance[vertex][vertex] = 0

    for source in range(n):
        for destination, weight in graph.adjacency[source]:
            distance[source][destination] = min(
                distance[source][destination],
                weight
            )

    for intermediate in range(n):
        for source in range(n):

            if distance[source][intermediate] == INF:
                continue

            for destination in range(n):

                if distance[intermediate][destination] == INF:
                    continue

                new_distance = (
                    distance[source][intermediate]
                    + distance[intermediate][destination]
                )

                if new_distance < distance[source][destination]:
                    distance[source][destination] = new_distance

    return distance


def has_negative_cycle(distance):
    for vertex in range(len(distance)):
        if distance[vertex][vertex] < 0:
            return True

    return False

def prim_mst(graph):
    key = [INF] * graph.vertices
    parent = [-1] * graph.vertices
    in_mst = [False] * graph.vertices

    key[0] = 0

    priority_queue = [(0, 0)]

    mst = []
    total_weight = 0

    while priority_queue:
        weight, current = heapq.heappop(
            priority_queue
        )

        if in_mst[current]:
            continue

        in_mst[current] = True

        if parent[current] != -1:
            mst.append(
                (
                    parent[current],
                    current,
                    weight
                )
            )

            total_weight += weight

        for neighbor, edge_weight in graph.adjacency[current]:

            if (
                not in_mst[neighbor]
                and edge_weight < key[neighbor]
            ):
                key[neighbor] = edge_weight
                parent[neighbor] = current

                heapq.heappush(
                    priority_queue,
                    (edge_weight, neighbor)
                )

    if len(mst) != graph.vertices - 1:
        return [], 0

    return mst, total_weight

class DisjointSet:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, value):
        if self.parent[value] != value:
            self.parent[value] = self.find(
                self.parent[value]
            )

        return self.parent[value]

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)

        if a == b:
            return

        if self.rank[a] < self.rank[b]:
            a, b = b, a

        self.parent[b] = a

        if self.rank[a] == self.rank[b]:
            self.rank[a] += 1


def kruskal_mst(graph):
    edges = []

    for source in range(graph.vertices):
        for destination, weight in graph.adjacency[source]:

            if graph.directed or source < destination:
                edges.append(
                    (
                        source,
                        destination,
                        weight
                    )
                )

    edges.sort(key=lambda edge: edge[2])

    disjoint_set = DisjointSet(graph.vertices)

    mst = []
    total_weight = 0

    for source, destination, weight in edges:

        if (
            disjoint_set.find(source)
            != disjoint_set.find(destination)
        ):
            disjoint_set.union(
                source,
                destination
            )

            mst.append(
                (
                    source,
                    destination,
                    weight
                )
            )

            total_weight += weight

            if len(mst) == graph.vertices - 1:
                break

    if len(mst) != graph.vertices - 1:
        return [], 0

    return mst, total_weight

def fill_order(
    graph,
    current,
    visited,
    order
):
    visited[current] = True

    for neighbor, weight in graph.adjacency[current]:
        if not visited[neighbor]:
            fill_order(
                graph,
                neighbor,
                visited,
                order
            )

    order.append(current)


def transpose_graph(graph):
    transpose = Graph(
        graph.vertices,
        directed=True
    )

    for source in range(graph.vertices):
        for destination, weight in graph.adjacency[source]:
            transpose.add_edge(
                destination,
                source,
                weight
            )

    return transpose


def collect_component(
    graph,
    current,
    visited,
    component
):
    visited[current] = True
    component.append(current)

    for neighbor, weight in graph.adjacency[current]:
        if not visited[neighbor]:
            collect_component(
                graph,
                neighbor,
                visited,
                component
            )


def strongly_connected_components(graph):
    visited = [False] * graph.vertices
    order = []

    for vertex in range(graph.vertices):
        if not visited[vertex]:
            fill_order(
                graph,
                vertex,
                visited,
                order
            )

    transpose = transpose_graph(graph)

    visited = [False] * graph.vertices
    components = []

    while order:
        current = order.pop()

        if not visited[current]:
            component = []

            collect_component(
                transpose,
                current,
                visited,
                component
            )

            components.append(component)

    return components

def manhattan_distance(a, b):
    return (
        abs(a[0] - b[0])
        + abs(a[1] - b[1])
    )


def valid_cell(grid, point):
    row, column = point

    return (
        0 <= row < len(grid)
        and 0 <= column < len(grid[0])
        and grid[row][column] == 0
    )


def a_star(grid, start, goal):
    rows = len(grid)
    columns = len(grid[0])

    g_cost = [
        [INF] * columns
        for _ in range(rows)
    ]

    parent = [
        [None] * columns
        for _ in range(rows)
    ]

    closed = [
        [False] * columns
        for _ in range(rows)
    ]

    priority_queue = []

    g_cost[start[0]][start[1]] = 0

    heapq.heappush(
        priority_queue,
        (
            manhattan_distance(start, goal),
            start
        )
    )

    directions = [
        (-1, 0),
        (1, 0),
        (0, -1),
        (0, 1)
    ]

    while priority_queue:
        _, current = heapq.heappop(
            priority_queue
        )

        row, column = current

        if closed[row][column]:
            continue

        closed[row][column] = True

        if current == goal:
            path = []

            while current != start:
                path.append(current)

                current = parent[
                    current[0]
                ][
                    current[1]
                ]

            path.append(start)
            path.reverse()

            return path

        for row_change, column_change in directions:

            neighbor = (
                row + row_change,
                column + column_change
            )

            if not valid_cell(grid, neighbor):
                continue

            neighbor_row, neighbor_column = neighbor

            if closed[neighbor_row][neighbor_column]:
                continue

            new_g = g_cost[row][column] + 1

            if new_g < g_cost[neighbor_row][neighbor_column]:

                g_cost[
                    neighbor_row
                ][
                    neighbor_column
                ] = new_g

                parent[
                    neighbor_row
                ][
                    neighbor_column
                ] = current

                h = manhattan_distance(
                    neighbor,
                    goal
                )

                heapq.heappush(
                    priority_queue,
                    (
                        new_g + h,
                        neighbor
                    )
                )

    return []

def print_distances(distances):
    for vertex, distance in enumerate(distances):
        if distance == INF:
            print(f"{vertex}: unreachable")
        else:
            print(f"{vertex}: {distance}")


def print_edges(edges, total_weight):
    for source, destination, weight in edges:
        print(
            f"{source} -- {destination} ({weight})"
        )

    print(f"Total weight: {total_weight}")


def print_order(order):
    print(" -> ".join(map(str, order)))

def main():

    components_graph = Graph(6)

    components_graph.add_edge(0, 1)
    components_graph.add_edge(1, 2)
    components_graph.add_edge(3, 4)
    components_graph.add_edge(4, 5)

    print(
        "Connected Components:",
        connected_components(
            components_graph
        )
    )

    cycle_graph = Graph(3)

    cycle_graph.add_edge(0, 1)
    cycle_graph.add_edge(1, 2)
    cycle_graph.add_edge(2, 0)

    print(
        "Undirected Cycle:",
        has_cycle_undirected(
            cycle_graph
        )
    )

    directed_cycle = Graph(
        3,
        directed=True
    )

    directed_cycle.add_edge(0, 1)
    directed_cycle.add_edge(1, 2)
    directed_cycle.add_edge(2, 0)

    print(
        "Directed Cycle:",
        has_cycle_directed(
            directed_cycle
        )
    )

    dag = Graph(
        6,
        directed=True
    )

    dag.add_edge(5, 0)
    dag.add_edge(5, 2)
    dag.add_edge(4, 0)
    dag.add_edge(4, 1)
    dag.add_edge(2, 3)
    dag.add_edge(3, 1)

    print("\nTopological Sort (DFS):")

    order = topological_sort_dfs(dag)

    if order is not None:
        print_order(order)
    else:
        print("Cycle detected")

    print("Topological Sort (Kahn):")

    order = topological_sort_kahn(dag)

    if order is not None:
        print_order(order)
    else:
        print("Cycle detected")

    weighted = Graph(
        6,
        directed=True
    )

    weighted.add_edge(0, 1, 4)
    weighted.add_edge(0, 2, 2)
    weighted.add_edge(1, 2, 1)
    weighted.add_edge(1, 3, 5)
    weighted.add_edge(2, 3, 8)
    weighted.add_edge(2, 4, 10)
    weighted.add_edge(3, 4, 2)
    weighted.add_edge(3, 5, 6)
    weighted.add_edge(4, 5, 3)

    distances = dijkstra(
        weighted,
        0
    )

    print("\nDijkstra from vertex 0:")
    print_distances(distances)

    bellman = Graph(
        5,
        directed=True
    )

    bellman.add_edge(0, 1, 6)
    bellman.add_edge(0, 2, 7)
    bellman.add_edge(1, 2, 8)
    bellman.add_edge(1, 3, 5)
    bellman.add_edge(1, 4, -4)
    bellman.add_edge(2, 3, -3)
    bellman.add_edge(2, 4, 9)
    bellman.add_edge(3, 1, -2)
    bellman.add_edge(4, 0, 2)
    bellman.add_edge(4, 3, 7)

    distances, negative_cycle = bellman_ford(
        bellman,
        0
    )

    print("\nBellman-Ford from vertex 0:")
    print_distances(distances)

    print(
        "Negative cycle:",
        negative_cycle
    )

    all_pairs = floyd_warshall(weighted)

    print("\nFloyd-Warshall:")

    for row in all_pairs:
        print(
            " ".join(
                "INF" if value == INF
                else str(value)
                for value in row
            )
        )

    print(
        "Negative cycle:",
        has_negative_cycle(all_pairs)
    )

    mst_graph = Graph(6)

    mst_graph.add_edge(0, 1, 4)
    mst_graph.add_edge(0, 2, 2)
    mst_graph.add_edge(1, 2, 1)
    mst_graph.add_edge(1, 3, 5)
    mst_graph.add_edge(2, 3, 8)
    mst_graph.add_edge(2, 4, 10)
    mst_graph.add_edge(3, 4, 2)
    mst_graph.add_edge(3, 5, 6)
    mst_graph.add_edge(4, 5, 3)

    mst, total_weight = prim_mst(
        mst_graph
    )

    print("\nPrim MST:")
    print_edges(
        mst,
        total_weight
    )

    mst, total_weight = kruskal_mst(
        mst_graph
    )

    print("\nKruskal MST:")
    print_edges(
        mst,
        total_weight
    )

    scc_graph = Graph(
        5,
        directed=True
    )

    scc_graph.add_edge(0, 1)
    scc_graph.add_edge(1, 2)
    scc_graph.add_edge(2, 0)
    scc_graph.add_edge(1, 3)
    scc_graph.add_edge(3, 4)
    scc_graph.add_edge(4, 3)

    components = strongly_connected_components(
        scc_graph
    )

    print("\nStrongly Connected Components:")

    for index, component in enumerate(
        components,
        start=1
    ):
        print(
            f"Component {index}:",
            *component
        )

    grid = [
        [0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0]
    ]

    start = (0, 0)
    goal = (4, 5)

    path = a_star(
        grid,
        start,
        goal
    )

    print("\nA* Path:")

    if not path:
        print("No path exists.")
    else:
        print(
            " -> ".join(
                f"({row}, {column})"
                for row, column in path
            )
        )


if __name__ == "__main__":
    main()