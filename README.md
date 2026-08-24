<div align="center">

```text
████████╗██╗  ██╗ ██████╗ ████████╗██╗  ██╗
╚══██╔══╝██║  ██║██╔═══██╗╚══██╔══╝██║  ██║
   ██║   ███████║██║   ██║   ██║   ███████║
   ██║   ██╔══██║██║   ██║   ██║   ██╔══██║
   ██║   ██║  ██║╚██████╔╝   ██║   ██║  ██║
   ╚═╝   ╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝
```

### *Algorithms. Data Structures. First Principles.*

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge\&logo=c\&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge\&logo=python\&logoColor=white)

</div>

---

## `> What is this?`

**Book of Thoth** is a personal collection of algorithms and data structures implemented from scratch.

The purpose is simple:

**learn Computer Science by building it.**

Every problem is approached from the underlying idea first, then implemented in **C, C++, and Python**.

No built-in sorting functions.

No copying implementations.

No "I understand it because I watched a 14-minute video at 1.75× speed."

Just the algorithm.

---

## `> The Approach`

```text
                  ┌───────────────────┐
                  │      PROBLEM      │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │   UNDERSTAND IT   │
                  └─────────┬─────────┘
                            │
                ┌───────────┼───────────┐
                ▼           ▼           ▼
           ┌────────┐  ┌────────┐  ┌────────┐
           │   C    │  │  C++   │  │ Python │
           └───┬────┘  └───┬────┘  └───┬────┘
               │            │            │
               └────────────┼────────────┘
                            ▼
                  ┌───────────────────┐
                  │      TEST IT      │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │     UNDERSTAND    │
                  │       AGAIN       │
                  └───────────────────┘
```

The languages are not the subject.

The **algorithm is**.

Using three languages makes it harder to confuse a language's syntax with the actual computational idea.

---

## `> Chapters`

### Algorithms

```text
[✓] Insertion Sort
[✓] Merge Sort
[ ] Selection Sort
[ ] Bubble Sort
[ ] Quick Sort
[ ] Heap Sort
[ ] Counting Sort
[ ] Radix Sort
[ ] Linear Search
[ ] Binary Search
[ ] Breadth-First Search
[ ] Depth-First Search
```

### Data Structures

```text
[ ] Linked List
[ ] Stack
[ ] Queue
[ ] Hash Table
[ ] Binary Search Tree
[ ] Heap
[ ] Graph
```

### Further Chapters

```text
[ ] Recursion
[ ] Divide & Conquer
[ ] Greedy Algorithms
[ ] Dynamic Programming
[ ] Graph Algorithms
[ ] String Algorithms
[ ] Complexity Analysis
```

---

## `> A Chapter Looks Like This`

```text
merge-sort/
│
├── problem.md
│
├── c/
│   ├── code.c
│   └── ...
│
├── cpp/
│   ├── code.cpp
│   └── ...
│
└── python/
    └── code.py
```

Each chapter starts with the problem.

Then comes the implementation.

Then comes the inevitable battle with a missing semicolon.

---

## `> The Three Languages`

```text
             ┌──────────────┐
             │   ALGORITHM  │
             └──────┬───────┘
                    │
          ┌─────────┼─────────┐
          │         │         │
          ▼         ▼         ▼
       ┌─────┐   ┌─────┐   ┌─────┐
       │  C  │   │ C++ │   │ Py  │
       └─────┘   └─────┘   └─────┘
          │         │         │
          ▼         ▼         ▼
       memory    abstraction  clarity
       control     & STL      & speed
```

C keeps the machinery visible.

C++ introduces abstraction and stronger data-structure tooling.

Python strips away much of the ceremony and exposes the underlying idea.

Same problem.

Different lenses.

---

## `> Current Progress`

```text
SORTING
████████░░░░░░░░░░░░  40%

SEARCHING
░░░░░░░░░░░░░░░░░░░░   0%

DATA STRUCTURES
░░░░░░░░░░░░░░░░░░░░   0%

GRADUALLY BECOMING
DANGEROUSLY COMPETENT
██████░░░░░░░░░░░░░░  30%
```

---

## `> Philosophy`

> **Don't memorize the spell. Understand the machinery that makes the spell work.**

An implementation is considered learned when it can be reconstructed from the algorithm rather than recalled line-for-line.

The Book is therefore not a collection of solutions.

It is a collection of things that have been **understood**.

---

## `> Why Thoth?`

Thoth is traditionally associated with writing, knowledge, mathematics, and the preservation of wisdom.

A fitting name for a repository whose entire purpose is to collect computational knowledge one chapter at a time.

---

<div align="center">

```text
╔══════════════════════════════════════╗
║                                      ║
║       THE BOOK IS STILL OPEN.        ║
║                                      ║
║          ──── CHAPTER 02 ────        ║
║                                      ║
║             MERGE SORT               ║
║                                      ║
╚══════════════════════════════════════╝
```

**One problem. Three languages. One less thing I don't understand.**

</div>
