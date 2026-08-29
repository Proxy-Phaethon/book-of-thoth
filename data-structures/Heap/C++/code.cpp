#include <iostream>
#include <vector>

class MaxHeap
{
private:
    std::vector<int> data;

    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void siftUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (data[parent] >= data[index])
            {
                break;
            }

            swap(data[parent], data[index]);

            index = parent;
        }
    }

    void siftDown(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < static_cast<int>(data.size()) &&
                data[left] > data[largest])
            {
                largest = left;
            }

            if (right < static_cast<int>(data.size()) &&
                data[right] > data[largest])
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            swap(data[index], data[largest]);

            index = largest;
        }
    }

public:
    void insert(int value)
    {
        data.push_back(value);

        siftUp(data.size() - 1);
    }

    int extractMax()
    {
        if (data.empty())
        {
            return -1;
        }

        int maximum = data[0];

        data[0] = data.back();
        data.pop_back();

        if (!data.empty())
        {
            siftDown(0);
        }

        return maximum;
    }

    int peekMax() const
    {
        if (data.empty())
        {
            return -1;
        }

        return data[0];
    }

    void heapify()
    {
        for (int i = static_cast<int>(data.size()) / 2 - 1;
             i >= 0;
             i--)
        {
            siftDown(i);
        }
    }

    bool isEmpty() const
    {
        return data.empty();
    }

    int size() const
    {
        return data.size();
    }
};

int main()
{
    MaxHeap heap;

    heap.insert(40);
    heap.insert(20);
    heap.insert(70);
    heap.insert(10);
    heap.insert(90);
    heap.insert(50);

    std::cout << "Peek Max: "
              << heap.peekMax()
              << "\n";

    std::cout << "Extract Max: "
              << heap.extractMax()
              << "\n";

    std::cout << "Size: "
              << heap.size()
              << "\n";

    return 0;
}