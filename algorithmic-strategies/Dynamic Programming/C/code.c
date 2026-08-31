#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long fibonacci_top_down_helper(
    int n,
    long long *memo
)
{
    if (n <= 1)
    {
        return n;
    }

    if (memo[n] != -1)
    {
        return memo[n];
    }

    memo[n] =
        fibonacci_top_down_helper(n - 1, memo) +
        fibonacci_top_down_helper(n - 2, memo);

    return memo[n];
}

long long fibonacci_top_down(int n)
{
    if (n < 0)
    {
        return -1;
    }

    long long *memo =
        malloc((n + 1) * sizeof(long long));

    if (memo == NULL)
    {
        return -1;
    }

    for (int i = 0; i <= n; i++)
    {
        memo[i] = -1;
    }

    long long result =
        fibonacci_top_down_helper(n, memo);

    free(memo);

    return result;
}

long long fibonacci_bottom_up(int n)
{
    if (n < 0)
    {
        return -1;
    }

    if (n <= 1)
    {
        return n;
    }

    long long previous = 0;
    long long current = 1;

    for (int i = 2; i <= n; i++)
    {
        long long next =
            previous + current;

        previous = current;
        current = next;
    }

    return current;
}

int knapsack(
    const int *weights,
    const int *values,
    int item_count,
    int capacity
)
{
    if (item_count <= 0 || capacity <= 0)
    {
        return 0;
    }

    int *dp =
        calloc(capacity + 1, sizeof(int));

    if (dp == NULL)
    {
        return -1;
    }

    for (int i = 0; i < item_count; i++)
    {
        for (int w = capacity;
             w >= weights[i];
             w--)
        {
            int include =
                values[i] +
                dp[w - weights[i]];

            if (include > dp[w])
            {
                dp[w] = include;
            }
        }
    }

    int result = dp[capacity];

    free(dp);

    return result;
}

int longest_common_subsequence(
    const char *a,
    const char *b
)
{
    int m = strlen(a);
    int n = strlen(b);

    int *dp =
        calloc(
            (m + 1) * (n + 1),
            sizeof(int)
        );

    if (dp == NULL)
    {
        return -1;
    }

    #define LCS(i, j) dp[(i) * (n + 1) + (j)]

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                LCS(i, j) =
                    LCS(i - 1, j - 1) + 1;
            }
            else
            {
                int skip_a =
                    LCS(i - 1, j);

                int skip_b =
                    LCS(i, j - 1);

                LCS(i, j) =
                    skip_a > skip_b
                        ? skip_a
                        : skip_b;
            }
        }
    }

    int result = LCS(m, n);

    free(dp);

    #undef LCS

    return result;
}

