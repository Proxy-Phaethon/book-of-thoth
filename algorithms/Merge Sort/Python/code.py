def merge_sort(arr: list[int]) -> None:
    def merge(left: int, middle: int, right: int) -> None:
        left_arr = arr[left:middle + 1]
        right_arr = arr[middle + 1:right + 1]

        i = 0
        j = 0
        k = left

        while i < len(left_arr) and j < len(right_arr):
            if left_arr[i] <= right_arr[j]:
                arr[k] = left_arr[i]
                i += 1
            else:
                arr[k] = right_arr[j]
                j += 1

            k += 1

        while i < len(left_arr):
            arr[k] = left_arr[i]
            i += 1
            k += 1

        while j < len(right_arr):
            arr[k] = right_arr[j]
            j += 1
            k += 1

    def sort(left: int, right: int) -> None:
        if left >= right:
            return

        middle = left + (right - left) // 2

        sort(left, middle)
        sort(middle + 1, right)

        merge(left, middle, right)

    if len(arr) > 1:
        sort(0, len(arr) - 1)


arr = [38, 27, 43, 3, 9, 82, 10]

merge_sort(arr)

print(arr)