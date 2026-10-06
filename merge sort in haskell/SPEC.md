# SPEC.md

CECS 342, Assignment 4 — Merge Sort in Haskell
Noor Kasem

## Assignment requirement

From `instructions.txt`:

> Recall the sorting algorithm merge sort (John von Neumann in 1945). Write
> this algorithm in the Haskell programing language by implementing the
> following function:
>
> `msort :: (Ord a) => [a] -> [a] -- Merge sort a list.`

Deliverables required: source `.hs` file(s) and `output.txt`. `AGENTS.md` and
`SPEC.md` are additionally required because AI was used.

## Files

- `merge sort.hs` — implementation:
  - `merge :: Ord a => [a] -> [a] -> [a]` — merges two already-sorted lists
    into one sorted list, using `<=` when comparing so the sort is stable.
  - `splitInHalf :: [a] -> ([a], [a])` — splits a list into two roughly
    equal halves via `splitAt (length xs \`div\` 2) xs`.
  - `msort :: Ord a => [a] -> [a]` — the required entry point. Base cases
    for `[]` and single-element lists; otherwise splits the list in half,
    recursively sorts each half, and merges the results.
  - `testSort` / `main` — test driver. Prints `Input:` / `Sorted:` for: an
    empty list, a single-element list, a small 3-element list, a list with
    negative numbers, and a list of strings — matching the test cases shown
    in `instructions.txt`.
- `output.txt` — captured stdout from running the compiled program.

## Design notes

- `msort` is a straightforward top-down merge sort: split the list roughly
  in half, sort each half recursively, then merge the two sorted halves.
- `splitInHalf` uses `length`/`splitAt` rather than the classic
  fast/slow-pointer split, which is simpler in Haskell at the cost of an
  extra `O(n)` pass to compute the length.
- `merge` is written with pattern matching (`[] ys`, `xs []`, and the
  general `(x:xs) (y:ys)` case) instead of explicit index arithmetic, which
  is the idiomatic way to express it in Haskell.

## Verification

Compiled with `ghc -o my_program "merge sort.hs"` and run with
`./my_program > output.txt`, producing correctly sorted output for every
test case (see `output.txt`).
