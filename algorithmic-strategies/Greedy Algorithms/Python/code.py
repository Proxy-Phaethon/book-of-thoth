from dataclasses import dataclass
import heapq

@dataclass
class Activity:
    start: int
    finish: int


def activity_selection(activities):
    if not activities:
        return 0

    activities.sort(key=lambda activity: activity.finish)

    selected = 1
    last_finish = activities[0].finish

    for activity in activities[1:]:
        if activity.start >= last_finish:
            selected += 1
            last_finish = activity.finish

    return selected

@dataclass
class Item:
    value: float
    weight: float


def fractional_knapsack(items, capacity):
    items.sort(
        key=lambda item: item.value / item.weight,
        reverse=True
    )

    total_value = 0.0

    for item in items:
        if capacity <= 0:
            break

        if item.weight <= capacity:
            total_value += item.value
            capacity -= item.weight
        else:
            fraction = capacity / item.weight
            total_value += item.value * fraction
            capacity = 0

    return total_value

@dataclass
class Job:
    id: str
    deadline: int
    profit: int


def job_sequencing(jobs):
    jobs.sort(
        key=lambda job: job.profit,
        reverse=True
    )

    max_deadline = max(
        (job.deadline for job in jobs),
        default=0
    )

    slots = [None] * max_deadline
    total_profit = 0
    selected = []

    for job in jobs:
        for slot in range(job.deadline - 1, -1, -1):
            if slots[slot] is None:
                slots[slot] = job
                selected.append(job)
                total_profit += job.profit
                break

    return selected, total_profit

@dataclass
class HuffmanNode:
    frequency: int
    character: str = ""
    left: object = None
    right: object = None


def build_huffman_tree(characters, frequencies):
    heap = []
    counter = 0

    for character, frequency in zip(
        characters,
        frequencies
    ):
        node = HuffmanNode(
            frequency=frequency,
            character=character
        )

        heapq.heappush(
            heap,
            (frequency, counter, node)
        )

        counter += 1

    if not heap:
        return None

    while len(heap) > 1:
        _, _, left = heapq.heappop(heap)
        _, _, right = heapq.heappop(heap)

        parent = HuffmanNode(
            frequency=left.frequency + right.frequency,
            left=left,
            right=right
        )

        heapq.heappush(
            heap,
            (
                parent.frequency,
                counter,
                parent
            )
        )

        counter += 1

    return heapq.heappop(heap)[2]


def generate_huffman_codes(
    root,
    code="",
    codes=None
):
    if codes is None:
        codes = {}

    if root is None:
        return codes

    if root.left is None and root.right is None:
        codes[root.character] = (
            code if code else "0"
        )

        return codes

    generate_huffman_codes(
        root.left,
        code + "0",
        codes
    )

    generate_huffman_codes(
        root.right,
        code + "1",
        codes
    )

    return codes


def huffman_codes(characters, frequencies):
    root = build_huffman_tree(
        characters,
        frequencies
    )

    return generate_huffman_codes(root)

@dataclass
class Edge:
    source: int
    destination: int
    weight: int


class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjacency = [
            [] for _ in range(vertices)
        ]

    def add_edge(
        self,
        source,
        destination,
        weight
    ):
        self.adjacency[source].append(
            (destination, weight)
        )

        self.adjacency[destination].append(
            (source, weight)
        )

class DisjointSet:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, vertex):
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(
                self.parent[vertex]
            )

        return self.parent[vertex]

    def union(self, a, b):
        root_a = self.find(a)
        root_b = self.find(b)

        if root_a == root_b:
            return

        if self.rank[root_a] < self.rank[root_b]:
            self.parent[root_a] = root_b

        elif self.rank[root_a] > self.rank[root_b]:
            self.parent[root_b] = root_a

        else:
            self.parent[root_b] = root_a
            self.rank[root_a] += 1

def kruskal_mst(vertices, edges):
    edges.sort(
        key=lambda edge: edge.weight
    )

    disjoint_set = DisjointSet(vertices)

    mst = []

    for edge in edges:
        if (
            disjoint_set.find(edge.source)
            != disjoint_set.find(edge.destination)
        ):
            mst.append(edge)

            disjoint_set.union(
                edge.source,
                edge.destination
            )

            if len(mst) == vertices - 1:
                break

    return mst

