#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int size;
    int capacity;
} MaxHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sift_up(MaxHeap *heap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (heap->data[parent] >= heap->data[index])
        {
            break;
        }

        swap(&heap->data[parent], &heap->data[index]);

        index = parent;
    }
}

void sift_down(MaxHeap *heap, int index)
{
    while (1)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap->size &&
            heap->data[left] > heap->data[largest])
        {
            largest = left;
        }

        if (right < heap->size &&
            heap->data[right] > heap->data[largest])
        {
            largest = right;
        }

        if (largest == index)
        {
            break;
        }

        swap(&heap->data[index], &heap->data[largest]);

        index = largest;
    }
}

void insert(MaxHeap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        int new_capacity = heap->capacity * 2;

        int *new_data = realloc(
            heap->data,
            new_capacity * sizeof(int)
        );

        if (new_data == NULL)
        {
            return;
        }

        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    heap->data[heap->size] = value;
    heap->size++;

    sift_up(heap, heap->size - 1);
}

int extract_max(MaxHeap *heap, int *value)
{
    if (heap->size == 0)
    {
        return 0;
    }

    *value = heap->data[0];

    heap->size--;

    if (heap->size > 0)
    {
        heap->data[0] = heap->data[heap->size];
        sift_down(heap, 0);
    }

    return 1;
}

int peek_max(const MaxHeap *heap, int *value)
{
    if (heap->size == 0)
    {
        return 0;
    }

    *value = heap->data[0];

    return 1;
}

void heapify(MaxHeap *heap)
{
    if (heap->size < 2)
    {
        return;
    }

    for (int i = (heap->size / 2) - 1; i >= 0; i--)
    {
        sift_down(heap, i);
    }
}

int is_empty(const MaxHeap *heap)
{
    return heap->size == 0;
}

int size(const MaxHeap *heap)
{
    return heap->size;
}

void free_heap(MaxHeap *heap)
{
    free(heap->data);

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

int main(void)
{
    MaxHeap heap = {
        .data = malloc(4 * sizeof(int)),
        .size = 0,
        .capacity = 4
    };

    if (heap.data == NULL)
    {
        return 1;
    }

    insert(&heap, 40);
    insert(&heap, 20);
    insert(&heap, 70);
    insert(&heap, 10);
    insert(&heap, 90);
    insert(&heap, 50);

    int value;

    if (peek_max(&heap, &value))
    {
        printf("Peek Max: %d\n", value);
    }

    if (extract_max(&heap, &value))
    {
        printf("Extract Max: %d\n", value);
    }

    printf("Size: %d\n", size(&heap));

    free_heap(&heap);

    return 0;
}