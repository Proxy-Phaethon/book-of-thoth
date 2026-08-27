#include <iostream>
#include <vector>
#include <utility>

void heapify(std::vector<int>& arr, int size, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != root)
    {
        std::swap(arr[root], arr[largest]);

        heapify(arr, size, largest);
    }
}

void heapSort(std::vector<int>& arr)
{
    int size = arr.size();

    // Build the max heap.
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    // Move the largest element to the end.
    for (int i = size - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);

        // Restore the max-heap property.
        heapify(arr, i, 0);
    }
}

int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    heapSort(arr);

    for (int value : arr)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}