def heap_sort(arr):
    def heapify(size, root):
        largest = root
        left = 2 * root + 1
        right = 2 * root + 2

        if left < size and arr[left] > arr[largest]:
            largest = left

        if right < size and arr[right] > arr[largest]:
            largest = right

        if largest != root:
            arr[root], arr[largest] = arr[largest], arr[root]

            heapify(size, largest)

    size = len(arr)

    # Build the max heap.
    for i in range(size // 2 - 1, -1, -1):
        heapify(size, i)

    # Move the largest element to the end.
    for i in range(size - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]

        # Restore the max-heap property.
        heapify(i, 0)


arr = [12, 11, 13, 5, 6, 7]

heap_sort(arr)

print(arr)