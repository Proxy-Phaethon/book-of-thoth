#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr)
{
    if (arr.size() <= 1)
    {
        return;
    }

    int max = arr[0];

    for (int value : arr)
    {
        if (value > max)
        {
            max = value;
        }
    }

    std::vector<int> count(max + 1, 0);

    for (int value : arr)
    {
        count[value]++;
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
}

int main()
{
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    countingSort(arr);

    for (int value : arr)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}