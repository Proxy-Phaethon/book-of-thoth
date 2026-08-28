# Breadth-First Search

## Problem

Given an **undirected graph** and a starting vertex, perform a **Breadth-First Search (BFS)** traversal of the graph.

Breadth-First Search explores a graph **level by level**. Starting from the given vertex, it visits all directly connected vertices before moving on to vertices that are farther away.

For this problem, represent the graph using an **adjacency list** and use a **queue** to manage the vertices that need to be visited.

Return the vertices in the order they are visited.

### Requirements

* Implement Breadth-First Search from scratch.
* Represent the graph using an adjacency list.
* Use a queue to manage the traversal.
* Maintain a visited structure to avoid visiting vertices more than once.
* Begin the traversal at the specified starting vertex.
* Visit adjacent vertices in the order they appear in the adjacency list.
* Return or print the traversal order.
* If the starting vertex has no edges, return only that vertex.
* Handle disconnected graphs by traversing only the component containing the starting vertex.

### Input

An undirected graph represented as an adjacency list and a starting vertex.

For example:

```text id="v6t2pn"
0 → [1, 2]
1 → [0, 3, 4]
2 → [0, 5]
3 → [1]
4 → [1, 5]
5 → [2, 4]
```

Starting vertex:

```text id="q9k4wx"
0
```

### Output

The vertices in the order they are visited.

### Example 1

**Input:**

```text id="r5m8cz"
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

```text id="x2v7nb"
0 1 2 3 4 5
```

### Example 2

**Input:**

```text id="d8p3qy"
Graph:

0 → [1, 2]
1 → [0, 3]
2 → [0, 4]
3 → [1]
4 → [2]

Start: 0
```

**Output:**

```text id="m4k9tw"
0 1 2 3 4
```

### Example 3

**Input:**

```text id="h7c2vx"
Graph:

0 → [1]
1 → [0]
2 → [3]
3 → [2]

Start: 2
```

**Output:**

```text id="p5n8zr"
2 3
```

Only the connected component containing the starting vertex is traversed.

## How It Works

Consider the graph:

```text id="j3w6kp"
        0
       / \
      1   2
     / \   \
    3   4   5
         \ /
          ─
```

Starting at `0`, BFS explores the graph one level at a time:

```text id="c8q2mv"
Level 0:        0

Level 1:      1   2

Level 2:    3  4   5
```

The traversal becomes:

```text id="n5x7bd"
0 → 1 → 2 → 3 → 4 → 5
```

The queue drives the traversal:

```text id="z4k9rp"
Visit 0
Queue: [1, 2]

Visit 1
Queue: [2, 3, 4]

Visit 2
Queue: [3, 4, 5]

Visit 3
Queue: [4, 5]

...
```

A vertex is marked as visited when it is added to the queue. This prevents cycles from causing the traversal to repeatedly visit the same vertices.

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