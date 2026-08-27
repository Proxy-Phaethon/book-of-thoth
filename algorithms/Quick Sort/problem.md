# Quick Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Quick Sort** algorithm.

Quick Sort uses a **divide-and-conquer** strategy. It selects an element as a **pivot**, partitions the array so that elements smaller than the pivot are placed before it and elements greater than the pivot are placed after it, then recursively sorts the resulting partitions.

### Requirements

* Implement Quick Sort from scratch.
* Do not use a built-in sorting function.
* Sort the array in ascending order.
* Perform the sorting **in-place**.
* Use the **last element as the pivot**.
* Recursively sort the partitions on either side of the pivot.
* Handle arrays containing duplicate values correctly.

### Input

An array of `n` integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text
[10, 7, 8, 9, 1, 5]
```

**Output:**

```text
[1, 5, 7, 8, 9, 10]
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
[4, 2, 4, 1, 3, 4]
```

**Output:**

```text
[1, 2, 3, 4, 4, 4]
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
* Duplicate values may occur.

## Complexity Requirement

Your implementation should have:

* **Average-case time complexity:** `O(n log n)`
* **Worst-case time complexity:** `O(n²)`
* **Space complexity:** `O(log n)` average auxiliary space due to recursion.