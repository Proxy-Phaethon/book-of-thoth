# Linear Search

## Problem

Given an array of integers and a target value, find the position of the target using the **Linear Search** algorithm.

Linear Search examines each element in the array sequentially, starting from the first element, until the target is found or the end of the array is reached.

If the target appears multiple times, return the index of its **first occurrence**.

### Requirements

* Implement Linear Search from scratch.
* Do not use built-in search or lookup functions.
* Search the array from left to right.
* Return the index of the first occurrence of the target.
* Return `-1` if the target does not exist in the array.
* An empty array should return `-1`.

### Input

An array of `n` integers and a target integer.

### Output

The zero-based index of the first occurrence of the target.

If the target is not present, return:

```text
-1
```

### Example 1

**Input:**

```text id="l3x8q1"
Array:  [10, 25, 7, 42, 18]
Target: 42
```

**Output:**

```text id="w7k2pz"
3
```

### Example 2

**Input:**

```text id="m8v4tc"
Array:  [10, 25, 7, 42, 18]
Target: 15
```

**Output:**

```text id="q2n6xr"
-1
```

### Example 3

**Input:**

```text id="f9k3dw"
Array:  [5, 3, 8, 3, 9]
Target: 3
```

**Output:**

```text id="r4p7mb"
1
```

The first `3` occurs at index `1`, so the second occurrence is ignored.

### Example 4

**Input:**

```text id="t6y2qh"
Array:  []
Target: 10
```

**Output:**

```text id="j8c5vn"
-1
```

## How It Works

Given:

```text id="x5m9kp"
Array:  [10, 25, 7, 42, 18]
Target: 42

Index:    0   1   2   3   4
          │   │   │   │   │
Search:   10  25  7   42  18
          ✗   ✗   ✗   ✓
                      ↑
                    found
```

The algorithm checks each element in order and stops as soon as the target is found.

## Constraints

* `0 <= n <= 100000`
* Each element is an integer.
* The target is an integer.
* Elements may be positive, negative, or zero.
* Duplicate values may occur.

## Complexity Requirement

Your implementation should have:

* **Best-case time complexity:** `O(1)`
* **Average-case time complexity:** `O(n)`
* **Worst-case time complexity:** `O(n)`
* **Space complexity:** `O(1)` auxiliary space