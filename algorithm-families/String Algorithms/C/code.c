#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int string_length(const char *str)
{
    int length = 0;

    while (str[length] != '\0')
    {
        length++;
    }

    return length;
}

void reverse_string(char *str)
{
    int left = 0;
    int right = string_length(str) - 1;

    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}

bool is_palindrome(const char *str)
{
    int left = 0;
    int right = string_length(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
        {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

void character_frequency(const char *str)
{
    int frequency[256] = {0};

    for (int i = 0; str[i] != '\0'; i++)
    {
        unsigned char character = (unsigned char)str[i];
        frequency[character]++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            if (i >= 32 && i <= 126)
            {
                printf("'%c': %d\n",
                       (char)i,
                       frequency[i]);
            }
            else
            {
                printf("ASCII %d: %d\n",
                       i,
                       frequency[i]);
            }
        }
    }
}

void naive_pattern_matching(
    const char *text,
    const char *pattern
)
{
    int n = string_length(text);
    int m = string_length(pattern);

    if (m == 0 || m > n)
    {
        return;
    }

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;

        while (
            j < m &&
            text[i + j] == pattern[j]
        )
        {
            j++;
        }

        if (j == m)
        {
            printf("%d ", i);
        }
    }
}

char *longest_common_prefix(
    const char *strings[],
    int count
)
{
    if (count == 0)
    {
        return NULL;
    }

    int length = string_length(strings[0]);

    char *prefix = malloc(
        (length + 1) * sizeof(char)
    );

    if (prefix == NULL)
    {
        return NULL;
    }

    strcpy(prefix, strings[0]);

    for (int i = 1; i < count; i++)
    {
        int j = 0;

        while (
            prefix[j] != '\0' &&
            strings[i][j] != '\0' &&
            prefix[j] == strings[i][j]
        )
        {
            j++;
        }

        prefix[j] = '\0';

        if (prefix[0] == '\0')
        {
            break;
        }
    }

    return prefix;
}

int longest_common_subsequence(
    const char *first,
    const char *second
)
{
    int n = string_length(first);
    int m = string_length(second);

    int **dp = malloc(
        (n + 1) * sizeof(int *)
    );

    if (dp == NULL)
    {
        return -1;
    }

    for (int i = 0; i <= n; i++)
    {
        dp[i] = calloc(
            m + 1,
            sizeof(int)
        );

        if (dp[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(dp[j]);
            }

            free(dp);
            return -1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (first[i - 1] == second[j - 1])
            {
                dp[i][j] =
                    dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] =
                    dp[i - 1][j] >
                    dp[i][j - 1]
                        ? dp[i - 1][j]
                        : dp[i][j - 1];
            }
        }
    }

    int result = dp[n][m];

    for (int i = 0; i <= n; i++)
    {
        free(dp[i]);
    }

    free(dp);

    return result;
}

void build_lps(
    const char *pattern,
    int *lps
)
{
    int length = 0;
    int i = 1;

    lps[0] = 0;

    int m = string_length(pattern);

    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else if (length != 0)
        {
            length = lps[length - 1];
        }
        else
        {
            lps[i] = 0;
            i++;
        }
    }
}


void kmp_pattern_matching(
    const char *text,
    const char *pattern
)
{
    int n = string_length(text);
    int m = string_length(pattern);

    if (m == 0 || m > n)
    {
        return;
    }

    int *lps = malloc(
        m * sizeof(int)
    );

    if (lps == NULL)
    {
        return;
    }

    build_lps(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            printf("%d ", i - j);

            j = lps[j - 1];
        }
        else if (
            i < n &&
            text[i] != pattern[j]
        )
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    free(lps);
}

bool are_anagrams(
    const char *first,
    const char *second
)
{
    int frequency[256] = {0};

    int first_length =
        string_length(first);

    int second_length =
        string_length(second);

    if (first_length != second_length)
    {
        return false;
    }

    for (int i = 0; i < first_length; i++)
    {
        frequency[
            (unsigned char)first[i]
        ]++;

        frequency[
            (unsigned char)second[i]
        ]--;
    }

    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] != 0)
        {
            return false;
        }
    }

    return true;
}

