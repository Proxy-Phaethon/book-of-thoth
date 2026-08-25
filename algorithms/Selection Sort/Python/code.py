def selection_sort(arr: list[int]) -> None:
    size = len(arr)

    for i in range(size - 1):
        min_index = i

        for j in range(i + 1, size):
            if arr[j] < arr[min_index]:
                min_index = j

        if min_index != i:
            arr[i], arr[min_index] = arr[min_index], arr[i]


arr = [64, 25, 12, 22, 11]

selection_sort(arr)

print(arr)