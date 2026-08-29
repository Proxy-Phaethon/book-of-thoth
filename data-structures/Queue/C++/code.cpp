#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

void enqueue(Queue *queue, int value)
{
    if (queue->size == queue->capacity)
    {
        int new_capacity = queue->capacity * 2;
        int *new_data = (int *)malloc(new_capacity * sizeof(int));

        if (new_data == NULL)
        {
            return;
        }

        /*
         * Copy elements in logical queue order.
         * This also unwraps the circular array.
         */
        for (int i = 0; i < queue->size; i++)
        {
            int index = (queue->front + i) % queue->capacity;
            new_data[i] = queue->data[index];
        }

        free(queue->data);

        queue->data = new_data;
        queue->capacity = new_capacity;
        queue->front = 0;
        queue->rear = queue->size;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
}

int dequeue(Queue *queue, int *value)
{
    if (queue->size == 0)
    {
        return 0;
    }

    *value = queue->data[queue->front];

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    if (queue->size == 0)
    {
        queue->front = 0;
        queue->rear = 0;
    }

    return 1;
}

int front(const Queue *queue, int *value)
{
    if (queue->size == 0)
    {
        return 0;
    }

    *value = queue->data[queue->front];

    return 1;
}

int is_empty(const Queue *queue)
{
    return queue->size == 0;
}

int size(const Queue *queue)
{
    return queue->size;
}

void free_queue(Queue *queue)
{
    free(queue->data);

    queue->data = NULL;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    queue->capacity = 0;
}

int main(void)
{
    Queue queue = {
        .data = (int *)malloc(2 * sizeof(int)),
        .front = 0,
        .rear = 0,
        .size = 0,
        .capacity = 2
    };

    if (queue.data == NULL)
    {
        return 1;
    }

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    int value;

    if (front(&queue, &value))
    {
        printf("Front: %d\n", value);
    }

    if (dequeue(&queue, &value))
    {
        printf("Dequeue: %d\n", value);
    }

    enqueue(&queue, 40);

    printf("Size: %d\n", size(&queue));

    free_queue(&queue);

    return 0;
}