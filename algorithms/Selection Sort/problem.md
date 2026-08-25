# Selection Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Selection Sort** algorithm.

Selection Sort works by repeatedly finding the smallest element in the unsorted portion of the array and placing it at the beginning of that portion.

### Requirements

* Implement Selection Sort from scratch.
* Do not use a built-in sorting function.
* Sort the array in ascending order.
* Perform the sorting **in-place**, modifying the original array.
* Minimize unnecessary swaps by swapping only when the minimum element is not already in the correct position.

### Input

An array of `n` integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text
[64, 25, 12, 22, 11]
```

**Output:**

```text
[11, 12, 22, 25, 64]
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

* **Time complexity:** `O(n²)`
* **Space complexity:** `O(1)` auxiliary space