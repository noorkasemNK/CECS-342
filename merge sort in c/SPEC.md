# SPEC.md
# had ai write this for me, and I edited it up a bit

CECS 342, Assignment 3 — Merge Sort in C
Noor Kasem

## Assignment requirement

From `instructions.txt`:

> Implement the merge sort algorithm by defining the following C procedure:
> `void merge_sort(int *a, size_t n);`
>
> The implementation of merge sort in C will require a temporary array. This
> array has to be dynamically allocated (not automatically).

Deliverables required: `merge_sort.h`, `merge_sort.c`, `main.c`, and
`output.txt`. `AGENTS.md` and `SPEC.md` are additionally required because AI
was used.

## Files

- `merge_sort.h` — declares `void merge_sort(int *a, size_t n);`, exactly as
  specified.
- `merge_sort.c` — implementation:
  - `merge(int *arr, int *temp, size_t left, size_t cent, size_t right)` —
    merges two already-sorted halves `arr[left..cent]` and
    `arr[cent+1..right]` into order, using `temp` as scratch space and
    copying the merged result back into `arr`. Uses `<=` when comparing so
    the sort is stable.
  - `merge_sort_range(int *arr, int *temp, size_t left, size_t right)` —
    static helper that recursively splits the range in half, sorts each
    half, then calls `merge` to combine them. Base case: a range of length
    0 or 1 (`left >= right`) is already sorted.
  - `merge_sort(int *arr, size_t d)` — the public entry point matching the
    required signature. Handles the trivial case (`d < 2`), allocates a
    single temporary array once with `malloc(d * sizeof(int))` (dynamic
    allocation, not a stack array, as required), checks for allocation
    failure, calls `merge_sort_range` over the full array, and `free`s the
    temporary array before returning.
- `main.c` — test driver. Prints the input and sorted output for: an empty
  array, a single-element array, a small 3-element array, an array with
  negative numbers, an array with duplicate values, and a randomized
  100-element array (seeded with `srand(12345u)` for reproducibility).
- `output.txt` — captured stdout from running the compiled program.

## Design notes

- The temporary array is allocated exactly once per top-level call to
  `merge_sort`, not once per recursive call, to avoid repeated
  `malloc`/`free` overhead during recursion.
- `size_t` is used throughout for indices/lengths to match the signature
  required by the header and to avoid signed/unsigned comparison warnings.
- Midpoint is computed as `left + (right - left) / 2` rather than
  `(left + right) / 2` to avoid unsigned overflow on large ranges.

## Verification

Compiled with `clang -std=c11 -Wall -Wextra -pedantic main.c merge_sort.c`
with no warnings, and run to confirm all test cases in `main.c` produce
correctly sorted output (see `output.txt`).
