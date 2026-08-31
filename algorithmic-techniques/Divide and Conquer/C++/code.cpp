#include <iostream>
#include <vector>
#include <climits>

void merge(
    int* array,
    int left,
    int middle,
    int right
)
{
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    std::vector<int> leftArray(leftSize);
    std::vector<int> rightArray(rightSize);

    for (int i = 0; i < leftSize; i++)
    {
        leftArray[i] = array[left + i];
    }

    for (int i = 0; i < rightSize; i++)
    {
        rightArray[i] = array[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize)
    {
        if (leftArray[i] <= rightArray[j])
        {
            array[k] = leftArray[i];
            i++;
        }
        else
        {
            array[k] = rightArray[j];
            j++;
        }

        k++;
    }

    while (i < leftSize)
    {
        array[k] = leftArray[i];

        i++;
        k++;
    }

    while (j < rightSize)
    {
        array[k] = rightArray[j];

        j++;
        k++;
    }
}

void mergeSort(
    int* array,
    int left,
    int right
)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSort(array, left, middle);
    mergeSort(array, middle + 1, right);

    merge(array, left, middle, right);
}

int binarySearch(
    const int* array,
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
        return binarySearch(
            array,
            left,
            middle - 1,
            target
        );
    }

    return binarySearch(
        array,
        middle + 1,
        right,
        target
    );
}

int maxCrossingSum(
    const int* array,
    int left,
    int middle,
    int right
)
{
    int leftSum = INT_MIN;
    int sum = 0;

    for (int i = middle; i >= left; i--)
    {
        sum += array[i];

        if (sum > leftSum)
        {
            leftSum = sum;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;

    for (int i = middle + 1; i <= right; i++)
    {
        sum += array[i];

        if (sum > rightSum)
        {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}

int maxSubarraySum(
    const int* array,
    int left,
    int right
)
{
    if (left == right)
    {
        return array[left];
    }

    int middle = left + (right - left) / 2;

    int leftSum = maxSubarraySum(
        array,
        left,
        middle
    );

    int rightSum = maxSubarraySum(
        array,
        middle + 1,
        right
    );

    int crossingSum = maxCrossingSum(
        array,
        left,
        middle,
        right
    );

    return std::max(
        leftSum,
        std::max(rightSum, crossingSum)
    );
}

long long fastPower(
    long long base,
    unsigned int exponent
)
{
    if (exponent == 0)
    {
        return 1;
    }

    long long half = fastPower(
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

int findMax(
    const int* array,
    int left,
    int right
)
{
    if (left == right)
    {
        return array[left];
    }

    int middle = left + (right - left) / 2;

    int leftMax = findMax(
        array,
        left,
        middle
    );

    int rightMax = findMax(
        array,
        middle + 1,
        right
    );

    return std::max(leftMax, rightMax);
}

void printArray(
    const int* array,
    int size
)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }

    std::cout << "\n";
}

int main()
{
    int array[] = {
        8, 3, 5, 4,
        7, 6, 1, 2
    };

    int size = sizeof(array) / sizeof(array[0]);

    std::cout << "Original array: ";
    printArray(array, size);

    mergeSort(array, 0, size - 1);

    std::cout << "Sorted array:   ";
    printArray(array, size);

    int target = 6;

    int index = binarySearch(
        array,
        0,
        size - 1,
        target
    );

    std::cout
        << "Binary Search ("
        << target
        << "): index "
        << index
        << "\n";

    int subarray[] = {
        -2, 1, -3, 4,
        -1, 2, 1, -5, 4
    };

    int subarraySize =
        sizeof(subarray) / sizeof(subarray[0]);

    int maximumSum = maxSubarraySum(
        subarray,
        0,
        subarraySize - 1
    );

    std::cout
        << "Maximum subarray sum: "
        << maximumSum
        << "\n";

    std::cout
        << "Fast Power (2^10): "
        << fastPower(2, 10)
        << "\n";

    int values[] = {
        7, 2, 9, 4, 1, 8
    };

    int valuesSize =
        sizeof(values) / sizeof(values[0]);

    std::cout
        << "Maximum element: "
        << findMax(
            values,
            0,
            valuesSize - 1
        )
        << "\n";

    return 0;
}