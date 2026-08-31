# Dynamic Programming

## Problem

Implement a collection of algorithms using the **Dynamic Programming (DP)** paradigm.

Dynamic programming solves problems by breaking them into smaller subproblems, solving each subproblem once, and storing its result so it does not need to be recomputed.

The two fundamental approaches are:

```text
Top-Down
    ↓
Recursion + Memoization

Bottom-Up
    ↓
Iterative computation + Table
```

The general idea is:

```text
                Problem
                   │
          ┌────────┴────────┐
          ▼                 ▼
    Subproblem 1       Subproblem 2
          │                 │
          └────────┬────────┘
                   ▼
             Store Result
                   │
                   ▼
          Reuse when needed
```

For this chapter, implement:

* Fibonacci using Dynamic Programming.
* 0/1 Knapsack.
* Longest Common Subsequence.
* Longest Increasing Subsequence.
* Coin Change.
* Matrix Chain Multiplication.
* Edit Distance.

---

# 1. Fibonacci

Calculate the `n`th Fibonacci number.

The mathematical definition is:

```text
F(0) = 0
F(1) = 1

F(n) = F(n - 1) + F(n - 2)
```

A naive recursive implementation repeatedly solves the same subproblems.

For example:

```text
              F(5)
             /    \
          F(4)    F(3)
          /  \    /  \
       F(3) F(2) F(2) F(1)
```

`F(3)` and `F(2)` are calculated multiple times.

Use Dynamic Programming to avoid this repetition.

Implement both:

```text
Top-Down
Bottom-Up
```

### Goal

Return `F(n)`.

### Complexity Target

```text
Time:  O(n)
Space: O(n)
```

The bottom-up version may be optimized to:

```text
Time:  O(n)
Space: O(1)
```

---

# 2. 0/1 Knapsack

Given a collection of items, where each item has:

```text
Weight
Value
```

and a knapsack with a maximum capacity, maximize the total value.

Each item can be selected **at most once**.

Example:

```text
Item    Weight    Value

A          1        1
B          3        4
C          4        5
D          5        7

Capacity = 7
```

The solution must determine which combination of items produces the maximum value without exceeding the capacity.

For every item, there are two possibilities:

```text
Take the item
     OR
Skip the item
```

Define:

```text
dp[i][w]
```

as the maximum value obtainable using the first `i` items with capacity `w`.

### Goal

Return the maximum possible value.

### Complexity Target

```text
Time:  O(n × capacity)
Space: O(n × capacity)
```

An optimized implementation may reduce space to:

```text
O(capacity)
```

---

# 3. Longest Common Subsequence

Given two strings, find the length of their **Longest Common Subsequence (LCS)**.

A subsequence does not need to occupy consecutive positions.

Example:

```text
String A:
ABCBDAB

String B:
BDCABA
```

One possible LCS is:

```text
BCBA
```

with length:

```text
4
```

Define:

```text
dp[i][j]
```

as the length of the LCS between:

```text
A[0 ... i-1]
B[0 ... j-1]
```

If the characters match:

```text
dp[i][j] =
    dp[i-1][j-1] + 1
```

Otherwise:

```text
dp[i][j] =
    max(
        dp[i-1][j],
        dp[i][j-1]
    )
```

### Goal

Return:

* The length of the LCS.
* Optionally, reconstruct one actual LCS.

### Complexity Target

```text
Time:  O(m × n)
Space: O(m × n)
```

---

# 4. Longest Increasing Subsequence

Given an array of integers, find the length of the longest subsequence whose values are strictly increasing.

Example:

```text
Array:

10 9 2 5 3 7 101 18
```

One valid LIS is:

```text
2 3 7 101
```

Therefore:

```text
LIS length = 4
```

Define:

```text
dp[i]
```

as the length of the longest increasing subsequence ending at index `i`.

For every previous index `j`:

```text
if array[j] < array[i]:

    dp[i] =
        max(
            dp[i],
            dp[j] + 1
        )
```

### Goal

Return the length of the LIS.

### Complexity Target

The basic Dynamic Programming solution should achieve:

```text
Time:  O(n²)
Space: O(n)
```

Do not use the `O(n log n)` optimization for this chapter unless implementing it as an optional extension.

---

# 5. Coin Change

Given coin denominations and a target amount, determine the minimum number of coins required to produce that amount.

Each coin may be used unlimited times.

Example:

```text
Coins:

1 3 4

Amount:

6
```

The optimal solution is:

```text
3 + 3
```

Therefore:

```text
Minimum coins = 2
```

A greedy strategy would choose:

```text
4 + 1 + 1
```

which requires three coins.

This demonstrates why Dynamic Programming can solve problems where a greedy strategy fails.

Define:

```text
dp[x]
```

as the minimum number of coins needed to create amount `x`.

For every coin:

```text
dp[x] =
    min(
        dp[x],
        dp[x - coin] + 1
    )
```

### Goal

Return the minimum number of coins.

If the amount cannot be formed, return:

```text
-1
```

### Complexity Target

```text
Time:  O(amount × number_of_coins)
Space: O(amount)
```

---

