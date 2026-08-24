#include <stdio.h>

void merge(int arr[], int left, int middle, int right)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int left_arr[left_size];
    int right_arr[right_size];

    for (int i = 0; i < left_size; i++)
        left_arr[i] = arr[left + i];

    for (int i = 0; i < right_size; i++)
        right_arr[i] = arr[middle + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_size && j < right_size)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }

        k++;
    }

    while (i < left_size)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right)
{
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;

    merge_sort(arr, left, middle);
    merge_sort(arr, middle + 1, right);

    merge(arr, left, middle, right);
}

int main(void)
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, size - 1);

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}