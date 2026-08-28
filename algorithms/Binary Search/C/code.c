#include <stdio.h>

int binary_search(int arr[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        if (arr[middle] == target)
        {
            return middle;
        }

        if (arr[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 11;

    int result = binary_search(arr, size, target);

    printf("%d\n", result);

    return 0;
}