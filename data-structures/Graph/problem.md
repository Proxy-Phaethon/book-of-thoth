# Graph

## Problem

Implement a **Graph** data structure from scratch.

A graph consists of **vertices (nodes)** connected by **edges**. Unlike a tree, a graph does not require a root and may contain cycles.

For this problem, implement an **undirected graph** using an **adjacency list**.

The graph should support adding vertices, adding and removing edges, checking whether an edge exists, and traversing the graph using **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**.

### Requirements

Implement the following operations:

* **Add Vertex** to the graph.
* **Add Edge** between two vertices.
* **Remove Edge** between two vertices.
* **Contains Edge** to determine whether two vertices are connected directly.
* **BFS** traversal starting from a given vertex.
* **DFS** traversal starting from a given vertex.
* **Free** all dynamically allocated memory when the graph is no longer needed.

The graph should:

* Be undirected.
* Use an adjacency list.
* Allow multiple disconnected components.
* Prevent duplicate edges.
* Handle attempts to add an edge involving a vertex that does not exist.

## Graph Structure

A graph can be visualized as:

```text
             GRAPH

        ┌─────┐
        │  A  │
        └──┬──┘
           │
      ┌────┴────┐
      │         │
   ┌──▼──┐   ┌──▼──┐
   │  B  │   │  C  │
   └──┬──┘   └──┬──┘
      │         │
      └────┬────┘
           │
        ┌──▼──┐
        │  D  │
        └─────┘
```

The corresponding adjacency list could be:

```text
A → B → C
B → A → D
C → A → D
D → B → C
```

Because the graph is undirected, every edge appears in both vertices' adjacency lists.

For example:

```text
A ─── B
```

is represented as:

```text
A → B
B → A
```

## Operations

### Add Vertex

Add a new vertex to the graph.

```text
add_vertex(A)
add_vertex(B)
add_vertex(C)
```

Produces:

```text
A → NULL
B → NULL
C → NULL
```

Adding the same vertex more than once should not create a duplicate.

### Add Edge

Connect two existing vertices.

```text
add_edge(A, B)
add_edge(A, C)
add_edge(B, D)
```

Produces:

```text
A → B → C
B → A → D
C → A
D → B
```

Since the graph is undirected:

```text
A ─── B
```

means both:

```text
A → B
B → A
```

An edge should not be added if it already exists.

### Remove Edge

Remove the connection between two vertices.

```text
remove_edge(A, B)
```

Before:

```text
A → B → C
B → A → D
```

After:

```text
A → C
B → D
```

The edge must be removed from both adjacency lists.

### Contains Edge

Check whether two vertices are directly connected.

```text
contains_edge(A, B) → true
contains_edge(A, D) → false
```

This operation should not perform a traversal. It only checks the adjacency list of the specified vertex.

## Breadth-First Search

BFS explores the graph **level by level**.

It uses a **queue**.

For:

```text
        A
       / \
      B   C
      |   |
      D   E
```

Starting from `A`:

```text
BFS(A)

A
↓
B C
↓
D E
```

Traversal order:

```text
A B C D E
```

A visited array or equivalent structure must be used to prevent visiting the same vertex multiple times.

## Depth-First Search

DFS explores as far as possible along one path before backtracking.

It can be implemented using:

* Recursion, or
* An explicit stack.

For:

```text
        A
       / \
      B   C
      |   |
      D   E
```

One possible DFS traversal starting from `A` is:

```text
A → B → D → C → E
```

Traversal order:

```text
A B D C E
```

The exact traversal order may depend on the order in which neighboring vertices are stored.

## BFS vs DFS

```text
BFS                          DFS

        A                           A
       / \                         / \
      B   C                       B   C
      |   |                       |
      D   E                       D

A → B → C → D → E             A → B → D → C → E
     │                            │
     ▼                            ▼
   Queue                        Stack /
                                Recursion
```

BFS explores outward from the starting vertex.

DFS follows a path deeply before returning to explore another path.

## Example

Perform the following operations:

```text
add_vertex(A)
add_vertex(B)
add_vertex(C)
add_vertex(D)
add_vertex(E)

add_edge(A, B)
add_edge(A, C)
add_edge(B, D)
add_edge(C, E)
add_edge(D, E)
```

The resulting graph:

```text
        A
       / \
      B   C
      |   |
      D   E
       \ /
        ─
```

Adjacency list:

```text
A → B → C
B → A → D
C → A → E
D → B → E
E → C → D
```

BFS starting at `A`:

```text
A B C D E
```

One possible DFS starting at `A`:

```text
A B D E C
```

Again, DFS order may differ depending on adjacency-list ordering.

## Disconnected Graphs

A graph does not have to be connected.

For example:

```text
A ─── B       C ─── D
```

There are two separate connected components.

A BFS or DFS starting at `A` should only visit:

```text
A B
```

It should not automatically jump to `C`.

## Edge Cases

Your implementation should correctly handle:

* An empty graph.
* Adding the first vertex.
* Adding the same vertex twice.
* Adding an edge between two vertices.
* Adding an edge that already exists.
* Adding an edge involving a nonexistent vertex.
* Removing an edge that does not exist.
* Removing an edge from a nonexistent vertex.
* Searching for an edge that does not exist.
* BFS from a nonexistent vertex.
* DFS from a nonexistent vertex.
* Self-loops.
* Disconnected graphs.
* Graphs containing cycles.
* Graphs with a single vertex.
* Graphs with no edges.

## Constraints

* The graph may contain up to `100000` vertices.
* The graph may contain up to `200000` edges.
* Vertex identifiers are integers.
* Duplicate vertices are not allowed.
* Duplicate edges are not allowed.
* The graph is undirected.

## Complexity Requirements

Let:

* `V` = number of vertices.
* `E` = number of edges.

Using an adjacency-list representation:

| Operation     |     Complexity |
| ------------- | -------------: |
| Add Vertex    | `O(1)` average |
| Add Edge      | `O(degree(V))` |
| Remove Edge   | `O(degree(V))` |
| Contains Edge | `O(degree(V))` |
| BFS           |     `O(V + E)` |
| DFS           |     `O(V + E)` |

Space complexity:

```text
O(V + E)
```