# Queue

## Problem

Implement a **Queue** data structure from scratch.

A Queue is a linear data structure that follows the **FIFO (First In, First Out)** principle. The first element added to the queue is the first element to be removed.

Implement the queue using a dynamically allocated array.

### Requirements

Implement the following operations:

* **Enqueue** a value at the rear of the queue.
* **Dequeue** the value from the front of the queue.
* **Front** to view the front value without removing it.
* **Is Empty** to determine whether the queue contains any elements.
* **Size** to return the number of elements currently in the queue.
* **Free** all dynamically allocated memory when the queue is no longer needed.

The queue should use a **circular array** so that freed positions at the front can be reused.

The queue should automatically grow when it reaches its capacity.

### Queue Structure

A queue can be visualized as:

```text
FRONT                         REAR
  │                             │
  ▼                             ▼
┌─────┬─────┬─────┬─────┐
│ 10  │ 20  │ 30  │ 40  │
└─────┴─────┴─────┴─────┘
  │                       │
  └── first in            └── last in
```

Calling `dequeue()` removes `10` first.

### Operations

#### Enqueue

Add a value to the rear of the queue.

```text
Before:

FRONT              REAR
  │                  │
  ▼                  ▼
10 → 20 → 30

enqueue(40)

After:

FRONT                    REAR
  │                        │
  ▼                        ▼
10 → 20 → 30 → 40
```

#### Dequeue

Remove and return the value at the front of the queue.

```text
Before:

FRONT              REAR
  │                  │
  ▼                  ▼
10 → 20 → 30 → 40

dequeue()

Result: 10

After:

FRONT          REAR
  │              │
  ▼              ▼
20 → 30 → 40
```

If the queue is empty, `dequeue()` should indicate that no value is available.

#### Front

Return the value at the front without removing it.

```text
Queue:

FRONT
  │
  ▼
20 → 30 → 40

front()

Result: 20
```

The queue remains unchanged.

#### Is Empty

Return whether the queue contains zero elements.

```text
Empty Queue:

FRONT
  │
  ▼
NULL

is_empty()

Result: true
```

#### Size

Return the number of elements currently stored.

```text
Queue:

10 → 20 → 30

size()

Result: 3
```

## Circular Queue

The queue should reuse empty positions instead of shifting every element.

For example:

```text
Initial:

[10][20][30][  ]

 dequeue()

[  ][20][30][  ]
  ↑       ↑
 FRONT   REAR

 enqueue(40)

[40][20][30][  ]
  ↑       ↑
 REAR    FRONT
```

The rear wraps around to the beginning of the array.

This allows both `enqueue()` and `dequeue()` to operate without shifting the remaining elements.

## Example

Perform the following operations:

```text
enqueue(10)
enqueue(20)
enqueue(30)
front()
dequeue()
enqueue(40)
size()
```

The operations produce:

```text
front()   → 10
dequeue() → 10
size()    → 3
```

The final queue is:

```text
FRONT
  │
  ▼
20 → 30 → 40
          ▲
         REAR
```

## Edge Cases

Your implementation should correctly handle:

* Creating an empty queue.
* Enqueuing into an empty queue.
* Dequeuing from an empty queue.
* Viewing the front of an empty queue.
* Dequeuing the final element.
* Reusing positions freed by dequeue operations.
* Wrapping around the underlying array.
* Growing the queue when capacity is reached.
* Multiple enqueue and dequeue operations.
* Reusing a queue after it becomes empty.

## Constraints

* The queue may contain up to `100000` elements.
* Each element is an integer.
* Values may be positive, negative, or zero.
* Duplicate values are allowed.

## Complexity Requirements

| Operation | Expected Complexity |
| --------- | ------------------: |
| Enqueue   |    `O(1)` amortized |
| Dequeue   |              `O(1)` |
| Front     |              `O(1)` |
| Is Empty  |              `O(1)` |
| Size      |              `O(1)` |

Growing the underlying array may require `O(n)` time for an individual `enqueue`, but the amortized complexity should remain `O(1)`.

Auxiliary space should be `O(n)` for the elements stored in the queue.