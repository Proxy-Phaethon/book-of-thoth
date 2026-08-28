# Radix Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Radix Sort** algorithm.

Radix Sort sorts numbers by processing their individual digits. Starting with the least significant digit, it groups elements according to the current digit and repeatedly sorts by the next digit until all digits have been processed.

For this problem, implement **LSD (Least Significant Digit) Radix Sort** using **Counting Sort** as the stable sorting method for each digit.

### Requirements

* Implement Radix Sort from scratch.
* Do not use a built-in sorting function.
* Use **LSD Radix Sort**.
* Use a stable Counting Sort for each digit.
* Sort the array in ascending order.
* Perform the sorting in-place with respect to the input array.
* Correctly handle duplicate values.
* Correctly handle arrays containing `0`.
* An empty array should remain unchanged.
* For this problem, only **non-negative integers** need to be supported.

### Input

An array of `n` non-negative integers.

### Output

The same array, sorted in ascending order.

### Example 1

**Input:**

```text id="4z7m2p"
[170, 45, 75, 90, 802, 24, 2, 66]
```

**Output:**

```text id="9q3k8v"
[2, 24, 45, 66, 75, 90, 170, 802]
```

### Example 2

**Input:**

```text id="r5t8cx"
[329, 457, 657, 839, 436, 720, 355]
```

**Output:**

```text id="m2v7qp"
[329, 355, 436, 457, 657, 720, 839]
```

### Example 3

**Input:**

```text id="x8k4nz"
[5, 5, 3, 1, 0, 2, 5]
```

**Output:**

```text id="b6q1tw"
[0, 1, 2, 3, 5, 5, 5]
```

### Example 4

**Input:**

```text id="h3p9ds"
[1, 2, 3, 4, 5]
```

**Output:**

```text id="c7w2mk"
[1, 2, 3, 4, 5]
```

## How It Works

Consider:

```text id="a4k8mz"
[170, 45, 75, 90, 802, 24, 2, 66]
```

Radix Sort processes the digits from right to left:

```text id="q9v3hx"
        Ones       Tens       Hundreds
          │          │            │
          ▼          ▼            ▼

        ┌───┐      ┌───┐        ┌───┐
        │ 0 │      │ 0 │        │ 0 │
        │ 1 │      │ 1 │        │ 1 │
        │ 2 │      │ 2 │        │ 2 │
        │...│      │...│        │...│
        │ 9 │      │ 9 │        │ 9 │
        └───┘      └───┘        └───┘
```

After each digit pass, the array becomes more ordered.

For example:

```text id="w7n2fc"
Original:
[170, 45, 75, 90, 802, 24, 2, 66]

After ones:
[170, 90, 802, 2, 24, 45, 75, 66]

After tens:
[802, 2, 24, 45, 66, 170, 75, 90]

After hundreds:
[2, 24, 45, 66, 75, 90, 170, 802]
```

The stability of each digit-level Counting Sort is essential. It preserves the ordering established by previous digit passes.

## Constraints

* `0 <= n <= 100000`
* Each element is a non-negative integer.
* `0 <= arr[i] <= 2³¹ - 1`
* Duplicate values may occur.

## Complexity Requirement

Let:

* `n` = number of elements
* `d` = number of digits in the largest value
* `k` = number of possible digit values (`10` for decimal digits)

Your implementation should have:

* **Time complexity:** `O(d × (n + k))`
* **Space complexity:** `O(n + k)`
* **Stable sorting:** Required for each digit pass.

For fixed-width integers, `d` is bounded, making the algorithm effectively linear with respect to `n`.