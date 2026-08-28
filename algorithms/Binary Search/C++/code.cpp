#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        if (arr[middle] == target)
        {
            return middle;
        }

        if (arr[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

int main()
{
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    int target = 11;

    int result = binarySearch(arr, target);

    std::cout << result << "\n";

    return 0;
}