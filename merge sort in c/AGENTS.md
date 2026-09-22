# AGENTS.md

CECS 342, Assignment 3 — Merge Sort in C
Noor Kasem

## AI tool used

Claude Code (Anthropic), used inside VS Code as an editor extension.

## What I wrote myself

I wrote the implementation of `merge`, `merge_sort_range`, and `merge_sort` in
`merge_sort.c`, and the test cases in `main.c`, using:
- My own notes from class
- GeeksforGeeks and W3Schools reference pages on merge sort and C syntax
- A Google/Gemini AI Overview search result for a general refresher on the
  merge sort algorithm
- The structure of my Assignment 1 and 2 `main.c` files as a starting point
  for how to lay out test cases and print output

## What Claude Code helped with


- I pasted my `merge_sort.c` and asked why it wasn't compiling. Claude
  pointed out two typos I had introduced: a stray `"` at the end of
  `#include<stdio.h>"`, and a missing space in `size_tright` that should have
  been `size_t right`.
- After I fixed those, I asked Claude to check my code against
  `instructions.txt` to make sure I wasn't missing a requirement. It flagged
  that I only had the `merge` helper at that point and still needed to write
  the actual `merge_sort(int *a, size_t n)` function the header declares.
- Once I wrote `merge_sort_range` and `merge_sort` myself, I asked Claude to
  re-check the file against the assignment instructions again (correct
  signature, temp array dynamically allocated via `malloc`/`free` instead of
  a stack array, tools-used comment present, correct file/header names). It
  confirmed the file compiled cleanly and matched the spec.
- After writing `main.c`, I asked Claude to review it against the
  instructions as well. It compiled and ran my test cases to confirm the
  output was correct and that the file satisfied the "separate `main.c` with
  reasonable test cases" requirement.

In short: Claude Code was used to debug compiler errors I introduced and to
answer my questions about whether my own code met the assignment
requirements — it did not generate the algorithm or the test cases.
Claude did write the AGENTS.md, i told it to write how it helped me.
