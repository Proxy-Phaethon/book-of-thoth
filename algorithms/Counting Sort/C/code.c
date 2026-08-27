#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int size)
{
    if (size <= 1)
    {
        return;
    }

    int max = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    int *count = calloc(max + 1, sizeof(int));

    if (count == NULL)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        count[arr[i]]++;
    }

    int index = 0;

    for (int value = 0; value <= max; value++)
    {
        while (count[value] > 0)
        {
            arr[index] = value;
            index++;
            count[value]--;
        }
    }

    free(count);
}

int main(void)
{
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    counting_sort(arr, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}