# 6. Matrix Chain Multiplication

Given a sequence of matrices, determine the most efficient order in which to multiply them.

Matrix multiplication is associative:

```text
(A × B) × C
```

produces the same mathematical result as:

```text
A × (B × C)
```

but the number of scalar multiplications can differ significantly.

Example:

```text
A = 10 × 30
B = 30 × 5
C = 5 × 60
```

Consider:

```text
(A × B) × C
```

Cost:

```text
10 × 30 × 5
+
10 × 5 × 60

= 1500 + 3000
= 4500
```

Now consider:

```text
A × (B × C)
```

Cost:

```text
30 × 5 × 60
+
10 × 30 × 60

= 9000 + 18000
= 27000
```

Therefore, the first ordering is significantly cheaper.

Define:

```text
dp[i][j]
```

as the minimum number of scalar multiplications required to multiply matrices `i` through `j`.

Try every possible split:

```text
i ... k | k+1 ... j
```

and select the minimum cost.

### Goal

Return the minimum number of scalar multiplications.

### Complexity Target

```text
Time:  O(n³)
Space: O(n²)
```

---

# 7. Edit Distance

Given two strings, determine the minimum number of operations required to transform one string into another.

Allowed operations:

```text
Insert
Delete
Replace
```

Example:

```text
kitten
```

to:

```text
sitting
```

requires:

```text
kitten
  ↓
sitten     Replace k → s
  ↓
sittin     Replace e → i
  ↓
sitting    Insert g
```

Therefore:

```text
Edit Distance = 3
```

Define:

```text
dp[i][j]
```

as the minimum number of operations required to transform the first `i` characters of one string into the first `j` characters of the other.

If the current characters match:

```text
dp[i][j] =
    dp[i-1][j-1]
```

Otherwise:

```text
dp[i][j] =
    1 + min(
        dp[i-1][j],     // Delete
        dp[i][j-1],     // Insert
        dp[i-1][j-1]    // Replace
    )
```

### Goal

Return the minimum edit distance.

### Complexity Target

```text
Time:  O(m × n)
Space: O(m × n)
```

---

# Dynamic Programming Requirements

For every problem, identify the following four components:

```text
1. State
2. Base Case
3. Transition
4. Final Answer
```

For example, 0/1 Knapsack:

```text
State:
dp[i][w]

Base Case:
dp[0][w] = 0

Transition:
Take or skip the item.

Final Answer:
dp[n][capacity]
```

---

# Top-Down vs Bottom-Up

Implement at least one problem using both approaches.

## Top-Down

Use recursion with memoization:

```text
solve(problem):
    if result already exists:
        return stored result

    calculate result

    store result

    return result
```

## Bottom-Up

Build the solution iteratively:

```text
initialize base cases

for each subproblem:
    calculate result
    store result

return final result
```

Compare the two implementations.

---

# Overlapping Subproblems

Determine whether a problem repeatedly solves the same smaller problems.

For example:

```text
F(5)
├── F(4)
│   ├── F(3)
│   └── F(2)
└── F(3)
    ├── F(2)
    └── F(1)
```

`F(3)` and `F(2)` appear repeatedly.

Dynamic Programming stores these results.

---

# Optimal Substructure

Determine whether an optimal solution can be constructed from optimal solutions to smaller subproblems.

For example, in 0/1 Knapsack:

```text
Optimal solution
       ↓
Optimal subproblem
       ↓
Optimal smaller subproblem
```

Understanding this property is essential for determining whether DP is appropriate.

---

# Greedy vs Dynamic Programming

Compare the two approaches.

```text
Greedy
    ↓
Make one locally optimal choice.
    ↓
Never reconsider it.
```

versus:

```text
Dynamic Programming
    ↓
Explore relevant subproblem choices.
    ↓
Store their optimal results.
    ↓
Combine them into the global optimum.
```

Use the Coin Change example:

```text
Coins = [1, 3, 4]
Amount = 6
```

Greedy:

```text
4 + 1 + 1
= 3 coins
```

Dynamic Programming:

```text
3 + 3
= 2 coins
```

---

# Edge Cases

Your implementations should correctly handle:

* Empty arrays.
* Empty strings.
* One-element arrays.
* One-character strings.
* Zero capacity.
* Zero target amount.
* Items heavier than the knapsack.
* Duplicate items.
* Duplicate coin denominations.
* Impossible coin-change amounts.
* Identical strings.
* Completely different strings.
* Matrices containing only one matrix.
* Increasing arrays.
* Decreasing arrays.
* Arrays containing duplicate values.
* Large input values without unnecessary overflow.

---

# Complexity Analysis

For every algorithm, record:

```text
Algorithm:
State:
Base Case:
Transition:
Time Complexity:
Space Complexity:
```

Pay attention to the difference between:

```text
Naive recursion
Memoized recursion
Bottom-up DP
Space-optimized DP
```

---

# Implementation Requirements

Implement every algorithm in:

```text
C
C++
Python
```

Do not use libraries that directly solve the problems.

For each implementation, prefer writing the DP state and transitions explicitly.

The objective is to understand how the recurrence becomes an algorithm.