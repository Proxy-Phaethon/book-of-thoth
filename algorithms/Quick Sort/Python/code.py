def quick_sort(arr):
    def partition(low, high):
        pivot = arr[high]
        i = low - 1

        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]

        arr[i + 1], arr[high] = arr[high], arr[i + 1]

        return i + 1

    def sort(low, high):
        if low >= high:
            return

        pivot_index = partition(low, high)

        sort(low, pivot_index - 1)
        sort(pivot_index + 1, high)

    if len(arr) > 1:
        sort(0, len(arr) - 1)


arr = [10, 7, 8, 9, 1, 5]

quick_sort(arr)

print(arr)