def prim_mst(graph, start):
    visited = [False] * graph.vertices

    min_heap = [
        (0, start, -1)
    ]

    mst = []

    while min_heap:
        weight, vertex, parent = heapq.heappop(
            min_heap
        )

        if visited[vertex]:
            continue

        visited[vertex] = True

        if parent != -1:
            mst.append(
                Edge(
                    parent,
                    vertex,
                    weight
                )
            )

        for neighbour, edge_weight in graph.adjacency[vertex]:
            if not visited[neighbour]:
                heapq.heappush(
                    min_heap,
                    (
                        edge_weight,
                        neighbour,
                        vertex
                    )
                )

    return mst

def dijkstra(graph, source):
    infinity = float("inf")

    distances = [
        infinity
        for _ in range(graph.vertices)
    ]

    distances[source] = 0

    min_heap = [
        (0, source)
    ]

    while min_heap:
        distance, vertex = heapq.heappop(
            min_heap
        )

        if distance != distances[vertex]:
            continue

        for neighbour, weight in graph.adjacency[vertex]:
            if weight < 0:
                raise ValueError(
                    "Dijkstra's algorithm "
                    "does not support negative weights."
                )

            new_distance = distance + weight

            if new_distance < distances[neighbour]:
                distances[neighbour] = new_distance

                heapq.heappush(
                    min_heap,
                    (
                        new_distance,
                        neighbour
                    )
                )

    return distances

def print_mst(mst):
    total_weight = 0

    for edge in mst:
        print(
            f"{edge.source} -- "
            f"{edge.destination} "
            f"({edge.weight})"
        )

        total_weight += edge.weight

    print(
        f"Total weight: {total_weight}"
    )

if __name__ == "__main__":

    activities = [
        Activity(1, 3),
        Activity(2, 4),
        Activity(3, 5),
        Activity(5, 7),
        Activity(8, 9),
        Activity(5, 9)
    ]

    print(
        "Activity Selection:",
        activity_selection(activities),
        "activities"
    )

    items = [
        Item(60, 10),
        Item(100, 20),
        Item(120, 30)
    ]

    print(
        "Fractional Knapsack:",
        fractional_knapsack(items, 50)
    )

    jobs = [
        Job("A", 2, 100),
        Job("B", 1, 19),
        Job("C", 2, 27),
        Job("D", 1, 25),
        Job("E", 3, 15)
    ]

    selected, total_profit = job_sequencing(
        jobs
    )

    print(
        "Job Sequencing:",
        [job.id for job in selected]
    )

    print(
        "Total profit:",
        total_profit
    )

    characters = [
        "A", "B", "C",
        "D", "E", "F"
    ]

    frequencies = [
        5, 9, 12,
        13, 16, 45
    ]

    codes = huffman_codes(
        characters,
        frequencies
    )

    print("Huffman Codes:")

    for character, code in codes.items():
        print(
            f"{character}: {code}"
        )

    vertices = 6

    edges = [
        Edge(0, 1, 4),
        Edge(0, 2, 2),
        Edge(1, 2, 1),
        Edge(1, 3, 5),
        Edge(2, 3, 8),
        Edge(2, 4, 10),
        Edge(3, 4, 2),
        Edge(3, 5, 6),
        Edge(4, 5, 3)
    ]

    kruskal_result = kruskal_mst(
        vertices,
        edges.copy()
    )

    print("\nKruskal MST:")

    print_mst(kruskal_result)

    graph = Graph(vertices)

    graph.add_edge(0, 1, 4)
    graph.add_edge(0, 2, 2)
    graph.add_edge(1, 2, 1)
    graph.add_edge(1, 3, 5)
    graph.add_edge(2, 3, 8)
    graph.add_edge(2, 4, 10)
    graph.add_edge(3, 4, 2)
    graph.add_edge(3, 5, 6)
    graph.add_edge(4, 5, 3)

    prim_result = prim_mst(
        graph,
        0
    )

    print("\nPrim MST:")

    print_mst(prim_result)

    distances = dijkstra(
        graph,
        0
    )

    print(
        "\nDijkstra from vertex 0:"
    )

    for vertex, distance in enumerate(
        distances
    ):
        if distance == float("inf"):
            print(
                f"{vertex}: unreachable"
            )
        else:
            print(
                f"{vertex}: {distance}"
            )