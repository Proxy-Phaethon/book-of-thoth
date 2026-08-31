#include <iostream>
#include <vector>

int constantTime(const std::vector<int>& array)
{
    return array[0];
}

int binarySearch(
    const std::vector<int>& array,
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

int linearSum(const std::vector<int>& array)
{
    int sum = 0;

    for (int value : array)
    {
        sum += value;
    }

    return sum;
}

void quadraticExample(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout
                << "("
                << i
                << ", "
                << j
                << ") ";
        }

        std::cout << "\n";
    }
}

long long cubicExample(int n)
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
    std::vector<int>& array,
    int left,
    int middle,
    int right
)
{
    std::vector<int> leftArray(
        array.begin() + left,
        array.begin() + middle + 1
    );

    std::vector<int> rightArray(
        array.begin() + middle + 1,
        array.begin() + right + 1
    );

    int i = 0;
    int j = 0;
    int k = left;

    while (
        i < static_cast<int>(leftArray.size()) &&
        j < static_cast<int>(rightArray.size())
    )
    {
        if (leftArray[i] <= rightArray[j])
        {
            array[k++] = leftArray[i++];
        }
        else
        {
            array[k++] = rightArray[j++];
        }
    }

    while (i < static_cast<int>(leftArray.size()))
    {
        array[k++] = leftArray[i++];
    }

    while (j < static_cast<int>(rightArray.size()))
    {
        array[k++] = rightArray[j++];
    }
}

void mergeSort(
    std::vector<int>& array,
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

    mergeSort(
        array,
        left,
        middle
    );

    mergeSort(
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

void swapValues(int& a, int& b)
{
    int temporary = a;
    a = b;
    b = temporary;
}

void permutations(
    std::vector<int>& array,
    int left,
    int right
)
{
    if (left == right)
    {
        for (int value : array)
        {
            std::cout << value << " ";
        }

        std::cout << "\n";

        return;
    }

    for (int i = left; i <= right; i++)
    {
        swapValues(
            array[left],
            array[i]
        );

        permutations(
            array,
            left + 1,
            right
        );

        swapValues(
            array[left],
            array[i]
        );
    }
}

std::vector<int> createArray(int size)
{
    std::vector<int> array(size);

    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }

    return array;
}

void constantSpaceExample(
    std::vector<int>& array
)
{
    for (int& value : array)
    {
        value *= 2;
    }
}

void recursiveExample(int n)
{
    if (n <= 0)
    {
        return;
    }

    recursiveExample(n - 1);
}

void printArray(
    const std::vector<int>& array
)
{
    for (int value : array)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
}

int main()
{
    std::vector<int> array = {
        8, 3, 5, 4,
        7, 6, 1, 2
    };

    std::cout
        << "O(1) - First element: "
        << constantTime(array)
        << "\n";

    std::vector<int> sorted = {
        1, 2, 3, 4,
        5, 6, 7, 8
    };

    int target = 6;

    int index = binarySearch(
        sorted,
        0,
        static_cast<int>(sorted.size()) - 1,
        target
    );

    std::cout
        << "O(log n) - Binary Search: "
        << "index "
        << index
        << "\n";

    std::cout
        << "O(n) - Array Sum: "
        << linearSum(array)
        << "\n";

    std::cout
        << "O(n^2) - Quadratic iterations: "
        << array.size() * array.size()
        << "\n";

    std::cout
        << "O(n^3) - Cubic iterations: "
        << cubicExample(5)
        << "\n";

    mergeSort(
        array,
        0,
        static_cast<int>(array.size()) - 1
    );

    std::cout
        << "O(n log n) - Merge Sort: ";

    printArray(array);

    std::cout
        << "O(2^n) - Fibonacci(10): "
        << fibonacci(10)
        << "\n";

    std::cout
        << "O(n!) - Permutations of "
        << "[1, 2, 3]:\n";

    std::vector<int> permutationArray = {
        1, 2, 3
    };

    permutations(
        permutationArray,
        0,
        static_cast<int>(
            permutationArray.size()
        ) - 1
    );

    std::vector<int> dynamicArray =
        createArray(5);

    std::cout
        << "O(n) Space - Dynamic array: ";

    printArray(dynamicArray);

    constantSpaceExample(array);

    recursiveExample(5);

    std::cout
        << "O(n) Auxiliary Stack Space - "
        << "Recursive function completed.\n";

    return 0;
}