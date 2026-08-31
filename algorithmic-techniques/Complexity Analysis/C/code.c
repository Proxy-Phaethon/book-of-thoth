#include <stdio.h>
#include <stdlib.h>

int constant_time(const int *array)
{
    return array[0];
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

int linear_sum(const int *array, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }

    return sum;
}

void quadratic_example(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf(
                "(%d, %d) ",
                i,
                j
            );
        }

        printf("\n");
    }
}

long long cubic_example(int n)
{
    long long count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                count++;
            }
        }
    }

    return count;
}

void merge(
    int *array,
    int left,
    int middle,
    int right
)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int *left_array =
        malloc(left_size * sizeof(int));

    int *right_array =
        malloc(right_size * sizeof(int));

    if (left_array == NULL ||
        right_array == NULL)
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
        right_array[i] =
            array[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_size &&
           j < right_size)
    {
        if (left_array[i] <= right_array[j])
        {
            array[k++] = left_array[i++];
        }
        else
        {
            array[k++] = right_array[j++];
        }
    }

    while (i < left_size)
    {
        array[k++] = left_array[i++];
    }

    while (j < right_size)
    {
        array[k++] = right_array[j++];
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

    int middle =
        left + (right - left) / 2;

    merge_sort(
        array,
        left,
        middle
    );

    merge_sort(
        array,
        middle + 1,
        right
    );

    merge(
        array,
        left,
        middle,
        right
    );
}

long long fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }

    return fibonacci(n - 1)
         + fibonacci(n - 2);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permutations(
    int *array,
    int left,
    int right
)
{
    if (left == right)
    {
        for (int i = 0; i <= right; i++)
        {
            printf("%d ", array[i]);
        }

        printf("\n");

        return;
    }

    for (int i = left; i <= right; i++)
    {
        swap(
            &array[left],
            &array[i]
        );

        permutations(
            array,
            left + 1,
            right
        );

        swap(
            &array[left],
            &array[i]
        );
    }
}

int *create_array(int size)
{
    int *array =
        malloc(size * sizeof(int));

    if (array == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }

    return array;
}

void constant_space_example(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] *= 2;
    }
}

void recursive_example(int n)
{
    if (n <= 0)
    {
        return;
    }

    recursive_example(n - 1);
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

    int size =
        sizeof(array) / sizeof(array[0]);

    printf(
        "O(1) - First element: %d\n",
        constant_time(array)
    );

    int sorted[] = {
        1, 2, 3, 4,
        5, 6, 7, 8
    };

    int target = 6;

    int index = binary_search(
        sorted,
        0,
        7,
        target
    );

    printf(
        "O(log n) - Binary Search: "
        "index %d\n",
        index
    );

    printf(
        "O(n) - Array Sum: %d\n",
        linear_sum(array, size)
    );

    printf(
        "O(n^2) - Quadratic iterations: "
        "%d\n",
        size * size
    );

    printf(
        "O(n^3) - Cubic iterations: "
        "%lld\n",
        cubic_example(5)
    );

    merge_sort(
        array,
        0,
        size - 1
    );

    printf(
        "O(n log n) - Merge Sort: "
    );

    print_array(array, size);

    printf(
        "O(2^n) - Fibonacci(10): %lld\n",
        fibonacci(10)
    );

    printf(
        "O(n!) - Permutations of "
        "[1, 2, 3]:\n"
    );

    int permutation_array[] = {
        1, 2, 3
    };

    permutations(
        permutation_array,
        0,
        2
    );

    int *dynamic_array =
        create_array(5);

    if (dynamic_array != NULL)
    {
        printf(
            "O(n) Space - Dynamic array: "
        );

        print_array(
            dynamic_array,
            5
        );

        free(dynamic_array);
    }

    recursive_example(5);

    printf(
        "O(n) Auxiliary Stack Space - "
        "Recursive function completed.\n"
    );

    return 0;
}