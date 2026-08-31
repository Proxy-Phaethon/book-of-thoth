# Graph Algorithms

## Problem

Implement a collection of fundamental algorithms for solving problems on graphs.

A graph consists of:

```text
Vertices (Nodes)
      +
Edges (Connections)
```

Graphs may be:

```text
Directed / Undirected
Weighted / Unweighted
Connected / Disconnected
```

You have already implemented:

* Breadth-First Search (BFS)
* Depth-First Search (DFS)

This chapter builds on those concepts and introduces algorithms for connectivity, ordering, shortest paths, and minimum spanning trees.

---

# 1. Connected Components

Given an undirected graph, determine the number of connected components.

A connected component is a group of vertices where every vertex is reachable from every other vertex in that group.

Example:

```text
0 ─── 1       3 ─── 4
│             │
2             5

Component 1: {0, 1, 2}
Component 2: {3, 4, 5}
```

The graph contains:

```text
2 connected components
```

Use BFS or DFS to explore each unvisited vertex.

### Goal

Return the number of connected components.

### Complexity Target

```text
Time:  O(V + E)
Space: O(V)
```

---

# 2. Cycle Detection

Determine whether a graph contains a cycle.

For an undirected graph, use DFS and track the parent of each vertex.

Example:

```text
0 ─── 1
│     │
└──── 2
```

The graph contains a cycle:

```text
0 → 1 → 2 → 0
```

For a directed graph, determine whether a cycle exists using DFS and a recursion-state mechanism.

### Goal

Return:

```text
true
```

if the graph contains a cycle, otherwise:

```text
false
```

### Complexity Target

```text
Time:  O(V + E)
Space: O(V)
```

---

# 3. Topological Sort

Given a directed acyclic graph (DAG), produce an ordering of its vertices such that for every directed edge:

```text
u → v
```

`u` appears before `v`.

Example:

```text
5 → 0
5 → 2
4 → 0
4 → 1
2 → 3
3 → 1
```

A valid ordering is:

```text
5 4 2 3 1 0
```

Implement topological sorting using:

1. DFS
2. Kahn's algorithm using indegrees and a queue

A topological ordering only exists if the graph contains no directed cycle.

### Goal

Return a valid topological ordering, or indicate that one does not exist.

### Complexity Target

```text
Time:  O(V + E)
Space: O(V)
```

---

# 4. Dijkstra's Shortest Path

Given a weighted graph with **non-negative edge weights**, find the shortest distance from a source vertex to every other vertex.

Example:

```text
       4
  0 ─────── 1
  │         │
 2│         │1
  │         │
  2 ─────── 3
       8
```

Starting from vertex `0`, determine the shortest distance to every vertex.

Use a priority queue to efficiently select the vertex with the smallest known distance.

### Goal

Return the shortest distance from the source to every vertex.

Unreachable vertices should be represented appropriately.

### Restriction

Dijkstra's algorithm must not be used with negative edge weights.

### Complexity Target

Using an adjacency list and priority queue:

```text
Time:  O((V + E) log V)
Space: O(V)
```

---

# 5. Bellman-Ford

Implement the Bellman-Ford algorithm to find shortest paths from a source vertex.

Unlike Dijkstra's algorithm, Bellman-Ford can handle negative edge weights.

Example:

```text
0 ──4──→ 1
│        │
5       -3
│        │
↓        ↓
2 ──2──→ 3
```

Relax every edge repeatedly.

For a graph with `V` vertices, perform at most:

```text
V - 1
```

relaxation rounds.

Then perform one additional round.

If any distance can still be improved, the graph contains a negative-weight cycle reachable from the source.

### Goal

Return:

* The shortest distance to every vertex.
* Whether a reachable negative-weight cycle exists.

### Complexity Target

```text
Time:  O(V × E)
Space: O(V)
```

---

# 6. Floyd-Warshall

Find the shortest paths between **every pair of vertices**.

Unlike Dijkstra and Bellman-Ford, which operate from a single source, Floyd-Warshall computes all-pairs shortest paths.

For every possible intermediate vertex `k`, determine whether:

```text
i → k → j
```

is shorter than:

```text
i → j
```

