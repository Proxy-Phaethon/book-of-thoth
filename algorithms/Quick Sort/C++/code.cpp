#include <iostream>
#include <vector>
#include <utility>

int partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivotIndex = partition(arr, low, high);

    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}

int main()
{
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};

    quickSort(arr, 0, arr.size() - 1);

    for (int value : arr)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}