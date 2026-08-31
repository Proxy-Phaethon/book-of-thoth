# Recursion

## Problem

Implement a collection of recursive algorithms from scratch.

The goal of this chapter is to understand **recursion**, where a function solves a problem by calling itself on a smaller version of that problem.

Every recursive solution must contain:

1. A **base case** that stops the recursion.
2. A **recursive case** that reduces the problem toward the base case.

Do not use loops for the required recursive implementations.

## Requirements

Implement the following recursive functions:

* Calculate the factorial of a non-negative integer.
* Calculate the nth Fibonacci number.
* Calculate the sum of integers from `1` to `n`.
* Calculate the sum of all elements in an array.
* Calculate the power `base^exponent`.
* Calculate the greatest common divisor (GCD) of two integers.
* Reverse a string recursively.

## 1. Factorial

The factorial of `n` is defined as:

```text
n! = n × (n - 1) × (n - 2) × ... × 1
```

With the base case:

```text
0! = 1
```

Example:

```text
factorial(5)

5 × factorial(4)
        ↓
    4 × factorial(3)
            ↓
        3 × factorial(2)
                ↓
            2 × factorial(1)
                    ↓
                1 × factorial(0)
                            ↓
                            1
```

Result:

```text
120
```

## 2. Fibonacci

The Fibonacci sequence is defined as:

```text
F(0) = 0
F(1) = 1

F(n) = F(n - 1) + F(n - 2)
```

The sequence begins:

```text
0 1 1 2 3 5 8 13 21 34 ...
```

Example:

```text
fibonacci(5)

= fibonacci(4) + fibonacci(3)
= (3 + 2)
= 5
```

## 3. Sum from 1 to n

Calculate:

```text
1 + 2 + 3 + ... + n
```

Example:

```text
sum(5)

= 5 + sum(4)
= 5 + 4 + sum(3)
= 5 + 4 + 3 + sum(2)
= 5 + 4 + 3 + 2 + sum(1)
= 15
```

Base case:

```text
sum(1) = 1
```

## 4. Array Sum

Calculate the sum of all elements in an array recursively.

Example:

```text
[2, 4, 6, 8]

sum_array([2, 4, 6, 8])

= 2 + sum_array([4, 6, 8])
= 2 + 4 + sum_array([6, 8])
= 2 + 4 + 6 + sum_array([8])
= 20
```

The recursive call should operate on a progressively smaller portion of the array.

## 5. Power

Calculate:

```text
base^exponent
```

For example:

```text
power(2, 5)

= 2 × power(2, 4)
= 2 × 2 × power(2, 3)
= 2 × 2 × 2 × power(2, 2)
= 2 × 2 × 2 × 2 × power(2, 1)
= 32
```

Base case:

```text
power(base, 0) = 1
```

## 6. Greatest Common Divisor

Calculate the GCD of two integers using the **Euclidean algorithm**:

```text
gcd(a, b) = gcd(b, a % b)
```

The recursion ends when:

```text
b = 0
```

At that point:

```text
gcd(a, 0) = a
```

Example:

```text
gcd(48, 18)

gcd(48, 18)
→ gcd(18, 12)
→ gcd(12, 6)
→ gcd(6, 0)
→ 6
```

## 7. Reverse a String

Reverse a string recursively.

Example:

```text
"hello"

reverse("hello")
→ "olleh"
```

One possible recursive structure:

```text
reverse("hello")
        │
        ├── reverse("ello")
        │       │
        │       ├── reverse("llo")
        │       │       │
        │       │       └── ...
        │       │
        │       └── ...
        │
        └── ...
```

The recursion should continue until the string contains zero or one characters.

## Recursion Structure

A recursive function generally follows this pattern:

```text
function(problem):

    if base_case:
        return result

    smaller_problem = reduce(problem)

    return combine(
        current_work,
        function(smaller_problem)
    )
```

For example:

```text
factorial(n):

    if n == 0:
        return 1

    return n * factorial(n - 1)
```

The important property is that every recursive call moves toward the base case.

## Edge Cases

Your implementations should correctly handle:

* `factorial(0)`
* `factorial(1)`
* `fibonacci(0)`
* `fibonacci(1)`
* `sum(0)`
* An empty array.
* An array containing one element.
* `power(base, 0)`
* `gcd(a, 0)`
* `gcd(0, b)`
* A string containing zero characters.
* A string containing one character.
* Negative values where mathematically appropriate.

## Constraints

* Do not use loops in the required recursive functions.
* Do not use built-in functions that directly perform the required operation.
* Each recursive function must have a clearly defined base case.
* Each recursive call must reduce the size of the problem.
* Use integers unless the operation requires another type.

## Complexity

| Function       |               Time |    Auxiliary Space |
| -------------- | -----------------: | -----------------: |
| Factorial      |             `O(n)` |             `O(n)` |
| Fibonacci      |           `O(2^n)` |             `O(n)` |
| Sum            |             `O(n)` |             `O(n)` |
| Array Sum      |             `O(n)` |             `O(n)` |
| Power          |             `O(n)` |             `O(n)` |
| GCD            | `O(log(min(a,b)))` | `O(log(min(a,b)))` |
| Reverse String |             `O(n)` |             `O(n)` |

The Fibonacci implementation intentionally uses the simple recursive formulation. Optimizing it is a later exercise when studying **Dynamic Programming**.