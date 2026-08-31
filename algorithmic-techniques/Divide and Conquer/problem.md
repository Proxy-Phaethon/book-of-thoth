# Divide & Conquer

## Problem

Implement a collection of algorithms using the **Divide & Conquer** paradigm.

Divide & Conquer solves a problem by:

```text
┌─────────────────────┐
│   Original Problem  │
└──────────┬──────────┘
           │
        DIVIDE
           ▼
   ┌───────┴───────┐
   ▼               ▼
┌──────┐        ┌──────┐
│Sub 1 │        │Sub 2 │
└──┬───┘        └──┬───┘
   │               │
   └───────┬───────┘
           │
         CONQUER
           │
           ▼
        COMBINE
           │
           ▼
   ┌─────────────────┐
   │     Solution    │
   └─────────────────┘
```

For this chapter, implement:

* Merge Sort.
* Binary Search.
* Maximum Subarray.
* Fast Exponentiation.
* Find the Maximum Element.

The implementations should use the Divide & Conquer approach rather than simply solving the entire problem iteratively.

## 1. Merge Sort

Sort an array using Merge Sort.

Merge Sort follows three steps:

```text
Divide
    ↓
Split the array into two halves.

Conquer
    ↓
Recursively sort both halves.

Combine
    ↓
Merge the two sorted halves.
```

Example:

```text
[8, 3, 5, 4, 7, 6, 1, 2]

             ↓ divide

[8, 3, 5, 4]       [7, 6, 1, 2]

       ↓                 ↓

[8, 3] [5, 4]       [7, 6] [1, 2]

       ↓                 ↓

[3, 8] [4, 5]       [6, 7] [1, 2]

             ↓ combine

[3, 4, 5, 8]       [1, 2, 6, 7]

             ↓

[1, 2, 3, 4, 5, 6, 7, 8]
```

The resulting array must be sorted in ascending order.

## 2. Binary Search

Search for a target value in a **sorted array** using Divide & Conquer.

At each step:

1. Find the middle element.
2. Compare it with the target.
3. If the target is smaller, search the left half.
4. If the target is larger, search the right half.
5. If they are equal, return its index.

Example:

```text
Array:

[10, 20, 30, 40, 50, 60, 70]

Target = 60

            40
           /  \
         <      >
        left   right

                 60
                 ↑
               found
```

Return the index of the target, or `-1` if it does not exist.

## 3. Maximum Subarray

Given an integer array, find the **contiguous subarray with the largest possible sum**.

Use Divide & Conquer.

For an array:

```text
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
```

The maximum-sum subarray is:

```text
[4, -1, 2, 1]
```

Its sum is:

```text
6
```

The problem should be divided into:

```text
┌─────────────────────────────┐
│       Entire Array          │
└──────────────┬──────────────┘
               │
             DIVIDE
               ▼
       ┌───────┴───────┐
       ▼               ▼
  Left Half       Right Half
       │               │
       └───────┬───────┘
               ▼
       Crossing Subarray
               │
               ▼
       Maximum of the 3
```

For each division, calculate:

* Maximum subarray entirely in the left half.
* Maximum subarray entirely in the right half.
* Maximum subarray crossing the midpoint.

Return the largest of the three.

## 4. Fast Exponentiation

Calculate:

```text
base^exponent
```

using Divide & Conquer.

Instead of calculating:

```text
x^n = x × x × x × ... × x
```

reduce the exponent by half.

For an even exponent:

```text
x^n = (x^(n/2))²
```

For an odd exponent:

```text
x^n = x × (x^(n/2))²
```

Example:

```text
2^8

        2^8
         │
         ▼
        2^4
         │
         ▼
        2^2
         │
         ▼
        2^1
         │
         ▼
        2^0
```

This reduces the number of multiplications dramatically.

## 5. Maximum Element

Find the maximum element in an array using Divide & Conquer.

Example:

```text
[7, 2, 9, 4, 1, 8]

             ↓

       [7, 2, 9]   [4, 1, 8]

          ↓             ↓

        max=9         max=8

             ↓

            9
```

The array should be recursively divided until individual elements remain.

Then combine the results by comparing the maximum values from each half.

## Divide & Conquer Pattern

A typical Divide & Conquer algorithm follows:

```text
function solve(problem):

    if problem is small enough:
        return direct_solution(problem)

    divide problem into subproblems

    solve each subproblem recursively

    combine the results

    return result
```

The three fundamental stages are:

```text
       ┌─────────┐
       │ DIVIDE  │
       └────┬────┘
            ↓
       ┌─────────┐
       │ CONQUER │
       └────┬────┘
            ↓
       ┌─────────┐
       │ COMBINE │
       └─────────┘
```

Not every Divide & Conquer algorithm requires an explicit combine step. Binary Search, for example, discards one half and continues with the other.

## Edge Cases

Your implementations should correctly handle:

* An empty array.
* An array containing one element.
* An already sorted array.
* A reverse-sorted array.
* Duplicate values.
* Negative values.
* Arrays containing only negative values.
* Arrays containing zero.
* A target that does not exist.
* A target at the first index.
* A target at the final index.
* `power(base, 0)`.
* `power(0, exponent)` where appropriate.

## Constraints

* Array size may be up to `100000`.
* Array elements are integers.
* Duplicate values are allowed.
* Binary Search receives a sorted array.
* Do not use built-in sorting functions.
* The required algorithms should use recursive Divide & Conquer.

## Complexity Requirements

| Algorithm           |         Time | Auxiliary Space |
| ------------------- | -----------: | --------------: |
| Merge Sort          | `O(n log n)` |          `O(n)` |
| Binary Search       |   `O(log n)` |      `O(log n)` |
| Maximum Subarray    | `O(n log n)` |      `O(log n)` |
| Fast Exponentiation |   `O(log n)` |      `O(log n)` |
| Maximum Element     |       `O(n)` |      `O(log n)` |