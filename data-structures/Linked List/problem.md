# Linked List

## Problem

Implement a **singly linked list** from scratch.

A linked list is a linear data structure made up of nodes. Each node stores a value and a pointer or reference to the next node in the sequence.

Unlike an array, the nodes do not need to occupy contiguous memory.

For this problem, implement a linked list that supports basic insertion, deletion, searching, and traversal operations.

### Requirements

Implement the following operations:

* **Append** a value to the end of the list.
* **Prepend** a value to the beginning of the list.
* **Insert** a value at a specified index.
* **Delete** the first node containing a specified value.
* **Search** for a value and return its index.
* **Print** all values in the list in order.
* **Free** all allocated memory when the list is no longer needed.

The list should support duplicate values.

When deleting a value that occurs multiple times, delete only its **first occurrence**.

When searching for a value that occurs multiple times, return the index of its **first occurrence**.

### Node Structure

Each node contains:

```text id="k8v3mp"
┌───────────┬───────────┐
│   value   │    next   │
└───────────┴─────┬─────┘
                  │
                  ▼
```

A complete list might look like:

```text id="p4x7zn"
HEAD
 │
 ▼
┌─────┬─────┐    ┌─────┬─────┐    ┌─────┬─────┐
│  10 │  ●──┼───►│  20 │  ●──┼───►│  30 │ NULL│
└─────┴─────┘    └─────┴─────┘    └─────┴─────┘
```

## Operations

### Append

Add a value to the end of the list.

```text id="f2c9qw"
Before:

10 → 20 → 30 → NULL

append(40)

After:

10 → 20 → 30 → 40 → NULL
```

### Prepend

Add a value to the beginning of the list.

```text id="n7v4kx"
Before:

10 → 20 → 30 → NULL

prepend(5)

After:

5 → 10 → 20 → 30 → NULL
```

### Insert

Insert a value at a specified zero-based index.

```text id="c6m8rt"
Before:

10 → 20 → 30 → NULL

insert(15, 1)

After:

10 → 15 → 20 → 30 → NULL
```

If the index is invalid, the list should remain unchanged.

### Delete

Delete the first node containing the specified value.

```text id="w3p9bd"
Before:

10 → 20 → 30 → 20 → NULL

delete(20)

After:

10 → 30 → 20 → NULL
```

If the value does not exist, the list should remain unchanged.

### Search

Return the zero-based index of the first occurrence of a value.

```text id="r5k2vz"
List:

10 → 20 → 30 → 40 → NULL

search(30)

Result:

2
```

If the value does not exist, return:

```text id="x8q4nm"
-1
```

### Print

Traverse the list from `HEAD` to `NULL` and print every value.

For:

```text id="a7d3kp"
10 → 20 → 30 → NULL
```

The output should be:

```text
10 20 30
```

## Example

### Input

Perform the following operations:

```text id="m4z8qx"
append(10)
append(20)
append(30)

prepend(5)

insert(15, 2)

delete(20)

search(30)
```

### List After Operations

```text id="v6p2cn"
5 → 10 → 15 → 30 → NULL
```

### Output

```text id="j9w4rt"
Search result: 3
List: 5 10 15 30
```

## Edge Cases

Your implementation should correctly handle:

* An empty list.
* A list containing one node.
* Inserting into an empty list.
* Inserting at index `0`.
* Inserting at the end of the list.
* Deleting the head node.
* Deleting the only node.
* Deleting a value that does not exist.
* Searching an empty list.
* Duplicate values.
* Invalid insertion indices.

## Constraints

* The list may contain up to `100000` nodes.
* Each node stores an integer.
* Values may be positive, negative, or zero.
* Duplicate values are allowed.

## Complexity Requirements

For a singly linked list:

| Operation | Expected Complexity |
| --------- | ------------------: |
| Append    |              `O(n)` |
| Prepend   |              `O(1)` |
| Insert    |              `O(n)` |
| Delete    |              `O(n)` |
| Search    |              `O(n)` |
| Traversal |              `O(n)` |

Auxiliary space should be `O(1)` for individual operations, excluding the memory occupied by the nodes themselves.