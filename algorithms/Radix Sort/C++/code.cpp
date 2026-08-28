#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr, int exponent)
{
    int size = arr.size();
    std::vector<int> output(size);
    int count[10] = {0};

    // Count occurrences of each digit.
    for (int i = 0; i < size; i++)
    {
        int digit = (arr[i] / exponent) % 10;
        count[digit]++;
    }

    // Convert counts into positions.
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the output array from right to left.
    // This preserves stability.
    for (int i = size - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exponent) % 10;

        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the sorted values back.
    for (int i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }
}

void radixSort(std::vector<int>& arr)
{
    if (arr.size() <= 1)
    {
        return;
    }

    int max = arr[0];

    // Find the largest value.
    for (int value : arr)
    {
        if (value > max)
        {
            max = value;
        }
    }

    // Process each digit from least significant
    // to most significant.
    for (int exponent = 1; max / exponent > 0; exponent *= 10)
    {
        countingSort(arr, exponent);
    }
}

int main()
{
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    radixSort(arr);

    for (int value : arr)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}