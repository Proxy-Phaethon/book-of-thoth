# Heap Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Heap Sort** algorithm.

Heap Sort uses a **binary heap** to repeatedly extract the largest element and place it at the end of the array.

For this problem, implement Heap Sort using a **max heap**.

The algorithm should:

1. Build a max heap from the input array.
2. Move the largest element, located at the root of the heap, to the end of the unsorted portion.
3. Restore the max-heap property.
4. Repeat until the entire array is sorted.

### Requirements

* Implement Heap Sort from scratch.
* Do not use a built-in sorting function.
* Use a **max heap**.
* Sort the array in ascending order.
* Perform the sorting **in-place**.
* Implement the heap operations yourself.
* Handle arrays containing duplicate values correctly.

### Input

An array of `n` integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text id="6tq6x9"
[12, 11, 13, 5, 6, 7]
```

**Output:**

```text id="yn5e7j"
[5, 6, 7, 11, 12, 13]
```

### Example 2

**Input:**

```text id="g9t2ku"
[4, 10, 3, 5, 1]
```

**Output:**

```text id="0p8g3x"
[1, 3, 4, 5, 10]
```

### Example 3

**Input:**

```text id="1h5kq8"
[5, 2, 4, 6, 1, 3]
```

**Output:**

```text id="0l6k3c"
[1, 2, 3, 4, 5, 6]
```

### Example 4

**Input:**

```text id="p3h8zc"
[-4, 10, -2, 0, 7]
```

**Output:**

```text id="5v6f9n"
[-4, -2, 0, 7, 10]
```

### Example 5

**Input:**

```text id="7x2mqp"
[4, 4, 2, 8, 2, 1]
```

**Output:**

```text id="q8k4vz"
[1, 2, 2, 4, 4, 8]
```

## Heap Representation

Represent the binary heap directly inside the array.

For an element at index `i`:

```text
Parent:      (i - 1) / 2
Left child:  2 * i + 1
Right child: 2 * i + 2
```

For example:

```text
             90
           /    \
         50      70
        /  \    /  \
      20   40  60   30

Array:

[90, 50, 70, 20, 40, 60, 30]
```

## Constraints

* `1 <= n <= 100000`
* Each element is an integer.
* Elements may be positive, negative, or zero.
* Duplicate values may occur.

## Complexity Requirement

Your implementation should have:

* **Time complexity:** `O(n log n)`
* **Space complexity:** `O(1)` auxiliary space.

Heap Sort should maintain `O(n log n)` time complexity even in the worst case.