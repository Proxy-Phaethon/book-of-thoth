# Binary Search Tree

## Problem

Implement a **Binary Search Tree (BST)** from scratch.

A Binary Search Tree is a binary tree where each node follows an ordering rule:

* Values smaller than a node are stored in its **left subtree**.
* Values larger than a node are stored in its **right subtree**.
* For this problem, duplicate values should not be inserted.

Implement the BST with operations for insertion, searching, deletion, and tree traversal.

### Requirements

Implement the following operations:

* **Insert** a value into the BST.
* **Search** for a value.
* **Delete** a value from the BST.
* **In-order traversal**.
* **Pre-order traversal**.
* **Post-order traversal**.
* **Free** all dynamically allocated nodes when the tree is no longer needed.

The implementation should preserve the BST property after every insertion and deletion.

## BST Structure

A BST might look like:

```text
              50
             /  \
           30    70
          / \    / \
        20  40  60  80
```

For every node:

```text
        smaller        larger
           │              │
           ▼              ▼
        ┌─────┐
        │ 50  │
        └─────┘
```

Everything in the left subtree is smaller than `50`, while everything in the right subtree is larger.

## Operations

### Insert

Insert a value while maintaining the BST property.

```text
insert(50)
insert(30)
insert(70)
insert(20)
insert(40)
```

Produces:

```text
        50
       /  \
     30    70
    /  \
  20   40
```

If the value already exists, do not insert another node.

### Search

Search for a value by using the BST ordering property.

```text
        50
       /  \
     30    70
    / \
  20  40
```

Searching for `40`:

```text
40 < 50
→ search left

40 > 30
→ search right

40 == 40
→ found
```

Searching for a value that does not exist should return an appropriate "not found" result.

### Delete

Delete a value while preserving the BST property.

There are three cases.

#### Case 1: Leaf Node

A node with no children can simply be removed.

```text
Before:

    30
   /  \
  20  40

delete(20)

After:

    30
      \
      40
```

#### Case 2: One Child

A node with one child is replaced by its child.

```text
Before:

    30
      \
      40
        \
        50

delete(40)

After:

    30
      \
      50
```

#### Case 3: Two Children

A node with two children should be replaced by its **in-order successor**, the smallest value in its right subtree.

```text
Before:

       50
      /  \
    30    70
         /  \
       60    80

delete(70)

Successor = 80

After:

       50
      /  \
    30    80
         /
        60
```

### In-Order Traversal

Visit:

```text
Left → Root → Right
```

For:

```text
        50
       /  \
     30    70
    / \    / \
  20  40  60  80
```

Output:

```text
20 30 40 50 60 70 80
```

An important property of a BST is that **in-order traversal produces the values in sorted order**.

### Pre-Order Traversal

Visit:

```text
Root → Left → Right
```

For the same tree:

```text
50 30 20 40 70 60 80
```

### Post-Order Traversal

Visit:

```text
Left → Right → Root
```

For the same tree:

```text
20 40 30 60 80 70 50
```

## Example

Perform the following operations:

```text
insert(50)
insert(30)
insert(70)
insert(20)
insert(40)
insert(60)
insert(80)

search(40)
delete(30)
```

Before deletion:

```text
              50
             /  \
           30    70
          / \    / \
        20  40  60  80
```

`search(40)` returns:

```text
found
```

After `delete(30)`:

```text
              50
             /  \
           40    70
          /     / \
        20     60  80
```

In-order traversal:

```text
20 40 50 60 70 80
```

## Edge Cases

Your implementation should correctly handle:

* An empty tree.
* Inserting the first node.
* Searching an empty tree.
* Searching for a value that does not exist.
* Inserting duplicate values.
* Deleting the root node.
* Deleting a leaf node.
* Deleting a node with one child.
* Deleting a node with two children.
* Deleting the only node in the tree.
* Traversing an empty tree.

## Constraints

* The tree may contain up to `100000` nodes.
* Each node stores an integer.
* Values may be positive, negative, or zero.
* Duplicate values are not allowed.

## Complexity Requirements

Let `h` be the height of the tree.

| Operation |    Average | Worst Case |
| --------- | ---------: | ---------: |
| Insert    | `O(log n)` |     `O(n)` |
| Search    | `O(log n)` |     `O(n)` |
| Delete    | `O(log n)` |     `O(n)` |
| Traversal |     `O(n)` |     `O(n)` |

Space complexity:

* Tree storage: `O(n)`
* Recursive traversal stack: `O(h)`

A completely unbalanced BST can have height `O(n)`, while a balanced BST has height `O(log n)`.