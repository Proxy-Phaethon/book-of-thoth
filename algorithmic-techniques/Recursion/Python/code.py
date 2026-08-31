def factorial(n):
    if n == 0:
        return 1

    return n * factorial(n - 1)


def fibonacci(n):
    if n == 0:
        return 0

    if n == 1:
        return 1

    return fibonacci(n - 1) + fibonacci(n - 2)


def sum_recursive(n):
    if n == 0:
        return 0

    return n + sum_recursive(n - 1)


def array_sum(array, size):
    if size == 0:
        return 0

    return array[size - 1] + array_sum(array, size - 1)


def power(base, exponent):
    if exponent == 0:
        return 1

    return base * power(base, exponent - 1)


def gcd(a, b):
    if b == 0:
        return a

    return gcd(b, a % b)


def reverse_string_recursive(string, left, right):
    if left >= right:
        return

    string[left], string[right] = string[right], string[left]

    reverse_string_recursive(
        string,
        left + 1,
        right - 1
    )


def reverse_string(string):
    characters = list(string)

    reverse_string_recursive(
        characters,
        0,
        len(characters) - 1
    )

    return "".join(characters)


array = [2, 4, 6, 8]

print("Factorial:", factorial(5))

print("Fibonacci:", fibonacci(5))

print("Sum:", sum_recursive(5))

print("Array Sum:", array_sum(array, len(array)))

print("Power:", power(2, 5))

print("GCD:", gcd(48, 18))

print("Reversed String:", reverse_string("hello"))