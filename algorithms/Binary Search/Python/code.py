def binary_search(arr, target):
    left = 0
    right = len(arr) - 1

    while left <= right:
        middle = left + (right - left) // 2

        if arr[middle] == target:
            return middle

        if arr[middle] < target:
            left = middle + 1
        else:
            right = middle - 1

    return -1


arr = [1, 3, 5, 7, 9, 11, 13]
target = 11

result = binary_search(arr, target)

print(result)