# Hash Table

## Problem

Implement a **Hash Table** from scratch that stores key-value pairs.

A hash table uses a **hash function** to convert a key into an index in an underlying array. When multiple keys produce the same index, a **collision** occurs. Your implementation must handle collisions using **separate chaining**.

The hash table should support inserting, searching, updating, and deleting key-value pairs.

### Requirements

Implement the following operations:

* **Insert** a key-value pair into the hash table.
* **Search** for a key and return its associated value.
* **Update** the value associated with an existing key.
* **Delete** a key and its associated value.
* **Contains** to determine whether a key exists.
* **Size** to return the number of key-value pairs.
* **Free** all dynamically allocated memory when the hash table is no longer needed.

The implementation must:

* Use a hash function to determine bucket indices.
* Handle collisions using **separate chaining**.
* Update an existing key instead of creating a duplicate entry.
* Return an appropriate result when searching for or deleting a key that does not exist.
* Handle duplicate insertion of the same key.
* Handle an empty hash table.

## Hash Table Structure

A simplified hash table can be visualized as:

```text
                 HASH TABLE

Key ──► Hash Function ──► Bucket Index
                              │
                              ▼

        ┌───────┬────────────────────────┐
   0    │       │                        │
        ├───────┼────────────────────────┤
   1    │   ●───┼──► [key:value] ─► ... │
        ├───────┼────────────────────────┤
   2    │       │                        │
        ├───────┼────────────────────────┤
   3    │   ●───┼──► [key:value] ─► ... │
        ├───────┼────────────────────────┤
   ...  │       │                        │
        └───────┴────────────────────────┘
```

Each bucket contains a linked list of entries.

## Hash Function

For this problem, use a simple hash function for string keys.

A possible approach is:

```text
hash = 0

for each character in key:
    hash = hash * 31 + character

index = hash % capacity
```

The exact implementation may differ between languages, but the hash function should consistently map the same key to the same bucket.

## Operations

### Insert

Add a key-value pair to the hash table.

```text id="a8v2kq"
insert("name", "Zia")
insert("language", "C")

Hash Table:

"name"     → "Zia"
"language" → "C"
```

If the key already exists, update its value instead of creating another entry.

```text id="m5x9rt"
insert("name", "Zia")
insert("name", "Alex")

Result:

"name" → "Alex"
```

### Search

Find the value associated with a key.

```text id="c3p7nw"
search("name")

Result:

"Alex"
```

If the key does not exist, indicate that the key was not found.

### Update

Change the value associated with an existing key.

```text id="v6k2bd"
Before:

"age" → "21"

update("age", "22")

After:

"age" → "22"
```

If the key does not exist, the table should remain unchanged.

### Delete

Remove a key-value pair.

```text id="q9r4xm"
Before:

"name" → "Zia"
"age"  → "21"

delete("age")

After:

"name" → "Zia"
```

If the key does not exist, the table should remain unchanged.

### Contains

Check whether a key exists.

```text id="w7n3pz"
contains("name") → true
contains("email") → false
```

### Size

Return the number of key-value pairs stored.

```text id="h4m8tc"
"name" → "Zia"
"age"  → "21"
```

```text
size() → 2
```

## Collision Handling

Two different keys may produce the same bucket index.

For example:

```text id="f2q6vk"
"cat" ──────┐
            ├──► Bucket 3
"dog" ──────┘
```

Separate chaining stores both entries in the same bucket:

```text id="n8t4rx"
Bucket 3

┌─────────────┐
│ "cat":"meow"│
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ "dog":"woof"│
└──────┬──────┘
       │
      NULL
```

When searching for a key, traverse the chain and compare keys until the correct entry is found.

## Example

Perform the following operations:

```text id="p5z8cw"
insert("name", "Zia")
insert("language", "C")
insert("level", "beginner")

search("language")
update("level", "intermediate")
contains("name")
delete("language")
size()
```

The operations produce:

```text id="j3v7qm"
search("language") → "C"
contains("name")    → true
size()              → 2
```

The final table contains:

```text id="r9k2xd"
"name"  → "Zia"
"level" → "intermediate"
```

## Edge Cases

Your implementation should correctly handle:

* An empty hash table.
* Inserting the first key-value pair.
* Searching an empty table.
* Deleting from an empty table.
* Searching for a key that does not exist.
* Deleting a key that does not exist.
* Inserting the same key multiple times.
* Multiple keys mapping to the same bucket.
* Deleting the first entry in a collision chain.
* Deleting an entry from the middle of a collision chain.
* Deleting the final entry in a collision chain.
* Keys with empty strings.
* Values containing spaces.

## Constraints

* The table should support up to `100000` key-value pairs.
* Keys are strings.
* Values are strings.
* Keys may contain letters, digits, spaces, and common punctuation.
* Duplicate keys are not allowed.
* Duplicate values are allowed.
* The initial table capacity should be at least `16` buckets.

## Complexity Requirements

Let:

* `n` = number of stored key-value pairs
* `m` = number of buckets

With a good hash function and a reasonable load factor:

| Operation | Average | Worst Case |
| --------- | ------: | ---------: |
| Insert    |  `O(1)` |     `O(n)` |
| Search    |  `O(1)` |     `O(n)` |
| Update    |  `O(1)` |     `O(n)` |
| Delete    |  `O(1)` |     `O(n)` |
| Contains  |  `O(1)` |     `O(n)` |
| Size      |  `O(1)` |     `O(1)` |

Space complexity should be `O(n + m)`.