int longest_increasing_subsequence(
    const int *array,
    int size
)
{
    if (size <= 0)
    {
        return 0;
    }

    int *dp =
        malloc(size * sizeof(int));

    if (dp == NULL)
    {
        return -1;
    }

    int longest = 1;

    for (int i = 0; i < size; i++)
    {
        dp[i] = 1;

        for (int j = 0; j < i; j++)
        {
            if (array[j] < array[i] &&
                dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > longest)
        {
            longest = dp[i];
        }
    }

    free(dp);

    return longest;
}

int coin_change(
    const int *coins,
    int coin_count,
    int amount
)
{
    if (amount < 0)
    {
        return -1;
    }

    if (amount == 0)
    {
        return 0;
    }

    if (coin_count <= 0)
    {
        return -1;
    }

    int *dp =
        malloc(
            (amount + 1) * sizeof(int)
        );

    if (dp == NULL)
    {
        return -1;
    }

    for (int i = 0; i <= amount; i++)
    {
        dp[i] = amount + 1;
    }

    dp[0] = 0;

    for (int current = 1;
         current <= amount;
         current++)
    {
        for (int i = 0;
             i < coin_count;
             i++)
        {
            int coin = coins[i];

            if (coin <= current)
            {
                int previous =
                    dp[current - coin];

                if (previous != amount + 1 &&
                    previous + 1 < dp[current])
                {
                    dp[current] =
                        previous + 1;
                }
            }
        }
    }

    int result =
        dp[amount] > amount
            ? -1
            : dp[amount];

    free(dp);

    return result;
}

long long matrix_chain_multiplication(
    const int *dimensions,
    int matrix_count
)
{
    if (matrix_count <= 0)
    {
        return 0;
    }

    long long *dp =
        malloc(
            (matrix_count + 1) *
            (matrix_count + 1) *
            sizeof(long long)
        );

    if (dp == NULL)
    {
        return -1;
    }

    for (int i = 0;
         i <= matrix_count;
         i++)
    {
        for (int j = 0;
             j <= matrix_count;
             j++)
        {
            dp[
                i * (matrix_count + 1) + j
            ] = 0;
        }
    }

    #define MATRIX(i, j) \
        dp[(i) * (matrix_count + 1) + (j)]

    for (int length = 2;
         length <= matrix_count;
         length++)
    {
        for (int i = 1;
             i <= matrix_count - length + 1;
             i++)
        {
            int j =
                i + length - 1;

            MATRIX(i, j) =
                LLONG_MAX;

            for (int k = i;
                 k < j;
                 k++)
            {
                long long cost =
                    MATRIX(i, k) +
                    MATRIX(k + 1, j) +
                    (long long) dimensions[i - 1] *
                    dimensions[k] *
                    dimensions[j];

                if (cost < MATRIX(i, j))
                {
                    MATRIX(i, j) = cost;
                }
            }
        }
    }

    long long result =
        MATRIX(1, matrix_count);

    free(dp);

    #undef MATRIX

    return result;
}

int edit_distance(
    const char *a,
    const char *b
)
{
    int m = strlen(a);
    int n = strlen(b);

    int *dp =
        malloc(
            (m + 1) *
            (n + 1) *
            sizeof(int)
        );

    if (dp == NULL)
    {
        return -1;
    }

    #define EDIT(i, j) dp[(i) * (n + 1) + (j)]

    for (int i = 0; i <= m; i++)
    {
        EDIT(i, 0) = i;
    }

    for (int j = 0; j <= n; j++)
    {
        EDIT(0, j) = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                EDIT(i, j) =
                    EDIT(i - 1, j - 1);
            }
            else
            {
                int delete =
                    EDIT(i - 1, j);

                int insert =
                    EDIT(i, j - 1);

                int replace =
                    EDIT(i - 1, j - 1);

                int minimum = delete;

                if (insert < minimum)
                {
                    minimum = insert;
                }

                if (replace < minimum)
                {
                    minimum = replace;
                }

                EDIT(i, j) =
                    minimum + 1;
            }
        }
    }

    int result =
        EDIT(m, n);

    free(dp);

    #undef EDIT

    return result;
}

void print_array(
    const int *array,
    int size
)
{
    printf("[");

    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);

        if (i < size - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}

int main(void)
{

    int n = 10;

    printf(
        "Fibonacci Top-Down: %lld\n",
        fibonacci_top_down(n)
    );

    printf(
        "Fibonacci Bottom-Up: %lld\n",
        fibonacci_bottom_up(n)
    );

    int weights[] = {
        1, 3, 4, 5
    };

    int values[] = {
        1, 4, 5, 7
    };

    int item_count =
        sizeof(weights) /
        sizeof(weights[0]);

    int capacity = 7;

    printf(
        "\n0/1 Knapsack: %d\n",
        knapsack(
            weights,
            values,
            item_count,
            capacity
        )
    );

    const char *string_a =
        "ABCBDAB";

    const char *string_b =
        "BDCABA";

    printf(
        "Longest Common Subsequence: %d\n",
        longest_common_subsequence(
            string_a,
            string_b
        )
    );

    int sequence[] = {
        10, 9, 2, 5,
        3, 7, 101, 18
    };

    int sequence_size =
        sizeof(sequence) /
        sizeof(sequence[0]);

    printf(
        "Longest Increasing Subsequence: %d\n",
        longest_increasing_subsequence(
            sequence,
            sequence_size
        )
    );

    int coins[] = {
        1, 3, 4
    };

    int coin_count =
        sizeof(coins) /
        sizeof(coins[0]);

    int amount = 6;

    printf(
        "Coin Change: %d coins\n",
        coin_change(
            coins,
            coin_count,
            amount
        )
    );

    int dimensions[] = {
        10, 30, 5, 60
    };

    int matrix_count = 3;

    printf(
        "Matrix Chain Multiplication: %lld\n",
        matrix_chain_multiplication(
            dimensions,
            matrix_count
        )
    );

    const char *source =
        "kitten";

    const char *target =
        "sitting";

    printf(
        "Edit Distance: %d\n",
        edit_distance(
            source,
            target
        )
    );

    printf("\nLIS Input: ");

    print_array(
        sequence,
        sequence_size
    );

    return 0;
}