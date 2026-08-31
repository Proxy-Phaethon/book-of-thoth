# String Algorithms

## Problem

Implement a collection of fundamental string algorithms.

Your program should work with strings and demonstrate the following operations:

1. **String Traversal**
   - Visit each character in a string.
   - Count the number of characters.

2. **String Reversal**
   - Reverse a string without using a built-in reverse function.

3. **Palindrome Detection**
   - Determine whether a string reads the same forwards and backwards.

4. **Character Frequency**
   - Count how many times each character occurs in a string.

5. **Naive Pattern Matching**
   - Given a text and a pattern, find every occurrence of the pattern in the text.

6. **Longest Common Prefix**
   - Given an array of strings, find the longest prefix shared by all strings.

7. **Longest Common Subsequence**
   - Given two strings, determine the length of their longest common subsequence.

8. **KMP Pattern Matching**
   - Implement the Knuth-Morris-Pratt algorithm.
   - Use a prefix/LPS table to avoid unnecessary comparisons.

9. **Anagram Detection**
   - Determine whether two strings contain the same characters with the same frequencies.

10. **String Compression**
    - Compress consecutive repeated characters using run-length encoding.
    - For example:
      ```text
      aaabbcdddd
      ```
      becomes:
      ```text
      a3b2c1d4
      ```

---

## Requirements

Your implementation should:

- Handle empty strings.
- Handle strings containing spaces and punctuation where appropriate.
- Avoid relying on built-in functions that directly solve the algorithm.
- Implement the algorithms manually.
- Keep each algorithm in its own function.
- Demonstrate every algorithm in `main()`.

---

## Example

### Input

```text
Text:    "abracadabra"
Pattern: "abra"