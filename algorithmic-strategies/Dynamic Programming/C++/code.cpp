#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long fibonacciTopDownHelper(
    int n,
    vector<long long>& memo
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
        fibonacciTopDownHelper(n - 1, memo) +
        fibonacciTopDownHelper(n - 2, memo);

    return memo[n];
}

long long fibonacciTopDown(int n)
{
    if (n < 0)
    {
        return -1;
    }

    vector<long long> memo(n + 1, -1);

    return fibonacciTopDownHelper(n, memo);
}

long long fibonacciBottomUp(int n)
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
    const vector<int>& weights,
    const vector<int>& values,
    int capacity
)
{
    if (capacity <= 0 ||
        weights.empty())
    {
        return 0;
    }

    vector<int> dp(capacity + 1, 0);

    for (size_t i = 0; i < weights.size(); i++)
    {
        for (int w = capacity;
             w >= weights[i];
             w--)
        {
            dp[w] = max(
                dp[w],
                values[i] +
                dp[w - weights[i]]
            );
        }
    }

    return dp[capacity];
}

int longestCommonSubsequence(
    const string& a,
    const string& b
)
{
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    vector<vector<int>> dp(
        m + 1,
        vector<int>(n + 1, 0)
    );

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] =
                    dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] =
                    max(
                        dp[i - 1][j],
                        dp[i][j - 1]
                    );
            }
        }
    }

    return dp[m][n];
}

int longestIncreasingSubsequence(
    const vector<int>& array
)
{
    if (array.empty())
    {
        return 0;
    }

    int n =
        static_cast<int>(array.size());

    vector<int> dp(n, 1);

    int longest = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[j] < array[i])
            {
                dp[i] =
                    max(
                        dp[i],
                        dp[j] + 1
                    );
            }
        }

        longest =
            max(longest, dp[i]);
    }

    return longest;
}

int coinChange(
    const vector<int>& coins,
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

    if (coins.empty())
    {
        return -1;
    }

    const int impossible =
        amount + 1;

    vector<int> dp(
        amount + 1,
        impossible
    );

    dp[0] = 0;

    for (int current = 1;
         current <= amount;
         current++)
    {
        for (int coin : coins)
        {
            if (coin <= current)
            {
                dp[current] =
                    min(
                        dp[current],
                        dp[current - coin] + 1
                    );
            }
        }
    }

    return dp[amount] == impossible
        ? -1
        : dp[amount];
}

long long matrixChainMultiplication(
    const vector<int>& dimensions
)
{

    int matrixCount =
        static_cast<int>(dimensions.size()) - 1;

    if (matrixCount <= 0)
    {
        return 0;
    }

    vector<vector<long long>> dp(
        matrixCount + 1,
        vector<long long>(
            matrixCount + 1,
            0
        )
    );

    for (int length = 2;
         length <= matrixCount;
         length++)
    {
        for (int i = 1;
             i <= matrixCount - length + 1;
             i++)
        {
            int j =
                i + length - 1;

            dp[i][j] =
                LLONG_MAX;

            for (int k = i;
                 k < j;
                 k++)
            {
                long long cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    static_cast<long long>(
                        dimensions[i - 1]
                    ) *
                    dimensions[k] *
                    dimensions[j];

                dp[i][j] =
                    min(
                        dp[i][j],
                        cost
                    );
            }
        }
    }

    return dp[1][matrixCount];
}

int editDistance(
    const string& a,
    const string& b
)
{
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    vector<vector<int>> dp(
        m + 1,
        vector<int>(n + 1, 0)
    );

    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] =
                    dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] =
                    1 + min({
                        dp[i - 1][j],
                        dp[i][j - 1],
                        dp[i - 1][j - 1]
                    });
            }
        }
    }

    return dp[m][n];
}

void printVector(
    const vector<int>& values
)
{
    cout << "[";

    for (size_t i = 0;
         i < values.size();
         i++)
    {
        cout << values[i];

        if (i + 1 < values.size())
        {
            cout << ", ";
        }
    }

    cout << "]\n";
}

int main()
{

    int n = 10;

    cout
        << "Fibonacci Top-Down: "
        << fibonacciTopDown(n)
        << '\n';

    cout
        << "Fibonacci Bottom-Up: "
        << fibonacciBottomUp(n)
        << '\n';

    vector<int> weights = {
        1, 3, 4, 5
    };

    vector<int> values = {
        1, 4, 5, 7
    };

    int capacity = 7;

    cout
        << "\n0/1 Knapsack: "
        << knapsack(
            weights,
            values,
            capacity
        )
        << '\n';

    string stringA = "ABCBDAB";
    string stringB = "BDCABA";

    cout
        << "Longest Common Subsequence: "
        << longestCommonSubsequence(
            stringA,
            stringB
        )
        << '\n';

    vector<int> sequence = {
        10, 9, 2, 5,
        3, 7, 101, 18
    };

    cout
        << "Longest Increasing Subsequence: "
        << longestIncreasingSubsequence(
            sequence
        )
        << '\n';

    vector<int> coins = {
        1, 3, 4
    };

    int amount = 6;

    cout
        << "Coin Change: "
        << coinChange(
            coins,
            amount
        )
        << " coins\n";

    vector<int> dimensions = {
        10, 30, 5, 60
    };

    cout
        << "Matrix Chain Multiplication: "
        << matrixChainMultiplication(
            dimensions
        )
        << '\n';

    string source = "kitten";
    string target = "sitting";

    cout
        << "Edit Distance: "
        << editDistance(
            source,
            target
        )
        << '\n';

    cout << "\nLIS Input: ";

    printVector(sequence);

    return 0;
}