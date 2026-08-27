def bubble_sort(arr: list[int]) -> None:
    size = len(arr)

    for i in range(size - 1):
        swapped = False

        for j in range(size - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True

        if not swapped:
            break


arr = [64, 34, 25, 12, 22, 11, 90]

bubble_sort(arr)

print(arr)