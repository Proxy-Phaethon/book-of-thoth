#include <iostream>
#include <vector>

class Stack
{
private:
    std::vector<int> data;

public:
    void push(int value)
    {
        data.push_back(value);
    }

    int pop()
    {
        if (data.empty())
        {
            return -1;
        }

        int value = data.back();
        data.pop_back();

        return value;
    }

    int peek() const
    {
        if (data.empty())
        {
            return -1;
        }

        return data.back();
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
    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Peek: " << stack.peek() << "\n";
    std::cout << "Pop: " << stack.pop() << "\n";

    stack.push(40);

    std::cout << "Size: " << stack.size() << "\n";

    return 0;
}