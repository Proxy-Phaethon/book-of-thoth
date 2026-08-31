def constant_time(array):
    return array[0]

def binary_search(array, left, right, target):
    if left > right:
        return -1

    middle = left + (right - left) // 2

    if array[middle] == target:
        return middle

    if target < array[middle]:
        return binary_search(
            array,
            left,
            middle - 1,
            target
        )

    return binary_search(
        array,
        middle + 1,
        right,
        target
    )

def linear_sum(array):
    total = 0

    for value in array:
        total += value

    return total

def quadratic_example(n):
    for i in range(n):
        for j in range(n):
            print(f"({i}, {j})", end=" ")

        print()

def cubic_example(n):
    count = 0

    for i in range(n):
        for j in range(n):
            for k in range(n):
                count += 1

    return count

def merge(array, left, middle, right):
    left_array = array[left:middle + 1]
    right_array = array[middle + 1:right + 1]

    i = 0
    j = 0
    k = left

    while (
        i < len(left_array)
        and j < len(right_array)
    ):
        if left_array[i] <= right_array[j]:
            array[k] = left_array[i]
            i += 1
        else:
            array[k] = right_array[j]
            j += 1

        k += 1

    while i < len(left_array):
        array[k] = left_array[i]
        i += 1
        k += 1

    while j < len(right_array):
        array[k] = right_array[j]
        j += 1
        k += 1


def merge_sort(array, left, right):
    if left >= right:
        return

    middle = left + (right - left) // 2

    merge_sort(array, left, middle)

    merge_sort(
        array,
        middle + 1,
        right
    )

    merge(
        array,
        left,
        middle,
        right
    )

def fibonacci(n):
    if n <= 1:
        return n

    return (
        fibonacci(n - 1)
        + fibonacci(n - 2)
    )

def permutations(array, left, right):
    if left == right:
        print(*array)
        return

    for i in range(left, right + 1):
        array[left], array[i] = (
            array[i],
            array[left]
        )

        permutations(
            array,
            left + 1,
            right
        )

        array[left], array[i] = (
            array[i],
            array[left]
        )

def create_array(size):
    array = [0] * size

    for i in range(size):
        array[i] = i

    return array

def constant_space_example(array):
    for i in range(len(array)):
        array[i] *= 2

def recursive_example(n):
    if n <= 0:
        return

    recursive_example(n - 1)

array = [
    8, 3, 5, 4,
    7, 6, 1, 2
]

print(
    "O(1) - First element:",
    constant_time(array)
)

sorted_array = [
    1, 2, 3, 4,
    5, 6, 7, 8
]

target = 6

index = binary_search(
    sorted_array,
    0,
    len(sorted_array) - 1,
    target
)

print(
    "O(log n) - Binary Search:",
    f"index {index}"
)

print(
    "O(n) - Array Sum:",
    linear_sum(array)
)

print(
    "O(n²) - Quadratic iterations:",
    len(array) ** 2
)

print(
    "O(n³) - Cubic iterations:",
    cubic_example(5)
)

merge_sort(
    array,
    0,
    len(array) - 1
)

print(
    "O(n log n) - Merge Sort:",
    *array
)

print(
    "O(2^n) - Fibonacci(10):",
    fibonacci(10)
)

print(
    "O(n!) - Permutations of [1, 2, 3]:"
)

permutation_array = [1, 2, 3]

permutations(
    permutation_array,
    0,
    len(permutation_array) - 1
)

dynamic_array = create_array(5)

print(
    "O(n) Space - Dynamic array:",
    *dynamic_array
)

constant_space_example(array)

recursive_example(5)

print(
    "O(n) Auxiliary Stack Space - "
    "Recursive function completed."
)