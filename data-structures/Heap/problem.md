# Heap

## Problem

Implement a **Binary Heap** from scratch.

A heap is a complete binary tree that satisfies the **heap property**.

For this problem, implement a **Max Heap**, where every parent node is greater than or equal to its children.

The heap should be stored using an **array**, rather than explicit tree nodes.

### Requirements

Implement the following operations:

* **Insert** a value into the heap.
* **Extract Max** to remove and return the largest value.
* **Peek Max** to view the largest value without removing it.
* **Heapify** to restore the heap property.
* **Is Empty** to determine whether the heap contains any elements.
* **Size** to return the number of elements.
* **Free** all dynamically allocated memory when the heap is no longer needed.

The heap should automatically grow when its capacity is reached.

## Heap Structure

A Max Heap might look like:

```text
              90
            /    \
          70      80
         /  \    /  \
       40   50  60   30
```

Every parent is greater than or equal to its children:

```text
90 ≥ 70, 80
70 ≥ 40, 50
80 ≥ 60, 30
```

The heap does **not** require the entire tree to be sorted.

Only the parent-child relationship matters.

## Array Representation

A binary heap can be represented using an array:

```text
Tree:

              90
            /    \
          70      80
         /  \    /  \
       40   50  60   30

Array:

[90, 70, 80, 40, 50, 60, 30]
```

For an element at index `i`:

```text
Parent:      (i - 1) / 2
Left child:  2 * i + 1
Right child: 2 * i + 2
```

For example, the element at index `1`:

```text
        90
       /
     70
```

has:

```text
Parent index = (1 - 1) / 2 = 0
Left child   = 2(1) + 1 = 3
Right child  = 2(1) + 2 = 4
```

## Operations

### Insert

Add a value to the end of the array, then move it upward until the heap property is restored.

This process is called **sift up** or **bubble up**.

```text
Before:

        80
       /  \
     50    70
    /
   20

insert(90)

Add 90:

        80
       /  \
     50    70
    / \
   20 90

Sift up:

        90
       /  \
     50    70
    /
   20
```

The resulting heap is:

```text
[90, 50, 70, 20]
```

### Extract Max

Remove the root, which contains the largest value.

Replace it with the final element and restore the heap property by moving it downward.

This process is called **sift down**.

```text
Before:

        90
       /  \
     70    80
    / \    /
   40 50  60

Extract Max → 90

Move last element to root:

        60
       /  \
     70    80
    / \
   40 50

Sift down:

        80
       /  \
     70    60
    / \
   40 50
```

### Peek Max

Return the root without removing it.

```text
Heap:

        90
       /  \
     70    80

peek_max()

Result: 90
```

### Is Empty

Return whether the heap contains zero elements.

```text
is_empty() → true
```

### Size

Return the number of elements currently stored.

```text
Heap:

[90, 70, 80, 40, 50]

size() → 5
```

## Heapify

Given an arbitrary array, transform it into a valid Max Heap.

For example:

```text
Input:

[20, 50, 10, 40, 30]
```

After heapification:

```text
        50
       /  \
     40    10
    / \
   20 30
```

Array representation:

```text
[50, 40, 10, 20, 30]
```

Heapify should be performed from the last non-leaf node toward the root.

The last non-leaf node is:

```text
(n / 2) - 1
```

where `n` is the number of elements.

## Example

Perform the following operations:

```text
insert(40)
insert(20)
insert(70)
insert(10)
insert(90)
insert(50)

peek_max()
extract_max()
size()
```

After insertion, the heap should satisfy:

```text
        90
       /  \
     70    50
    / \    /
   10 20  40
```

The operations produce:

```text
peek_max()   → 90
extract_max() → 90
size()        → 5
```

The resulting heap is:

```text
        70
       /  \
     40    50
    / \
   10 20
```

## Edge Cases

Your implementation should correctly handle:

* Creating an empty heap.
* Inserting the first element.
* Extracting from an empty heap.
* Peeking at an empty heap.
* Extracting the final element.
* Inserting duplicate values.
* Negative values.
* A heap containing one element.
* Growing the underlying array.
* Heapifying an empty array.
* Heapifying an already valid heap.
* Heapifying an arbitrary array.

## Constraints

* The heap may contain up to `100000` elements.
* Each element is an integer.
* Values may be positive, negative, or zero.
* Duplicate values are allowed.

## Complexity Requirements

| Operation   | Complexity |
| ----------- | ---------: |
| Insert      | `O(log n)` |
| Extract Max | `O(log n)` |
| Peek Max    |     `O(1)` |
| Heapify     |     `O(n)` |
| Is Empty    |     `O(1)` |
| Size        |     `O(1)` |

Space complexity should be `O(n)` for the heap elements.