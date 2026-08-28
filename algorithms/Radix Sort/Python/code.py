def counting_sort(arr, exponent):
    size = len(arr)
    output = [0] * size
    count = [0] * 10

    # Count occurrences of each digit.
    for value in arr:
        digit = (value // exponent) % 10
        count[digit] += 1

    # Convert counts into positions.
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build the output array from right to left.
    # This preserves stability.
    for i in range(size - 1, -1, -1):
        digit = (arr[i] // exponent) % 10

        output[count[digit] - 1] = arr[i]
        count[digit] -= 1

    # Copy the sorted values back.
    for i in range(size):
        arr[i] = output[i]


def radix_sort(arr):
    if len(arr) <= 1:
        return

    max_value = arr[0]

    # Find the largest value.
    for value in arr:
        if value > max_value:
            max_value = value

    # Process each digit from least significant
    # to most significant.
    exponent = 1

    while max_value // exponent > 0:
        counting_sort(arr, exponent)
        exponent *= 10


arr = [170, 45, 75, 90, 802, 24, 2, 66]

radix_sort(arr)

print(arr)