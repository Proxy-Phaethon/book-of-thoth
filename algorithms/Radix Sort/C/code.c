#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int size, int exponent)
{
    int *output = malloc(size * sizeof(int));
    int count[10] = {0};

    if (output == NULL)
    {
        return;
    }

    /* Count occurrences of each digit. */
    for (int i = 0; i < size; i++)
    {
        int digit = (arr[i] / exponent) % 10;
        count[digit]++;
    }

    /* Convert counts into positions. */
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    /*
     * Build the output array from right to left.
     * This preserves stability.
     */
    for (int i = size - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exponent) % 10;

        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    /* Copy the sorted values back into the input array. */
    for (int i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }

    free(output);
}

void radix_sort(int arr[], int size)
{
    if (size <= 1)
    {
        return;
    }

    int max = arr[0];

    /* Find the largest value. */
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    /*
     * Process each digit from least significant
     * to most significant.
     */
    for (int exponent = 1; max / exponent > 0; exponent *= 10)
    {
        counting_sort(arr, size, exponent);
    }
}

int main(void)
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int size = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}