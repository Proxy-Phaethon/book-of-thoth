# Greedy Algorithms

## Problem

Implement a collection of algorithms using the **Greedy Algorithm** paradigm.

A greedy algorithm builds a solution step by step by making the **locally optimal choice** at each stage, with the goal of producing a globally optimal solution.

The general pattern is:

```text
┌─────────────────────┐
│    Start Problem    │
└──────────┬──────────┘
           │
           ▼
   ┌───────────────┐
   │ Make the best │
   │ local choice  │
   └───────┬───────┘
           │
           ▼
   ┌───────────────┐
   │ Add choice to │
   │   solution    │
   └───────┬───────┘
           │
           ▼
     More choices?
       /       \
     Yes        No
      │          │
      └──────┐   ▼
             │ Complete
             ▼ Solution
```

For this chapter, implement:

* Activity Selection.
* Fractional Knapsack.
* Job Sequencing with Deadlines.
* Huffman Coding.
* Minimum Spanning Tree using Kruskal's Algorithm.
* Minimum Spanning Tree using Prim's Algorithm.
* Dijkstra's Shortest Path Algorithm.

The goal is not merely to implement them, but to understand **why a greedy choice works** when it does.

---

## 1. Activity Selection

Given a collection of activities, where each activity has:

```text
Start Time
Finish Time
```

select the maximum number of **non-overlapping activities**.

Example:

```text
Activity    Start    Finish

A             1        3
B             2        4
C             3        5
D             5        7
E             8        9
F             5        9
```

A valid maximum selection is:

```text
A → D → E
```

The greedy strategy is:

```text
1. Sort activities by finish time.
2. Select the activity that finishes earliest.
3. Ignore activities that overlap with it.
4. Repeat.
```

### Goal

Return the maximum number of compatible activities.

### Complexity Target

```text
Sorting: O(n log n)
Selection: O(n)

Total: O(n log n)
```

---

## 2. Fractional Knapsack

Given items with:

```text
Value
Weight
```

and a knapsack with limited capacity, maximize the total value.

Unlike the 0/1 Knapsack problem, items may be divided.

Example:

```text
Item    Value    Weight

A        60        10
B       100        20
C       120        30

Capacity = 50
```

Calculate:

```text
Value / Weight
```

for every item and prioritize the item with the highest ratio.

The greedy strategy is:

```text
1. Calculate value/weight for every item.
2. Sort items by ratio.
3. Take the highest-ratio item.
4. If the entire item fits, take it.
5. Otherwise, take the fraction that fits.
6. Continue until the capacity is full.
```

### Goal

Return the maximum possible value.

### Important

Do **not** use the same strategy for the 0/1 Knapsack problem.

The greedy approach works for **Fractional Knapsack**, but not generally for 0/1 Knapsack.

---

## 3. Job Sequencing with Deadlines

Given a collection of jobs where each job has:

```text
Job ID
Deadline
Profit
```

Each job requires exactly one unit of time.

A job earns its profit only if it is completed before or on its deadline.

Example:

```text
Job    Deadline    Profit

A         2          100
B         1           19
C         2           27
D         1           25
E         3           15
```

The objective is to maximize total profit.

Greedy strategy:

```text
1. Sort jobs by decreasing profit.
2. Consider the most profitable job first.
3. Place it in the latest available slot before its deadline.
4. Continue until all jobs have been considered.
```

### Goal

Return:

* The selected jobs.
* The maximum total profit.

### Complexity Target

```text
O(n log n)
```

for the sorting portion, assuming an efficient slot-management implementation.

---

## 4. Huffman Coding

Build a Huffman Tree from characters and their frequencies.

Example:

```text
Character    Frequency

A               5
B               9
C              12
D              13
E              16
F              45
```

Greedy strategy:

```text
1. Put every character into a priority queue.
2. Remove the two nodes with the smallest frequencies.
3. Combine them into a new node.
4. Insert the new node back into the queue.
5. Repeat until one node remains.
```

The final node is the root of the Huffman Tree.

Example structure:

```text
             [100]
             /   \
          [45]    [55]
           F      /  \
                ...  ...
```

Assign:

```text
Left edge  → 0
Right edge → 1
```

to generate prefix-free binary codes.

### Goal

Given character frequencies:

1. Build the Huffman Tree.
2. Generate the binary code for every character.
3. Print the resulting codes.

### Complexity Target

```text
O(n log n)
```

when using a priority queue.

---

## 5. Kruskal's Algorithm

Given a weighted, undirected graph, find its **Minimum Spanning Tree (MST)** using Kruskal's Algorithm.

Example:

```text
       4
   A-------B
   |       |
  2|       |3
   |       |
   C-------D
       1
```

Edges should be sorted by weight.

Greedy strategy:

```text
1. Sort all edges by increasing weight.
2. Consider the smallest edge.
3. Add it if it does not create a cycle.
4. Otherwise discard it.
5. Continue until the MST contains V - 1 edges.
```

A **Disjoint Set Union (DSU)** / **Union-Find** structure should be used to efficiently detect cycles.

### Goal

Return:

* The edges belonging to the MST.
* The total MST weight.

### Complexity Target

```text
O(E log E)
```

---

## 6. Prim's Algorithm

Given a weighted, undirected graph, find its Minimum Spanning Tree using Prim's Algorithm.

Unlike Kruskal's Algorithm, Prim's algorithm grows a single tree.

Greedy strategy:

```text
1. Start from any vertex.
2. Find the minimum-weight edge connecting
   the current tree to an unvisited vertex.
3. Add that edge and vertex to the tree.
4. Repeat until every vertex is included.
```

Example:

```text
             4
        A---------B
        |         |
       2|         |3
        |         |
        C---------D
             1
```

Starting at `A`:

