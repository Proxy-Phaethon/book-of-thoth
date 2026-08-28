#include <iostream>

class LinkedList
{
private:
    struct Node
    {
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        clear();
    }

    void append(int value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    void prepend(int value)
    {
        Node* newNode = new Node(value);

        newNode->next = head;
        head = newNode;
    }

    void insert(int value, int index)
    {
        if (index < 0)
        {
            return;
        }

        if (index == 0)
        {
            prepend(value);
            return;
        }

        Node* current = head;

        for (int i = 0; current != nullptr && i < index - 1; i++)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            return;
        }

        Node* newNode = new Node(value);

        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(int value)
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->value == value)
        {
            Node* temp = head;
            head = head->next;

            delete temp;
            return;
        }

        Node* current = head;

        while (current->next != nullptr)
        {
            if (current->next->value == value)
            {
                Node* temp = current->next;

                current->next = temp->next;

                delete temp;
                return;
            }

            current = current->next;
        }
    }

    int search(int value) const
    {
        Node* current = head;
        int index = 0;

        while (current != nullptr)
        {
            if (current->value == value)
            {
                return index;
            }

            current = current->next;
            index++;
        }

        return -1;
    }

    void print() const
    {
        Node* current = head;

        while (current != nullptr)
        {
            std::cout << current->value;

            if (current->next != nullptr)
            {
                std::cout << " ";
            }

            current = current->next;
        }

        std::cout << "\n";
    }

    void clear()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* next = current->next;

            delete current;

            current = next;
        }

        head = nullptr;
    }
};

int main()
{
    LinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.prepend(5);

    list.insert(15, 2);

    list.remove(20);

    std::cout << "List: ";
    list.print();

    std::cout << "Search result: "
              << list.search(30)
              << "\n";

    return 0;
}