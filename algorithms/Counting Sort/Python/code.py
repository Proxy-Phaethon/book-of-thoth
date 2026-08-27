def counting_sort(arr):
    if len(arr) <= 1:
        return

    max_value = arr[0]

    for value in arr:
        if value > max_value:
            max_value = value

    count = [0] * (max_value + 1)

    for value in arr:
        count[value] += 1

    index = 0

    for value in range(max_value + 1):
        while count[value] > 0:
            arr[index] = value
            index += 1
            count[value] -= 1


arr = [4, 2, 2, 8, 3, 3, 1]

counting_sort(arr)

print(arr)