The central recurrence is:

```text
dp[i][j] =
    min(
        dp[i][j],
        dp[i][k] + dp[k][j]
    )
```

Example:

```text
0 ──3──→ 1
│        │
10       2
│        │
└──────→ 2
```

The direct path:

```text
0 → 2 = 10
```

can be improved through vertex `1`:

```text
0 → 1 → 2
= 3 + 2
= 5
```

### Goal

Return the shortest distance between every pair of vertices.

### Negative Edges

Negative edge weights are allowed.

A negative cycle can be detected if:

```text
distance[i][i] < 0
```

for any vertex `i` after the algorithm completes.

### Complexity Target

```text
Time:  O(V³)
Space: O(V²)
```

---

# 7. Minimum Spanning Tree with Prim's Algorithm

Given a connected, weighted, undirected graph, find a **Minimum Spanning Tree (MST)**.

A spanning tree:

* Contains every vertex.
* Contains exactly `V - 1` edges.
* Contains no cycles.

The minimum spanning tree has the smallest possible total edge weight.

Prim's algorithm starts with one vertex and repeatedly chooses the cheapest edge connecting the current tree to an unvisited vertex.

Example:

```text
       4
  0 ─────── 1
  │ \       │
 2│  \1     │5
  │   \     │
  2 ─────── 3
       8
```

### Goal

Return the edges belonging to the MST and their total weight.

### Complexity Target

Using an adjacency list and priority queue:

```text
Time:  O((V + E) log V)
Space: O(V)
```

---

# 8. Minimum Spanning Tree with Kruskal's Algorithm

Implement another MST algorithm using Kruskal's approach.

Sort all edges by increasing weight.

Then repeatedly select the cheapest edge that does not create a cycle.

Use a **Disjoint Set Union (DSU)** / **Union-Find** data structure to efficiently detect whether adding an edge would create a cycle.

General process:

```text
Sort edges
    ↓
Take smallest edge
    ↓
Would it create a cycle?
    ├── Yes → Skip
    └── No  → Add
    ↓
Repeat until V - 1 edges are selected
```

### Goal

Return the MST and its total weight.

### Complexity Target

```text
Time:  O(E log E)
Space: O(V)
```

---

# 9. Strongly Connected Components

Given a directed graph, find all **Strongly Connected Components (SCCs)**.

A strongly connected component is a maximal set of vertices where every vertex can reach every other vertex.

Example:

```text
0 → 1
↑   ↓
└── 2

3 → 4
↑   ↓
└── 3
```

The SCCs are:

```text
{0, 1, 2}
{3, 4}
```

Implement Kosaraju's algorithm:

```text
1. Perform DFS on the original graph.
2. Record vertices by finishing time.
3. Reverse every edge.
4. Process vertices in decreasing finishing-time order.
5. Perform DFS on the reversed graph.
6. Each DFS traversal produces one SCC.
```

### Goal

Return all strongly connected components.

### Complexity Target

```text
Time:  O(V + E)
Space: O(V + E)
```

---

# 10. A* Search

Implement the A* pathfinding algorithm.

A* finds a path between a starting vertex and a target vertex using:

```text
f(n) = g(n) + h(n)
```

where:

```text
g(n) = cost from the start to n

h(n) = estimated cost from n to the target

f(n) = estimated total path cost
```

For a grid, a common heuristic is Manhattan distance:

```text
h(n) =
|x₁ - x₂| + |y₁ - y₂|
```

Example:

```text
S . . #
. # . .
. . . G
```

Find the lowest-cost path from:

```text
S
```

to:

```text
G
```

### Goal

Return the shortest path from the source to the destination.

### Requirement

Your implementation should maintain enough information to reconstruct the actual path, not merely its cost.

### Complexity

The complexity depends heavily on the graph structure and heuristic.

For this implementation, focus primarily on understanding:

```text
g(n)
h(n)
f(n)
```

and how the priority queue chooses the next vertex.

---

# Graph Representations

Use an adjacency list as the primary representation for most algorithms:

```text
0 → (1, 4), (2, 2)
1 → (0, 4), (2, 1), (3, 5)
2 → (0, 2), (1, 1), (3, 8)
```

