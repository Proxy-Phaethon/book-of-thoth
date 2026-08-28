#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
} LinkedList;

void append(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        return;
    }

    Node *current = list->head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;
}

void prepend(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return;
    }

    new_node->value = value;
    new_node->next = list->head;

    list->head = new_node;
}

void insert(LinkedList *list, int value, int index)
{
    if (index < 0)
    {
        return;
    }

    if (index == 0)
    {
        prepend(list, value);
        return;
    }

    Node *current = list->head;

    for (int i = 0; current != NULL && i < index - 1; i++)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        return;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return;
    }

    new_node->value = value;
    new_node->next = current->next;

    current->next = new_node;
}

void delete(LinkedList *list, int value)
{
    if (list->head == NULL)
    {
        return;
    }

    if (list->head->value == value)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    Node *current = list->head;

    while (current->next != NULL)
    {
        if (current->next->value == value)
        {
            Node *temp = current->next;

            current->next = temp->next;
            free(temp);

            return;
        }

        current = current->next;
    }
}

int search(const LinkedList *list, int value)
{
    Node *current = list->head;
    int index = 0;

    while (current != NULL)
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

void print_list(const LinkedList *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        printf("%d", current->value);

        if (current->next != NULL)
        {
            printf(" ");
        }

        current = current->next;
    }

    printf("\n");
}

void free_list(LinkedList *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        Node *next = current->next;

        free(current);

        current = next;
    }

    list->head = NULL;
}

int main(void)
{
    LinkedList list = {NULL};

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);

    prepend(&list, 5);

    insert(&list, 15, 2);

    delete(&list, 20);

    printf("List: ");
    print_list(&list);

    printf("Search result: %d\n", search(&list, 30));

    free_list(&list);

    return 0;
}