char *compress_string(const char *str)
{
    int length = string_length(str);

    if (length == 0)
    {
        char *empty = malloc(1);

        if (empty != NULL)
        {
            empty[0] = '\0';
        }

        return empty;
    }

    char *compressed = malloc(
        (length * 2 + 1) * sizeof(char)
    );

    if (compressed == NULL)
    {
        return NULL;
    }

    int output_index = 0;
    int i = 0;

    while (i < length)
    {
        char current = str[i];
        int count = 0;

        while (
            i < length &&
            str[i] == current
        )
        {
            count++;
            i++;
        }

        compressed[output_index++] = current;

        char count_buffer[32];

        sprintf(
            count_buffer,
            "%d",
            count
        );

        for (
            int j = 0;
            count_buffer[j] != '\0';
            j++
        )
        {
            compressed[output_index++] =
                count_buffer[j];
        }
    }

    compressed[output_index] = '\0';

    return compressed;
}

void print_separator(void)
{
    printf(
        "----------------------------------------\n"
    );
}

int main(void)
{

    const char *text = "Hello, World!";

    printf("String: %s\n", text);
    printf(
        "Length: %d\n",
        string_length(text)
    );

    print_separator();

    char reversed[] = "algorithm";

    printf(
        "Original: %s\n",
        reversed
    );

    reverse_string(reversed);

    printf(
        "Reversed: %s\n",
        reversed
    );

    print_separator();

    const char *palindrome = "racecar";

    printf(
        "Palindrome \"%s\": %s\n",
        palindrome,
        is_palindrome(palindrome)
            ? "true"
            : "false"
    );

    print_separator();

    const char *frequency_text =
        "hello world";

    printf(
        "Character Frequency for \"%s\":\n",
        frequency_text
    );

    character_frequency(
        frequency_text
    );

    print_separator();

    const char *search_text =
        "abracadabra";

    const char *pattern =
        "abra";

    printf(
        "Naive Pattern Matching:\n"
    );

    printf(
        "Text: %s\n",
        search_text
    );

    printf(
        "Pattern: %s\n",
        pattern
    );

    printf("Indices: ");

    naive_pattern_matching(
        search_text,
        pattern
    );

    printf("\n");

    print_separator();

    const char *words[] = {
        "flower",
        "flow",
        "flight"
    };

    char *prefix =
        longest_common_prefix(
            words,
            3
        );

    printf(
        "Longest Common Prefix: %s\n",
        prefix
    );

    free(prefix);

    print_separator();

    const char *first =
        "ABCBDAB";

    const char *second =
        "BDCABA";

    int lcs =
        longest_common_subsequence(
            first,
            second
        );

    printf(
        "Longest Common Subsequence Length: %d\n",
        lcs
    );

    print_separator();

    const char *kmp_text =
        "ABABDABACDABABCABAB";

    const char *kmp_pattern =
        "ABABCABAB";

    printf(
        "KMP Pattern Matching:\n"
    );

    printf(
        "Text: %s\n",
        kmp_text
    );

    printf(
        "Pattern: %s\n",
        kmp_pattern
    );

    printf("Indices: ");

    kmp_pattern_matching(
        kmp_text,
        kmp_pattern
    );

    printf("\n");

    print_separator();

    const char *anagram_a =
        "listen";

    const char *anagram_b =
        "silent";

    printf(
        "Are \"%s\" and \"%s\" anagrams? %s\n",
        anagram_a,
        anagram_b,
        are_anagrams(
            anagram_a,
            anagram_b
        )
            ? "true"
            : "false"
    );

    print_separator();

    const char *compression_input =
        "aaabbcdddd";

    char *compressed =
        compress_string(
            compression_input
        );

    printf(
        "Original: %s\n",
        compression_input
    );

    printf(
        "Compressed: %s\n",
        compressed
    );

    free(compressed);

    print_separator();


    return 0;
}