For algorithms such as Floyd-Warshall, use an adjacency matrix:

```text
      0    1    2

0     0    4    2
1     4    0    1
2     2    1    0
```

Understand why different algorithms benefit from different representations.

---

# Algorithm Comparison

Create a comparison between the major algorithms:

```text
Algorithm          Purpose
────────────────────────────────────────
BFS                Traversal / unweighted shortest path
DFS                Traversal / graph exploration
Connected          Find disconnected regions
Components

Cycle Detection    Detect cycles
Topological Sort   Order DAG vertices
Dijkstra           Single-source shortest path
Bellman-Ford       Shortest path with negative edges
Floyd-Warshall     All-pairs shortest path
Prim               Minimum spanning tree
Kruskal            Minimum spanning tree
SCC                Strong connectivity
A*                 Heuristic pathfinding
```

Compare their properties:

```text
Algorithm       Directed   Weighted   Negative
────────────────────────────────────────────────
BFS             Yes        No         No
DFS             Yes        No         No
Dijkstra        Yes        Yes        No
Bellman-Ford    Yes        Yes        Yes
Floyd-Warshall  Yes        Yes        Yes
Prim            No         Yes        No
Kruskal         No         Yes        No
A*              Yes        Yes        Usually No
```

---

# Edge Cases

Your implementations should handle:

* Empty graphs.
* A graph containing one vertex.
* Disconnected graphs.
* Graphs containing isolated vertices.
* Duplicate edges.
* Self-loops.
* Cyclic graphs.
* Acyclic graphs.
* Directed graphs.
* Undirected graphs.
* Unweighted graphs.
* Weighted graphs.
* Unreachable vertices.
* Zero-weight edges.
* Negative-weight edges where supported.
* Negative cycles where applicable.
* Graphs containing multiple valid topological orderings.
* Graphs where no MST exists because the graph is disconnected.

---

# Complexity Analysis

For every algorithm, record:

```text
Algorithm:
Purpose:
Graph Type:
Data Structure Used:
Time Complexity:
Space Complexity:
Limitations:
```

Pay particular attention to why:

```text
Dijkstra ≠ Bellman-Ford ≠ Floyd-Warshall
```

and:

```text
Prim ≠ Kruskal
```

even though some of them solve related problems.

---

# Implementation Requirements

Implement the algorithms in:

```text
C
C++
Python
```

Do not use libraries that directly implement the algorithms.

Implement the core graph logic yourself.

Use:

```text
Adjacency Lists
Adjacency Matrices
Queues
Stacks / Recursion
Priority Queues
Disjoint Set Union
```

where appropriate.

---

# Recommended Implementation Order

Implement the algorithms in this order:

```text
1. Connected Components
       ↓
2. Cycle Detection
       ↓
3. Topological Sort
       ↓
4. Dijkstra
       ↓
5. Bellman-Ford
       ↓
6. Floyd-Warshall
       ↓
7. Prim
       ↓
8. Kruskal
       ↓
9. Strongly Connected Components
       ↓
10. A*
```

This order gradually introduces the machinery required by the later algorithms.

---

# Goal

By the end of this chapter, you should be able to look at a graph problem and determine:

```text
What type of graph is this?
        ↓
Directed or undirected?
        ↓
Weighted or unweighted?
        ↓
Are negative weights possible?
        ↓
Do I need traversal?
        ↓
Do I need shortest paths?
        ↓
Do I need an MST?
        ↓
Do I need connectivity analysis?
        ↓
Which algorithm fits?
```

The larger picture is:

```text
                         GRAPH
                           │
          ┌────────────────┼────────────────┐
          │                │                │
       Traverse         Shortest          Structure
          │               Paths               │
       ┌──┴──┐       ┌────┼────┐        ┌────┼────┐
       BFS  DFS       │    │    │        │    │    │
                      │    │    │       MST  SCC  DAG
                  Dijkstra │ Floyd       │         │
                           │              │    Topological
                     Bellman-Ford      Prim
                                      Kruskal
```

The objective is not to memorize graph algorithms individually. It is to recognize the **structure of a graph problem** and select the appropriate algorithm for it.