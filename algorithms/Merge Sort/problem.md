# Merge Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Merge Sort** algorithm.

Merge Sort must use the **divide-and-conquer** approach:

1. Divide the array into two halves.
2. Recursively sort each half.
3. Merge the two sorted halves into a single sorted array.

### Requirements

* Implement Merge Sort from scratch.
* Do not use a built-in sorting function.
* The algorithm must sort the array in ascending order.
* The original array should contain the sorted result after the algorithm finishes.

### Input

An array of `n` integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text
[38, 27, 43, 3, 9, 82, 10]
```

**Output:**

```text
[3, 9, 10, 27, 38, 43, 82]
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

### Constraints

* `1 <= n <= 100000`
* Each element is an integer.
* Elements may be positive, negative, or zero.

### Complexity Requirement

Your implementation should have:

* **Time complexity:** `O(n log n)`
* **Space complexity:** `O(n)` auxiliary space