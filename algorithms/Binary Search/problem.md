# Binary Search

## Problem

Given a **sorted** array of integers and a target value, find the position of the target using the **Binary Search** algorithm.

Binary Search repeatedly divides the search range in half. At each step, it compares the target with the middle element:

* If the middle element equals the target, return its index.
* If the target is smaller, continue searching the left half.
* If the target is larger, continue searching the right half.

If the target is not present, return `-1`.

If the target appears multiple times, return the index of **any occurrence**.

### Requirements

* Implement Binary Search from scratch.
* Do not use built-in search or lookup functions.
* The input array must be sorted in ascending order.
* Use an iterative approach.
* Return the index of the target if it exists.
* Return `-1` if the target does not exist.
* An empty array should return `-1`.

### Input

A sorted array of `n` integers and a target integer.

### Output

The zero-based index of the target.

If the target is not present, return:

```text id="q8m2vr"
-1
```

### Example 1

**Input:**

```text id="x4k7pz"
Array:  [1, 3, 5, 7, 9, 11, 13]
Target: 7
```

**Output:**

```text id="n6w3tc"
3
```

### Example 2

**Input:**

```text id="f2q9mb"
Array:  [1, 3, 5, 7, 9, 11, 13]
Target: 8
```

**Output:**

```text id="v5r1kx"
-1
```

### Example 3

**Input:**

```text id="j7c4dh"
Array:  [2, 4, 6, 8, 10, 12]
Target: 2
```

**Output:**

```text id="p3m8qy"
0
```

### Example 4

**Input:**

```text id="s9t2wf"
Array:  []
Target: 10
```

**Output:**

```text id="k6x4bn"
-1
```

## How It Works

Given:

```text id="h5v8qp"
Array:  [1, 3, 5, 7, 9, 11, 13]
Target: 11

             middle
                ↓
[1, 3, 5, 7, 9, 11, 13]
          ↑
         7

11 > 7
→ discard the left half

[9, 11, 13]
    ↑
   11

11 == 11
→ found at index 5
```

Instead of checking every element, Binary Search eliminates half of the remaining search space after every comparison.

## Constraints

* `0 <= n <= 100000`
* The array is sorted in ascending order.
* Each element is an integer.
* The target is an integer.
* Elements may be positive, negative, or zero.
* Duplicate values may occur.

## Complexity Requirement

Your implementation should have:

* **Best-case time complexity:** `O(1)`
* **Average-case time complexity:** `O(log n)`
* **Worst-case time complexity:** `O(log n)`
* **Space complexity:** `O(1)` auxiliary space