#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

int string_length(const string& str)
{
    int length = 0;

    for (char character : str)
    {
        (void)character;
        length++;
    }

    return length;
}

void reverse_string(string& str)
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

bool is_palindrome(const string& str)
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

void character_frequency(const string& str)
{
    unordered_map<char, int> frequency;

    for (char character : str)
    {
        frequency[character]++;
    }

    for (const auto& [character, count] : frequency)
    {
        cout << "'" << character << "': "
             << count << '\n';
    }
}

vector<int> naive_pattern_matching(
    const string& text,
    const string& pattern
)
{
    vector<int> matches;

    int n = string_length(text);
    int m = string_length(pattern);

    if (m == 0 || m > n)
    {
        return matches;
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
            matches.push_back(i);
        }
    }

    return matches;
}

string longest_common_prefix(
    const vector<string>& strings
)
{
    if (strings.empty())
    {
        return "";
    }

    string prefix = strings[0];

    for (size_t i = 1; i < strings.size(); i++)
    {
        int j = 0;

        while (
            j < static_cast<int>(prefix.length()) &&
            j < static_cast<int>(strings[i].length()) &&
            prefix[j] == strings[i][j]
        )
        {
            j++;
        }

        prefix = prefix.substr(0, j);

        if (prefix.empty())
        {
            break;
        }
    }

    return prefix;
}

int longest_common_subsequence(
    const string& first,
    const string& second
)
{
    int n = string_length(first);
    int m = string_length(second);

    vector<vector<int>> dp(
        n + 1,
        vector<int>(m + 1, 0)
    );

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
                    max(
                        dp[i - 1][j],
                        dp[i][j - 1]
                    );
            }
        }
    }

    return dp[n][m];
}

vector<int> build_lps(const string& pattern)
{
    int m = string_length(pattern);

    vector<int> lps(m, 0);

    int length = 0;
    int i = 1;

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

    return lps;
}


vector<int> kmp_pattern_matching(
    const string& text,
    const string& pattern
)
{
    vector<int> matches;

    int n = string_length(text);
    int m = string_length(pattern);

    if (m == 0 || m > n)
    {
        return matches;
    }

    vector<int> lps =
        build_lps(pattern);

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
            matches.push_back(i - j);

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

    return matches;
}

bool are_anagrams(
    const string& first,
    const string& second
)
{
    if (first.length() != second.length())
    {
        return false;
    }

    unordered_map<char, int> frequency;

    for (char character : first)
    {
        frequency[character]++;
    }

    for (char character : second)
    {
        frequency[character]--;

        if (frequency[character] < 0)
        {
            return false;
        }
    }

    return true;
}

string compress_string(const string& str)
{
    if (str.empty())
    {
        return "";
    }

    string compressed;

    int i = 0;

    while (i < string_length(str))
    {
        char current = str[i];
        int count = 0;

        while (
            i < string_length(str) &&
            str[i] == current
        )
        {
            count++;
            i++;
        }

        compressed += current;
        compressed += to_string(count);
    }

    return compressed;
}

void print_separator()
{
    cout << "----------------------------------------\n";
}


void print_matches(const vector<int>& matches)
{
    for (int index : matches)
    {
        cout << index << ' ';
    }

    cout << '\n';
}

int main()
{

    string text = "Hello, World!";

    cout << "String: "
         << text
         << '\n';

    cout << "Length: "
         << string_length(text)
         << '\n';

    print_separator();

    string reversed = "algorithm";

    cout << "Original: "
         << reversed
         << '\n';

    reverse_string(reversed);

    cout << "Reversed: "
         << reversed
         << '\n';

    print_separator();

    string palindrome = "racecar";

    cout << "Palindrome \""
         << palindrome
         << "\": "
         << (
                is_palindrome(palindrome)
                    ? "true"
                    : "false"
            )
         << '\n';

    print_separator();

    string frequency_text =
        "hello world";

    cout << "Character Frequency for \""
         << frequency_text
         << "\":\n";

    character_frequency(
        frequency_text
    );

    print_separator();

    string search_text =
        "abracadabra";

    string pattern =
        "abra";

    cout << "Naive Pattern Matching:\n";

    cout << "Text: "
         << search_text
         << '\n';

    cout << "Pattern: "
         << pattern
         << '\n';

    cout << "Indices: ";

    print_matches(
        naive_pattern_matching(
            search_text,
            pattern
        )
    );

    print_separator();

    vector<string> words = {
        "flower",
        "flow",
        "flight"
    };

    cout << "Longest Common Prefix: "
         << longest_common_prefix(words)
         << '\n';

    print_separator();

    string first =
        "ABCBDAB";

    string second =
        "BDCABA";

    cout << "Longest Common Subsequence Length: "
         << longest_common_subsequence(
                first,
                second
            )
         << '\n';

    print_separator();

    string kmp_text =
        "ABABDABACDABABCABAB";

    string kmp_pattern =
        "ABABCABAB";

    cout << "KMP Pattern Matching:\n";

    cout << "Text: "
         << kmp_text
         << '\n';

    cout << "Pattern: "
         << kmp_pattern
         << '\n';

    cout << "Indices: ";

    print_matches(
        kmp_pattern_matching(
            kmp_text,
            kmp_pattern
        )
    );

    print_separator();

    string anagram_a =
        "listen";

    string anagram_b =
        "silent";

    cout << "Are \""
         << anagram_a
         << "\" and \""
         << anagram_b
         << "\" anagrams? "
         << (
                are_anagrams(
                    anagram_a,
                    anagram_b
                )
                    ? "true"
                    : "false"
            )
         << '\n';

    print_separator();

    string compression_input =
        "aaabbcdddd";

    string compressed =
        compress_string(
            compression_input
        );

    cout << "Original: "
         << compression_input
         << '\n';

    cout << "Compressed: "
         << compressed
         << '\n';

    print_separator();


    return 0;
}