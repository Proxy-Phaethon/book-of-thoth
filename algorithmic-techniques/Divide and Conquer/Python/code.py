def merge(array, left, middle, right):
    left_array = array[left:middle + 1]
    right_array = array[middle + 1:right + 1]

    i = 0
    j = 0
    k = left

    while i < len(left_array) and j < len(right_array):
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
    merge_sort(array, middle + 1, right)

    merge(array, left, middle, right)


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


def max_crossing_sum(array, left, middle, right):
    left_sum = float("-inf")
    total = 0

    for index in range(middle, left - 1, -1):
        total += array[index]

        if total > left_sum:
            left_sum = total

    right_sum = float("-inf")
    total = 0

    for index in range(middle + 1, right + 1):
        total += array[index]

        if total > right_sum:
            right_sum = total

    return left_sum + right_sum


def max_subarray_sum(array, left, right):
    if left == right:
        return array[left]

    middle = left + (right - left) // 2

    left_sum = max_subarray_sum(
        array,
        left,
        middle
    )

    right_sum = max_subarray_sum(
        array,
        middle + 1,
        right
    )

    crossing_sum = max_crossing_sum(
        array,
        left,
        middle,
        right
    )

    return max(
        left_sum,
        right_sum,
        crossing_sum
    )


def fast_power(base, exponent):
    if exponent == 0:
        return 1

    half = fast_power(
        base,
        exponent // 2
    )

    result = half * half

    if exponent % 2 != 0:
        result *= base

    return result


def find_max(array, left, right):
    if left == right:
        return array[left]

    middle = left + (right - left) // 2

    left_max = find_max(
        array,
        left,
        middle
    )

    right_max = find_max(
        array,
        middle + 1,
        right
    )

    return max(left_max, right_max)


def print_array(array):
    print(*array)


array = [8, 3, 5, 4, 7, 6, 1, 2]

print("Original array:", end=" ")
print_array(array)

merge_sort(array, 0, len(array) - 1)

print("Sorted array:  ", end=" ")
print_array(array)

target = 6

index = binary_search(
    array,
    0,
    len(array) - 1,
    target
)

print(f"Binary Search ({target}): index {index}")

subarray = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

maximum_sum = max_subarray_sum(
    subarray,
    0,
    len(subarray) - 1
)

print("Maximum subarray sum:", maximum_sum)

print("Fast Power (2^10):", fast_power(2, 10))

values = [7, 2, 9, 4, 1, 8]

maximum = find_max(
    values,
    0,
    len(values) - 1
)

print("Maximum element:", maximum)