```text
A
│
├── 2 → C
│
└── 4 → B
        │
        └── 3 → D
```

The algorithm must always choose the cheapest edge that expands the current tree.

### Goal

Return:

* The MST edges.
* The total MST weight.

### Complexity Target

With an adjacency matrix:

```text
O(V²)
```

With an adjacency list and priority queue:

```text
O(E log V)
```

---

## 7. Dijkstra's Algorithm

Given a weighted graph and a source vertex, find the shortest distance from the source to every other vertex.

The graph must contain **non-negative edge weights**.

Example:

```text
       4
   A-------B
   |       |
  1|       |2
   |       |
   C-------D
       5
```

Starting from `A`:

```text
A → C = 1
A → B = 4
A → B → D = 6
```

Greedy strategy:

```text
1. Set the source distance to 0.
2. Set all other distances to infinity.
3. Select the unvisited vertex with the smallest
   known distance.
4. Relax its outgoing edges.
5. Mark the vertex as finalized.
6. Repeat.
```

### Goal

Return the shortest distance from the source to every vertex.

### Important

Dijkstra's algorithm does **not** work correctly with negative edge weights.

For graphs containing negative weights, other algorithms such as Bellman-Ford may be required.

### Complexity Target

With an adjacency matrix:

```text
O(V²)
```

With an adjacency list and priority queue:

```text
O((V + E) log V)
```

---

# Greedy Choice

For every greedy algorithm, identify:

```text
1. What is the local choice?
2. Why is this choice attractive?
3. Does the choice eliminate alternatives?
4. Why does the choice lead to an optimal solution?
```

For example, Activity Selection chooses:

```text
The activity that finishes earliest.
```

This leaves the greatest possible amount of time for future activities.

---

# Greedy vs Other Paradigms

Understand the distinction between:

```text
Greedy
   ↓
Make the best local choice.

Divide & Conquer
   ↓
Divide the problem into independent
subproblems and combine their solutions.

Dynamic Programming
   ↓
Solve overlapping subproblems and
reuse their results.
```

A greedy algorithm does **not** automatically produce an optimal solution merely because every individual choice looks good.

---

# Greedy Algorithms That Work

Study why the greedy strategy works for:

```text
Activity Selection
Fractional Knapsack
Huffman Coding
Kruskal's MST
Prim's MST
Dijkstra's Algorithm
```

Identify the mathematical property that permits the greedy strategy.

Common concepts include:

```text
Greedy-choice property
Optimal substructure
Exchange argument
Cut property
```

---

# Counterexample: Greedy Can Fail

Consider the coin denominations:

```text
1, 3, 4
```

Target:

```text
6
```

A greedy strategy chooses:

```text
4 + 1 + 1

3 coins
```

But the optimal solution is:

```text
3 + 3

2 coins
```

Therefore:

```text
Greedy choice ≠ guaranteed optimal solution
```

This is an important part of the chapter.

You should be able to construct examples where a greedy strategy fails.

---

# Edge Cases

Your implementations should correctly handle:

* Empty input.
* One-element input.
* Duplicate values.
* Equal weights.
* Equal profits.
* Equal deadlines.
* Activities with identical start and finish times.
* An activity that starts exactly when another finishes.
* Knapsack capacity of zero.
* Items heavier than the remaining capacity.
* Disconnected graphs.
* Graphs containing isolated vertices.
* Multiple edges between the same vertices.
* Zero-weight edges.
* Zero-value items.
* Dijkstra graphs containing zero-weight edges.
* Negative edges being rejected by Dijkstra's implementation.

---

# Complexity Analysis

For every algorithm, record:

```text
Algorithm:
Input Size:
Greedy Choice:
Best Case:
Average Case:
Worst Case:
Time Complexity:
Space Complexity:
```

Pay particular attention to the cost of sorting and priority queues.

For example:

```text
Activity Selection

Sort:
O(n log n)

Selection:
O(n)

Total:
O(n log n)
```

---

# Implementation Requirements

Implement every algorithm in:

```text
C
C++
Python
```

Do not use built-in implementations of the algorithms.

For sorting, priority queues, and graph operations, implement the underlying structures yourself where practical.

The goal is to understand the mechanics rather than simply calling a library function.

---

# Function Signatures

## C

```c
int activity_selection(
    const Activity *activities,
    int count
);

double fractional_knapsack(
    const Item *items,
    int count,
    double capacity
);

int job_sequencing(
    Job *jobs,
    int count,
    Job *selected
);

void huffman_codes(
    const char *characters,
    const int *frequencies,
    int count
);

int kruskal_mst(
    const Edge *edges,
    int vertex_count,
    int edge_count,
    Edge *mst
);

int prim_mst(
    const Graph *graph,
    int start,
    Edge *mst
);

void dijkstra(
    const Graph *graph,
    int source,
    int *distances
);
```

## C++

```cpp
int activitySelection(
    const std::vector<Activity>& activities
);

double fractionalKnapsack(
    std::vector<Item> items,
    double capacity
);

int jobSequencing(
    std::vector<Job> jobs,
    std::vector<Job>& selected
);

void huffmanCodes(
    const std::vector<char>& characters,
    const std::vector<int>& frequencies
);

std::vector<Edge> kruskalMST(
    int vertexCount,
    std::vector<Edge> edges
);

std::vector<Edge> primMST(
    const Graph& graph,
    int start
);

std::vector<int> dijkstra(
    const Graph& graph,
    int source
);
```

## Python

```python
def activity_selection(activities):
    pass


def fractional_knapsack(items, capacity):
    pass


def job_sequencing(jobs):
    pass


def huffman_codes(characters, frequencies):
    pass


def kruskal_mst(vertices, edges):
    pass


def prim_mst(graph, start):
    pass


def dijkstra(graph, source):
    pass
```