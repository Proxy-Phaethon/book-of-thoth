# Counting Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Counting Sort** algorithm.

Counting Sort does not compare elements directly. Instead, it counts how many times each value occurs and uses those counts to reconstruct the sorted array.

For this problem, implement Counting Sort for integer arrays containing **non-negative values**.

### Requirements

* Implement Counting Sort from scratch.
* Do not use a built-in sorting function.
* Sort the array in ascending order.
* Modify the original array with the sorted result.
* Determine the required counting range from the input.
* Correctly handle duplicate values.
* Correctly handle arrays containing only one unique value.
* An empty array should remain unchanged.

### Input

An array of `n` non-negative integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text id="j0ck8z"
[4, 2, 2, 8, 3, 3, 1]
```

**Output:**

```text id="xq1k5v"
[1, 2, 2, 3, 3, 4, 8]
```

### Example 2

**Input:**

```text id="y0xw2m"
[5, 5, 3, 1, 0, 2, 5]
```

**Output:**

```text id="3k5x9r"
[0, 1, 2, 3, 5, 5, 5]
```

### Example 3

**Input:**

```text id="4f9q2c"
[7, 7, 7, 7]
```

**Output:**

```text id="r7w8pz"
[7, 7, 7, 7]
```

### Example 4

**Input:**

```text id="b8q3tw"
[0, 4, 1, 0, 3, 2]
```

**Output:**

```text id="w2z7km"
[0, 0, 1, 2, 3, 4]
```

## How It Works

For the input:

```text id="5gqv2k"
[4, 2, 2, 3, 1, 4]
```

The values range from `1` to `4`.

Count each occurrence:

```text id="1w3c9p"
Value:  1  2  3  4
Count:  1  2  1  2
```

Then reconstruct the array using the counts:

```text id="0b4v6m"
[1, 2, 2, 3, 4, 4]
```

The important idea is that the algorithm uses the **value itself as an index into the counting array**.

## Constraints

* `0 <= n <= 100000`
* Each element is a non-negative integer.
* `0 <= arr[i] <= 100000`
* Duplicate values may occur.

## Complexity Requirement

Let:

* `n` = number of elements
* `k` = range of values from the minimum to maximum element

Your implementation should have:

* **Time complexity:** `O(n + k)`
* **Space complexity:** `O(k)`
* **Stable sorting is not required.**