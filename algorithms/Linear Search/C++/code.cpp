#include <iostream>
#include <vector>

int linearSearch(const std::vector<int>& arr, int target)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    std::vector<int> arr = {10, 25, 7, 42, 18};
    int target = 42;

    int result = linearSearch(arr, target);

    std::cout << result << "\n";

    return 0;
}