# Depth-First Search

## Problem

Given an **undirected graph** and a starting vertex, perform a **Depth-First Search (DFS)** traversal of the graph.

Depth-First Search explores as far as possible along one branch before backtracking and exploring the next available branch.

For this problem, represent the graph using an **adjacency list** and implement DFS using an explicit **stack**.

Return or print the vertices in the order they are visited.

### Requirements

* Implement Depth-First Search from scratch.
* Represent the graph using an adjacency list.
* Use a stack to manage the traversal.
* Maintain a visited structure to avoid visiting vertices more than once.
* Begin the traversal at the specified starting vertex.
* Visit adjacent vertices in the order they appear in the adjacency list.
* Return or print the traversal order.
* If the starting vertex has no edges, return only that vertex.
* Handle disconnected graphs by traversing only the component containing the starting vertex.

### Input

An undirected graph represented as an adjacency list and a starting vertex.

For example:

```text
0 → [1, 2]
1 → [0, 3, 4]
2 → [0, 5]
3 → [1]
4 → [1, 5]
5 → [2, 4]
```

Starting vertex:

```text
0
```

### Output

The vertices in the order they are visited.

### Example 1

**Input:**

```text
Graph:

0 → [1, 2]
1 → [0, 3, 4]
2 → [0, 5]
3 → [1]
4 → [1, 5]
5 → [2, 4]

Start: 0
```

**Output:**

```text
0 1 3 4 5 2
```

### Example 2

**Input:**

```text
Graph:

0 → [1, 2]
1 → [0, 3]
2 → [0, 4]
3 → [1]
4 → [2]

Start: 0
```

**Output:**

```text
0 1 3 2 4
```

### Example 3

**Input:**

```text
Graph:

0 → [1]
1 → [0]
2 → [3]
3 → [2]

Start: 2
```

**Output:**

```text
2 3
```

Only the connected component containing the starting vertex is traversed.

### Example 4

**Input:**

```text
Graph:

0 → []
1 → [2]
2 → [1]

Start: 0
```

**Output:**

```text
0
```

## How It Works

Consider the graph:

```text
        0
       / \
      1   2
     / \   \
    3   4   5
         \ /
          ─
```

Starting at `0`, DFS follows one branch as deeply as possible before backtracking:

```text
0
│
└── 1
    │
    └── 3
        │
        └── backtrack
    │
    └── 4
        │
        └── 5
            │
            └── 2
```

The traversal becomes:

```text
0 → 1 → 3 → 4 → 5 → 2
```

The stack drives the traversal:

```text
Visit 0
Stack: [1, 2]

Visit 1
Stack: [2, 3, 4]

Visit 3
Stack: [2, 4]

Visit 4
Stack: [2, 5]

...
```

A vertex is marked as visited when it is added to the stack. This prevents cycles from causing the traversal to repeatedly visit the same vertices.

## Constraints

* `1 <= V <= 100000`
* `0 <= E <= 200000`
* Vertices are numbered from `0` to `V - 1`.
* The graph is undirected.
* The graph may contain cycles.
* The graph may be disconnected.
* The starting vertex is valid.

## Complexity Requirement

Let:

* `V` = number of vertices
* `E` = number of edges

Your implementation should have:

* **Time complexity:** `O(V + E)`
* **Space complexity:** `O(V)`

Each vertex and edge should be processed at most a constant number of times.