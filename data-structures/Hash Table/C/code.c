#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry
{
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct HashTable
{
    Entry **buckets;
    int capacity;
    int size;
} HashTable;

unsigned long hash(const char *key)
{
    unsigned long hash = 0;

    while (*key != '\0')
    {
        hash = hash * 31 + (unsigned char)*key;
        key++;
    }

    return hash;
}

char *copy_string(const char *string)
{
    char *copy = malloc(strlen(string) + 1);

    if (copy == NULL)
    {
        return NULL;
    }

    strcpy(copy, string);

    return copy;
}

HashTable *create_hash_table(int capacity)
{
    HashTable *table = malloc(sizeof(HashTable));

    if (table == NULL)
    {
        return NULL;
    }

    table->buckets = calloc(capacity, sizeof(Entry *));

    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }

    table->capacity = capacity;
    table->size = 0;

    return table;
}

void insert(HashTable *table, const char *key, const char *value)
{
    unsigned long index = hash(key) % table->capacity;

    Entry *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            char *new_value = copy_string(value);

            if (new_value == NULL)
            {
                return;
            }

            free(current->value);
            current->value = new_value;

            return;
        }

        current = current->next;
    }

    Entry *entry = malloc(sizeof(Entry));

    if (entry == NULL)
    {
        return;
    }

    entry->key = copy_string(key);
    entry->value = copy_string(value);

    if (entry->key == NULL || entry->value == NULL)
    {
        free(entry->key);
        free(entry->value);
        free(entry);
        return;
    }

    entry->next = table->buckets[index];
    table->buckets[index] = entry;

    table->size++;
}

const char *search(const HashTable *table, const char *key)
{
    unsigned long index = hash(key) % table->capacity;

    Entry *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }

        current = current->next;
    }

    return NULL;
}

int update(HashTable *table, const char *key, const char *value)
{
    unsigned long index = hash(key) % table->capacity;

    Entry *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            char *new_value = copy_string(value);

            if (new_value == NULL)
            {
                return 0;
            }

            free(current->value);
            current->value = new_value;

            return 1;
        }

        current = current->next;
    }

    return 0;
}

int delete(HashTable *table, const char *key)
{
    unsigned long index = hash(key) % table->capacity;

    Entry *current = table->buckets[index];
    Entry *previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
            {
                table->buckets[index] = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current->key);
            free(current->value);
            free(current);

            table->size--;

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

int contains(const HashTable *table, const char *key)
{
    return search(table, key) != NULL;
}

int size(const HashTable *table)
{
    return table->size;
}

void free_hash_table(HashTable *table)
{
    if (table == NULL)
    {
        return;
    }

    for (int i = 0; i < table->capacity; i++)
    {
        Entry *current = table->buckets[i];

        while (current != NULL)
        {
            Entry *next = current->next;

            free(current->key);
            free(current->value);
            free(current);

            current = next;
        }
    }

    free(table->buckets);
    free(table);
}

int main(void)
{
    HashTable *table = create_hash_table(16);

    if (table == NULL)
    {
        return 1;
    }

    insert(table, "name", "Zia");
    insert(table, "language", "C");
    insert(table, "level", "beginner");

    const char *language = search(table, "language");

    if (language != NULL)
    {
        printf("Search: %s\n", language);
    }

    update(table, "level", "intermediate");

    printf("Contains name: %s\n",
           contains(table, "name") ? "true" : "false");

    delete(table, "language");

    printf("Size: %d\n", size(table));

    free_hash_table(table);

    return 0;
}