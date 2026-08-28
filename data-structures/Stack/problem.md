# Stack

## Problem

Implement a **Stack** data structure from scratch.

A Stack is a linear data structure that follows the **LIFO (Last In, First Out)** principle. The most recently added element is the first element to be removed.

Implement the stack using a dynamically allocated array.

### Requirements

Implement the following operations:

* **Push** a value onto the top of the stack.
* **Pop** the value from the top of the stack.
* **Peek** at the top value without removing it.
* **Is Empty** to determine whether the stack contains any elements.
* **Size** to return the number of elements currently in the stack.
* **Free** all dynamically allocated memory when the stack is no longer needed.

The stack should automatically grow when it runs out of capacity.

### Stack Structure

A stack can be visualized as:

```text
        TOP
         │
         ▼
      ┌─────┐
      │ 30  │ ← most recently pushed
      ├─────┤
      │ 20  │
      ├─────┤
      │ 10  │ ← first pushed
      └─────┘
```

Calling `pop()` removes `30` first.

### Operations

#### Push

Add a value to the top of the stack.

```text
Before:

TOP
 │
 ▼
30
20
10

push(40)

After:

TOP
 │
 ▼
40
30
20
10
```

#### Pop

Remove and return the value at the top of the stack.

```text
Before:

TOP
 │
 ▼
40
30
20
10

pop()

Result: 40

After:

TOP
 │
 ▼
30
20
10
```

If the stack is empty, `pop()` should indicate that no value is available.

#### Peek

Return the value at the top without removing it.

```text
Stack:

TOP
 │
 ▼
30
20
10

peek()

Result: 30
```

The stack remains unchanged.

#### Is Empty

Return whether the stack contains zero elements.

```text
Empty stack:

TOP
 │
 ▼
NULL

is_empty()

Result: true
```

#### Size

Return the number of elements currently stored.

```text
Stack:

30
20
10

size()

Result: 3
```

## Example

Perform the following operations:

```text
push(10)
push(20)
push(30)
peek()
pop()
push(40)
size()
```

The operations produce:

```text
peek() → 30
pop()  → 30
size() → 3
```

The final stack is:

```text
TOP
 │
 ▼
40
20
10
```

## Edge Cases

Your implementation should correctly handle:

* Creating an empty stack.
* Pushing into an empty stack.
* Popping from an empty stack.
* Peeking at an empty stack.
* Popping the final element.
* Growing the stack when capacity is reached.
* Multiple pushes and pops.
* Reusing a stack after it becomes empty.

## Constraints

* The stack may contain up to `100000` elements.
* Each element is an integer.
* Values may be positive, negative, or zero.
* Duplicate values are allowed.

## Complexity Requirements

| Operation | Expected Complexity |
| --------- | ------------------: |
| Push      |    `O(1)` amortized |
| Pop       |              `O(1)` |
| Peek      |              `O(1)` |
| Is Empty  |              `O(1)` |
| Size      |              `O(1)` |

Growing the underlying array may require `O(n)` time for an individual `push`, but the amortized complexity of `push` should remain `O(1)`.

Auxiliary space should be `O(n)` for the elements stored in the stack.