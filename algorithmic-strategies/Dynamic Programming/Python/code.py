from dataclasses import dataclass
import heapq

def fibonacci_top_down(n):
    if n < 0:
        return -1

    memo = [-1] * (n + 1)

    def solve(value):
        if value <= 1:
            return value

        if memo[value] != -1:
            return memo[value]

        memo[value] = (
            solve(value - 1) +
            solve(value - 2)
        )

        return memo[value]

    return solve(n)

def fibonacci_bottom_up(n):
    if n < 0:
        return -1

    if n <= 1:
        return n

    previous = 0
    current = 1

    for _ in range(2, n + 1):
        next_value = previous + current

        previous = current
        current = next_value

    return current

def knapsack(weights, values, capacity):
    if capacity <= 0 or not weights:
        return 0

    dp = [0] * (capacity + 1)

    for weight, value in zip(weights, values):
        for current_capacity in range(
            capacity,
            weight - 1,
            -1
        ):
            dp[current_capacity] = max(
                dp[current_capacity],
                value +
                dp[current_capacity - weight]
            )

    return dp[capacity]

def longest_common_subsequence(a, b):
    m = len(a)
    n = len(b)

    dp = [
        [0] * (n + 1)
        for _ in range(m + 1)
    ]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = (
                    dp[i - 1][j - 1] + 1
                )
            else:
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                )

    return dp[m][n]

def longest_increasing_subsequence(array):
    if not array:
        return 0

    n = len(array)
    dp = [1] * n

    longest = 1

    for i in range(n):
        for j in range(i):
            if array[j] < array[i]:
                dp[i] = max(
                    dp[i],
                    dp[j] + 1
                )

        longest = max(
            longest,
            dp[i]
        )

    return longest

def coin_change(coins, amount):
    if amount < 0:
        return -1

    if amount == 0:
        return 0

    if not coins:
        return -1

    impossible = amount + 1

    dp = [impossible] * (amount + 1)

    dp[0] = 0

    for current_amount in range(1, amount + 1):
        for coin in coins:
            if coin <= current_amount:
                dp[current_amount] = min(
                    dp[current_amount],
                    dp[current_amount - coin] + 1
                )

    if dp[amount] == impossible:
        return -1

    return dp[amount]

def matrix_chain_multiplication(dimensions):

    matrix_count = len(dimensions) - 1

    if matrix_count <= 0:
        return 0

    dp = [
        [0] * (matrix_count + 1)
        for _ in range(matrix_count + 1)
    ]

    for length in range(
        2,
        matrix_count + 1
    ):
        for i in range(
            1,
            matrix_count - length + 2
        ):
            j = i + length - 1

            dp[i][j] = float("inf")

            for k in range(i, j):
                cost = (
                    dp[i][k]
                    + dp[k + 1][j]
                    + (
                        dimensions[i - 1]
                        * dimensions[k]
                        * dimensions[j]
                    )
                )

                dp[i][j] = min(
                    dp[i][j],
                    cost
                )

    return dp[1][matrix_count]

def edit_distance(a, b):
    m = len(a)
    n = len(b)

    dp = [
        [0] * (n + 1)
        for _ in range(m + 1)
    ]

    for i in range(m + 1):
        dp[i][0] = i

    for j in range(n + 1):
        dp[0][j] = j

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = (
                    dp[i - 1][j - 1]
                )
            else:
                dp[i][j] = 1 + min(
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                )

    return dp[m][n]

if __name__ == "__main__":

    n = 10

    print(
        "Fibonacci Top-Down:",
        fibonacci_top_down(n)
    )

    print(
        "Fibonacci Bottom-Up:",
        fibonacci_bottom_up(n)
    )

    weights = [
        1, 3, 4, 5
    ]

    values = [
        1, 4, 5, 7
    ]

    capacity = 7

    print(
        "\n0/1 Knapsack:",
        knapsack(
            weights,
            values,
            capacity
        )
    )

    string_a = "ABCBDAB"
    string_b = "BDCABA"

    print(
        "Longest Common Subsequence:",
        longest_common_subsequence(
            string_a,
            string_b
        )
    )

    sequence = [
        10, 9, 2, 5,
        3, 7, 101, 18
    ]

    print(
        "Longest Increasing Subsequence:",
        longest_increasing_subsequence(
            sequence
        )
    )

    coins = [
        1, 3, 4
    ]

    amount = 6

    print(
        "Coin Change:",
        coin_change(
            coins,
            amount
        ),
        "coins"
    )

    dimensions = [
        10, 30, 5, 60
    ]

    print(
        "Matrix Chain Multiplication:",
        matrix_chain_multiplication(
            dimensions
        )
    )

    source = "kitten"
    target = "sitting"

    print(
        "Edit Distance:",
        edit_distance(
            source,
            target
        )
    )