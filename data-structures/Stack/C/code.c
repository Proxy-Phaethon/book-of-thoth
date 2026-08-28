#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int size;
    int capacity;
} Stack;

void push(Stack *stack, int value)
{
    if (stack->size == stack->capacity)
    {
        int new_capacity = stack->capacity * 2;

        int *new_data = realloc(
            stack->data,
            new_capacity * sizeof(int)
        );

        if (new_data == NULL)
        {
            return;
        }

        stack->data = new_data;
        stack->capacity = new_capacity;
    }

    stack->data[stack->size] = value;
    stack->size++;
}

int pop(Stack *stack, int *value)
{
    if (stack->size == 0)
    {
        return 0;
    }

    stack->size--;
    *value = stack->data[stack->size];

    return 1;
}

int peek(const Stack *stack, int *value)
{
    if (stack->size == 0)
    {
        return 0;
    }

    *value = stack->data[stack->size - 1];

    return 1;
}

int is_empty(const Stack *stack)
{
    return stack->size == 0;
}

int size(const Stack *stack)
{
    return stack->size;
}

void free_stack(Stack *stack)
{
    free(stack->data);

    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}

int main(void)
{
    Stack stack = {
        .data = malloc(2 * sizeof(int)),
        .size = 0,
        .capacity = 2
    };

    if (stack.data == NULL)
    {
        return 1;
    }

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    int value;

    if (peek(&stack, &value))
    {
        printf("Peek: %d\n", value);
    }

    if (pop(&stack, &value))
    {
        printf("Pop: %d\n", value);
    }

    push(&stack, 40);

    printf("Size: %d\n", size(&stack));

    free_stack(&stack);

    return 0;
}