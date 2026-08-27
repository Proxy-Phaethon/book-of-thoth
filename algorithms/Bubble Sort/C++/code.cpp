#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& arr)
{
    int size = arr.size();

    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

int main()
{
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    bubbleSort(arr);

    for (int value : arr)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}