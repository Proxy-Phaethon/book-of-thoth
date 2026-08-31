#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(
    int *array,
    int left,
    int middle,
    int right
)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int *left_array = malloc(left_size * sizeof(int));
    int *right_array = malloc(right_size * sizeof(int));

    if (left_array == NULL || right_array == NULL)
    {
        free(left_array);
        free(right_array);
        return;
    }

    for (int i = 0; i < left_size; i++)
    {
        left_array[i] = array[left + i];
    }

    for (int i = 0; i < right_size; i++)
    {
        right_array[i] = array[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_size && j < right_size)
    {
        if (left_array[i] <= right_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i < left_size)
    {
        array[k] = left_array[i];

        i++;
        k++;
    }

    while (j < right_size)
    {
        array[k] = right_array[j];

        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

void merge_sort(
    int *array,
    int left,
    int right
)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    merge_sort(array, left, middle);
    merge_sort(array, middle + 1, right);

    merge(array, left, middle, right);
}

int binary_search(
    const int *array,
    int left,
    int right,
    int target
)
{
    if (left > right)
    {
        return -1;
    }

    int middle = left + (right - left) / 2;

    if (array[middle] == target)
    {
        return middle;
    }

    if (target < array[middle])
    {
        return binary_search(
            array,
            left,
            middle - 1,
            target
        );
    }

    return binary_search(
        array,
        middle + 1,
        right,
        target
    );
}

int max_crossing_sum(
    const int *array,
    int left,
    int middle,
    int right
)
{
    int left_sum = INT_MIN;
    int sum = 0;

    for (int i = middle; i >= left; i--)
    {
        sum += array[i];

        if (sum > left_sum)
        {
            left_sum = sum;
        }
    }

    int right_sum = INT_MIN;
    sum = 0;

    for (int i = middle + 1; i <= right; i++)
    {
        sum += array[i];

        if (sum > right_sum)
        {
            right_sum = sum;
        }
    }

    return left_sum + right_sum;
}

int max_subarray_sum(
    const int *array,
    int left,
    int right
)
{
    if (left == right)
    {
        return array[left];
    }

    int middle = left + (right - left) / 2;

    int left_sum = max_subarray_sum(
        array,
        left,
        middle
    );

    int right_sum = max_subarray_sum(
        array,
        middle + 1,
        right
    );

    int crossing_sum = max_crossing_sum(
        array,
        left,
        middle,
        right
    );

    if (left_sum >= right_sum &&
        left_sum >= crossing_sum)
    {
        return left_sum;
    }

    if (right_sum >= left_sum &&
        right_sum >= crossing_sum)
    {
        return right_sum;
    }

    return crossing_sum;
}

long long fast_power(
    long long base,
    unsigned int exponent
)
{
    if (exponent == 0)
    {
        return 1;
    }

    long long half = fast_power(
        base,
        exponent / 2
    );

    long long result = half * half;

    if (exponent % 2 != 0)
    {
        result *= base;
    }

    return result;
}

/* --------------------------------------------------
 * Find Maximum
 * -------------------------------------------------- */

int find_max(
    const int *array,
    int left,
    int right
)
{
    if (left == right)
    {
        return array[left];
    }

    int middle = left + (right - left) / 2;

    int left_max = find_max(
        array,
        left,
        middle
    );

    int right_max = find_max(
        array,
        middle + 1,
        right
    );

    return left_max > right_max
        ? left_max
        : right_max;
}

void print_array(
    const int *array,
    int size
)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main(void)
{
    int array[] = {
        8, 3, 5, 4,
        7, 6, 1, 2
    };

    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    print_array(array, size);

    merge_sort(array, 0, size - 1);

    printf("Sorted array:   ");
    print_array(array, size);

    int target = 6;

    int index = binary_search(
        array,
        0,
        size - 1,
        target
    );

    printf(
        "Binary Search (%d): index %d\n",
        target,
        index
    );

    int subarray[] = {
        -2, 1, -3, 4,
        -1, 2, 1, -5, 4
    };

    int subarray_size =
        sizeof(subarray) / sizeof(subarray[0]);

    int maximum_sum = max_subarray_sum(
        subarray,
        0,
        subarray_size - 1
    );

    printf(
        "Maximum subarray sum: %d\n",
        maximum_sum
    );

    printf(
        "Fast Power (2^10): %lld\n",
        fast_power(2, 10)
    );

    int values[] = {
        7, 2, 9, 4, 1, 8
    };

    int values_size =
        sizeof(values) / sizeof(values[0]);

    printf(
        "Maximum element: %d\n",
        find_max(
            values,
            0,
            values_size - 1
        )
    );

    return 0;
}