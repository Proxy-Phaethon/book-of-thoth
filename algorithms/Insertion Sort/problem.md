# Insertion Sort

## Problem

Given an array of integers, sort the array in ascending order using the **Insertion Sort** algorithm.

You must implement the sorting algorithm yourself. Do not use a built-in sorting function.

## Input

An array of `n` integers.

The values may be positive, negative, or zero.

## Output

The same array, sorted in ascending order.

## Examples

### Example 1

```text
Input:  [5, 2, 4, 6, 1, 3]
Output: [1, 2, 3, 4, 5, 6]
```

### Example 2

```text
Input:  [5, 1, 4, 2, 8]
Output: [1, 2, 4, 5, 8]
```

### Example 3

```text
Input:  [3]
Output: [3]
```

### Example 4

```text
Input:  []
Output: []
```

### Example 5

```text
Input:  [4, 4, 2, 1, 2]
Output: [1, 2, 2, 4, 4]
```

## Requirements

* Implement **Insertion Sort**.
* Sort the array **in place**.
* Do not use a built-in sorting function.
* The algorithm should work with duplicate values.
* The algorithm should work with negative values.
* The algorithm should handle arrays containing zero or one element.

## Goal

Before writing the implementation, identify:

1. What part of the array is already sorted at each iteration?
2. Which element is being inserted?
3. Which elements need to be shifted?
4. When should shifting stop?
5. Where should the selected element be placed?

## Complexity

After implementing the algorithm, determine its:

* Best-case time complexity
* Average-case time complexity
* Worst-case time complexity
* Space complexity

## Notes
the key here is to make a system that can look at a value and compare it to the value to the left of it, and move it based on the given rules, i.e. for ascending order, we want the smallest values to the left. so we need an algorithm to look at a value, compare it to the value to the left, and either move it based on the value or stay neutral.

and then we need to account for the fail cases, such as duplicates, or negative integers, or being a null/zero/only one item.

