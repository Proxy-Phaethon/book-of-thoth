#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int middle, int right)
{
    std::vector<int> left_arr(
        arr.begin() + left,
        arr.begin() + middle + 1
    );

    std::vector<int> right_arr(
        arr.begin() + middle + 1,
        arr.begin() + right + 1
    );

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_arr.size() && j < right_arr.size())
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }

        k++;
    }

    while (i < left_arr.size())
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_arr.size())
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;

    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);

    merge(arr, left, middle, right);
}

int main()
{
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    mergeSort(arr, 0, arr.size() - 1);

    for (int value : arr)
        std::cout << value << " ";

    std::cout << "\n";

    return 0;
}