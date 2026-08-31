from collections import Counter

def string_length(string):
    length = 0

    for _ in string:
        length += 1

    return length

def reverse_string(string):
    characters = list(string)

    left = 0
    right = string_length(characters) - 1

    while left < right:
        characters[left], characters[right] = (
            characters[right],
            characters[left],
        )

        left += 1
        right -= 1

    return "".join(characters)

def is_palindrome(string):
    left = 0
    right = string_length(string) - 1

    while left < right:
        if string[left] != string[right]:
            return False

        left += 1
        right -= 1

    return True

def character_frequency(string):
    frequency = {}

    for character in string:
        if character in frequency:
            frequency[character] += 1
        else:
            frequency[character] = 1

    return frequency

def naive_pattern_matching(text, pattern):
    matches = []

    n = string_length(text)
    m = string_length(pattern)

    if m == 0 or m > n:
        return matches

    for i in range(n - m + 1):
        j = 0

        while j < m and text[i + j] == pattern[j]:
            j += 1

        if j == m:
            matches.append(i)

    return matches

def longest_common_prefix(strings):
    if not strings:
        return ""

    prefix = strings[0]

    for string in strings[1:]:
        length = 0

        while (
            length < string_length(prefix)
            and length < string_length(string)
            and prefix[length] == string[length]
        ):
            length += 1

        prefix = prefix[:length]

        if not prefix:
            break

    return prefix

def longest_common_subsequence(first, second):
    n = string_length(first)
    m = string_length(second)

    dp = [
        [0] * (m + 1)
        for _ in range(n + 1)
    ]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if first[i - 1] == second[j - 1]:
                dp[i][j] = (
                    dp[i - 1][j - 1] + 1
                )
            else:
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1],
                )

    return dp[n][m]

def build_lps(pattern):
    m = string_length(pattern)

    lps = [0] * m

    length = 0
    i = 1

    while i < m:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1

        elif length != 0:
            length = lps[length - 1]

        else:
            lps[i] = 0
            i += 1

    return lps


def kmp_pattern_matching(text, pattern):
    matches = []

    n = string_length(text)
    m = string_length(pattern)

    if m == 0 or m > n:
        return matches

    lps = build_lps(pattern)

    i = 0
    j = 0

    while i < n:
        if text[i] == pattern[j]:
            i += 1
            j += 1

        if j == m:
            matches.append(i - j)

            j = lps[j - 1]

        elif i < n and text[i] != pattern[j]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1

    return matches

def are_anagrams(first, second):
    if string_length(first) != string_length(second):
        return False

    frequency = {}

    for character in first:
        if character in frequency:
            frequency[character] += 1
        else:
            frequency[character] = 1

    for character in second:
        if character not in frequency:
            return False

        frequency[character] -= 1

        if frequency[character] < 0:
            return False

    return True

def compress_string(string):
    if not string:
        return ""

    compressed = []

    i = 0
    length = string_length(string)

    while i < length:
        current = string[i]
        count = 0

        while (
            i < length
            and string[i] == current
        ):
            count += 1
            i += 1

        compressed.append(current)
        compressed.append(str(count))

    return "".join(compressed)

def main():

    text = "Hello, World!"

    print("String:", text)
    print("Length:", string_length(text))

    print("----------------------------------------")

    reversed_text = "algorithm"

    print("Original:", reversed_text)

    reversed_text = reverse_string(reversed_text)

    print("Reversed:", reversed_text)

    print("----------------------------------------")

    palindrome = "racecar"

    print(
        f'Palindrome "{palindrome}":',
        is_palindrome(palindrome),
    )

    print("----------------------------------------")

    frequency_text = "hello world"

    print(
        f'Character Frequency for "{frequency_text}":'
    )

    frequency = character_frequency(
        frequency_text
    )

    for character, count in frequency.items():
        print(f"'{character}': {count}")

    print("----------------------------------------")

    search_text = "abracadabra"
    pattern = "abra"

    print("Naive Pattern Matching:")
    print("Text:", search_text)
    print("Pattern:", pattern)

    matches = naive_pattern_matching(
        search_text,
        pattern,
    )

    print("Indices:", *matches)

    print("----------------------------------------")

    words = [
        "flower",
        "flow",
        "flight",
    ]

    prefix = longest_common_prefix(words)

    print("Longest Common Prefix:", prefix)

    print("----------------------------------------")

    first = "ABCBDAB"
    second = "BDCABA"

    lcs = longest_common_subsequence(
        first,
        second,
    )

    print(
        "Longest Common Subsequence Length:",
        lcs,
    )

    print("----------------------------------------")

    kmp_text = "ABABDABACDABABCABAB"
    kmp_pattern = "ABABCABAB"

    print("KMP Pattern Matching:")
    print("Text:", kmp_text)
    print("Pattern:", kmp_pattern)

    matches = kmp_pattern_matching(
        kmp_text,
        kmp_pattern,
    )

    print("Indices:", *matches)

    print("----------------------------------------")

    anagram_a = "listen"
    anagram_b = "silent"

    print(
        f'Are "{anagram_a}" and "{anagram_b}" '
        f"anagrams?",
        are_anagrams(
            anagram_a,
            anagram_b,
        ),
    )

    print("----------------------------------------")

    compression_input = "aaabbcdddd"

    compressed = compress_string(
        compression_input
    )

    print("Original:", compression_input)
    print("Compressed:", compressed)

    print("----------------------------------------")


if __name__ == "__main__":
    main()