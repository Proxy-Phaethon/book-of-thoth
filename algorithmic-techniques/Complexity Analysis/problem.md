# Complexity Analysis

## Problem

Analyze the **time and space complexity** of common algorithms and data structures.

The goal of this chapter is to learn how to evaluate an algorithm based on how its resource requirements grow as the input size increases.

You should be able to determine:

* Time complexity.
* Space complexity.
* Best-case complexity.
* Average-case complexity.
* Worst-case complexity.
* Asymptotic complexity using **Big O**, **Big Ω**, and **Big Θ** notation.

Do not rely on measuring execution time. Complexity analysis should be based on the structure of the algorithm.

## 1. Basic Growth Rates

Determine the Big O complexity of algorithms exhibiting the following patterns:

```text
O(1)
O(log n)
O(n)
O(n log n)
O(n²)
O(n³)
O(2ⁿ)
O(n!)
```

Order them from fastest-growing efficiency to slowest:

```text
O(1)
  ↓
O(log n)
  ↓
O(n)
  ↓
O(n log n)
  ↓
O(n²)
  ↓
O(n³)
  ↓
O(2ⁿ)
  ↓
O(n!)
```

The goal is to understand how dramatically these growth rates differ as `n` becomes large.

## 2. Constant Time

Analyze the following:

```c
int first = array[0];
```

Determine:

* Time complexity.
* Space complexity.

The operation accesses exactly one element regardless of the array size.

Expected time complexity:

```text
O(1)
```

## 3. Linear Time

Analyze:

```c
for (int i = 0; i < n; i++)
{
    printf("%d\n", array[i]);
}
```

Determine the time complexity.

The loop executes once for every element.

Expected time complexity:

```text
O(n)
```

## 4. Quadratic Time

Analyze:

```c
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
        printf("%d %d\n", i, j);
    }
}
```

Determine:

* Number of iterations.
* Time complexity.
* Space complexity.

Expected time complexity:

```text
O(n²)
```

## 5. Logarithmic Time

Analyze Binary Search:

```text
function binary_search(array, left, right, target):

    if left > right:
        return -1

    middle = (left + right) / 2

    if array[middle] == target:
        return middle

    if target < array[middle]:
        search left half

    otherwise:
        search right half
```

Determine why the time complexity is:

```text
O(log n)
```

Explain how repeatedly dividing the search space by two produces logarithmic growth.

## 6. Sorting Algorithms

Analyze the sorting algorithms implemented in previous chapters:

| Algorithm      |   Best | Average |  Worst |  Space |
| -------------- | -----: | ------: | -----: | -----: |
| Insertion Sort | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Selection Sort | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Bubble Sort    | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Merge Sort     | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Quick Sort     | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Heap Sort      | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Counting Sort  | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |
| Radix Sort     | `O(?)` |  `O(?)` | `O(?)` | `O(?)` |

Fill in the missing complexities and explain why each algorithm has those bounds.

## 7. Searching Algorithms

Analyze:

### Linear Search

```text
Best:
Average:
Worst:
Space:
```

### Binary Search

```text
Best:
Average:
Worst:
Space:
```

Explain why Binary Search requires a sorted input.

## 8. Data Structures

Analyze the operations of the data structures implemented previously.

### Linked List

Determine the complexity of:

* Access.
* Search.
* Insertion at the beginning.
* Insertion at the end.
* Deletion.
* Space usage.

### Stack

Determine the complexity of:

* Push.
* Pop.
* Peek.
* Search.

### Queue

Determine the complexity of:

* Enqueue.
* Dequeue.
* Peek.
* Search.

### Hash Table

Determine the average and worst-case complexity of:

* Insert.
* Search.
* Delete.

Explain why hash-table operations can degrade to `O(n)`.

### Binary Search Tree

Determine the average and worst-case complexity of:

* Search.
* Insert.
* Delete.
* Traversal.

Explain how an unbalanced BST can effectively become a linked list.

### Heap

Determine the complexity of:

* Insert.
* Peek.
* Extract maximum/minimum.
* Build Heap.
* Search.

### Graph

Using an adjacency-list representation, determine the complexity of:

* Add Vertex.
* Add Edge.
* Remove Edge.
* Search for an Edge.
* BFS.
* DFS.

## 9. Space Complexity

Analyze the memory requirements of:

```c
void example(int n)
{
    int x = 10;
}
```

and:

```c
void example(int n)
{
    int array[n];
}
```

Determine why the first uses:

```text
O(1)
```

additional space while the second uses:

```text
O(n)
```

additional space.

## 10. Recursion and Stack Space

Analyze:

```c
int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    return n * factorial(n - 1);
}
```

Determine:

* Time complexity.
* Auxiliary space complexity.
* Maximum recursion depth.

Explain why recursive algorithms can consume additional stack memory even when they do not explicitly allocate memory.

## 11. Recurrence Relations

Analyze the following recursive algorithms.

### Factorial

```text
T(n) = T(n - 1) + O(1)
```

Determine the resulting complexity.

### Binary Search

```text
T(n) = T(n / 2) + O(1)
```

Determine the resulting complexity.

### Merge Sort

```text
T(n) = 2T(n / 2) + O(n)
```

Determine the resulting complexity.

### Fibonacci

```text
T(n) = T(n - 1) + T(n - 2) + O(1)
```

Determine the resulting complexity.

The purpose of this section is to connect recursive code with mathematical complexity analysis.

## 12. Best, Average, and Worst Case

For each algorithm below, identify a possible input producing its best and worst cases:

```text
Insertion Sort
Quick Sort
Linear Search
Binary Search
```

For example, Linear Search:

```text
Best Case:
Target is the first element.

Worst Case:
Target is the final element or does not exist.
```

Explain why different inputs can cause the same algorithm to perform different amounts of work.

## 13. Big O, Big Ω, and Big Θ

Understand the distinction:

```text
Big O
Upper bound.

Big Ω
Lower bound.

Big Θ
Tight bound.
```

For an algorithm that always examines every element:

```text
Θ(n)
```

is more precise than merely saying:

```text
O(n)
```

because the algorithm both requires at most and at least a linear amount of work.

## 14. Complexity Comparison

Suppose an algorithm receives:

```text
n = 1,000,000
```

Compare the approximate number of operations represented by:

```text
O(1)
O(log n)
O(n)
O(n log n)
O(n²)
O(2ⁿ)
```

The goal is to develop an intuition for why asymptotic complexity matters.

## 15. Analyze Your Own Algorithms

Return to every algorithm implemented in the previous chapters.

For each one, record:

```text
Algorithm:
Input Size:
Best Case:
Average Case:
Worst Case:
Time Complexity:
Space Complexity:
```

Then explain which part of the implementation determines each complexity.

## Complexity Rules

Use the following basic rules when analyzing algorithms:

### Sequential Operations

```text
O(n) + O(n)
= O(n)
```

Keep the dominant growth rate.

### Nested Operations

```text
O(n) × O(n)
= O(n²)
```

Nested loops commonly produce multiplicative complexity.

### Dropping Constants

```text
O(2n)
= O(n)

O(500n)
= O(n)
```

Constants are ignored in asymptotic analysis.

### Dropping Lower-Order Terms

```text
O(n² + n)
= O(n²)

O(n³ + n² + n)
= O(n³)
```

Only the dominant growth rate matters.

## Edge Cases

When analyzing an algorithm, consider:

* Empty input.
* One-element input.
* Already sorted input.
* Reverse-sorted input.
* Duplicate values.
* Very large inputs.
* Best-case input.
* Average-case input.
* Worst-case input.
* Recursive depth.
* Additional allocated memory.