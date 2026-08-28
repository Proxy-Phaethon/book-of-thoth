#include <stdio.h>

int linear_search(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {10, 25, 7, 42, 18};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 42;

    int result = linear_search(arr, size, target);

    printf("%d\n", result);

    return 0;
}