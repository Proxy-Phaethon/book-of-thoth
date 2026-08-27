# Bubble Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Bubble Sort** algorithm.

Bubble Sort repeatedly compares adjacent elements and swaps them if they are in the wrong order. After each pass through the unsorted portion of the array, the largest remaining element moves to its correct position at the end.

### Requirements

* Implement Bubble Sort from scratch.
* Do not use a built-in sorting function.
* Sort the array in ascending order.
* Perform the sorting **in-place**, modifying the original array.
* Optimize the algorithm by stopping early if a complete pass makes no swaps.

### Input

An array of `n` integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text
[64, 34, 25, 12, 22, 11, 90]
```

**Output:**

```text
[11, 12, 22, 25, 34, 64, 90]
```

### Example 2

**Input:**

```text
[5, 2, 4, 6, 1, 3]
```

**Output:**

```text
[1, 2, 3, 4, 5, 6]
```

### Example 3

**Input:**

```text
[1, 2, 3, 4, 5]
```

**Output:**

```text
[1, 2, 3, 4, 5]
```

### Example 4

**Input:**

```text
[-4, 10, -2, 0, 7]
```

**Output:**

```text
[-4, -2, 0, 7, 10]
```

## Constraints

* `1 <= n <= 100000`
* Each element is an integer.
* Elements may be positive, negative, or zero.

## Complexity Requirement

Your implementation should have:

* **Worst-case time complexity:** `O(n²)`
* **Best-case time complexity:** `O(n)` with the early-termination optimization
* **Space complexity:** `O(1)` auxiliary space