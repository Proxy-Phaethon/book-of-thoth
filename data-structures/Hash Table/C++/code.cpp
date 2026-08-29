#include <iostream>
#include <string>
#include <vector>

class HashTable
{
private:
    struct Entry
    {
        std::string key;
        std::string value;
        Entry* next;

        Entry(const std::string& key, const std::string& value)
            : key(key), value(value), next(nullptr)
        {
        }
    };

    std::vector<Entry*> buckets;
    int tableSize;

    unsigned long hash(const std::string& key) const
    {
        unsigned long value = 0;

        for (char character : key)
        {
            value = value * 31 + static_cast<unsigned char>(character);
        }

        return value;
    }

    int getIndex(const std::string& key) const
    {
        return hash(key) % buckets.size();
    }

public:
    HashTable(int capacity = 16)
        : buckets(capacity, nullptr), tableSize(0)
    {
    }

    ~HashTable()
    {
        clear();
    }

    void insert(const std::string& key, const std::string& value)
    {
        int index = getIndex(key);

        Entry* current = buckets[index];

        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->value = value;
                return;
            }

            current = current->next;
        }

        Entry* entry = new Entry(key, value);

        entry->next = buckets[index];
        buckets[index] = entry;

        tableSize++;
    }

    std::string search(const std::string& key) const
    {
        int index = getIndex(key);

        Entry* current = buckets[index];

        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current->value;
            }

            current = current->next;
        }

        return "";
    }

    bool update(const std::string& key, const std::string& value)
    {
        int index = getIndex(key);

        Entry* current = buckets[index];

        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->value = value;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    bool remove(const std::string& key)
    {
        int index = getIndex(key);

        Entry* current = buckets[index];
        Entry* previous = nullptr;

        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (previous == nullptr)
                {
                    buckets[index] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                delete current;
                tableSize--;

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    bool contains(const std::string& key) const
    {
        int index = getIndex(key);

        Entry* current = buckets[index];

        while (current != nullptr)
        {
            if (current->key == key)
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    int size() const
    {
        return tableSize;
    }

    void clear()
    {
        for (Entry*& bucket : buckets)
        {
            Entry* current = bucket;

            while (current != nullptr)
            {
                Entry* next = current->next;

                delete current;

                current = next;
            }

            bucket = nullptr;
        }

        tableSize = 0;
    }
};

int main()
{
    HashTable table;

    table.insert("name", "Zia");
    table.insert("language", "C++");
    table.insert("level", "beginner");

    std::cout << "Search: "
              << table.search("language")
              << "\n";

    table.update("level", "intermediate");

    std::cout << "Contains name: "
              << (table.contains("name") ? "true" : "false")
              << "\n";

    table.remove("language");

    std::cout << "Size: "
              << table.size()
              << "\n";

    return 0;
}