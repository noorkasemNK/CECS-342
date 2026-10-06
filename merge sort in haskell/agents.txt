# AGENTS.md

CECS 342, Assignment 4 — Merge Sort in Haskell
Noor Kasem

## AI tool used

Claude Code (Anthropic), used inside VS Code as an editor extension.

## What I wrote myself

I wrote `merge sort.hs` myself, including the `merge`, `splitInHalf`, and
`msort` functions and the `testSort`/`main` test driver, following the
function signature (`msort :: (Ord a) => [a] -> [a]`) and test-case structure
given in `instructions.txt`.

## What Claude Code helped with

- I asked Claude to check my finished `merge sort.hs` against
  `instructions.txt` to make sure I wasn't missing a requirement. It
  confirmed the `msort` signature and implementation were correct and that
  my test cases matched what was asked for, but flagged two things:
  - I had left the placeholder `"Your Name"` in the printed output instead
    of my actual name.
  - I hadn't generated `output.txt` yet, which the instructions require as a
    deliverable.
- I asked Claude to fix the name placeholder and generate `output.txt` for
  me. It edited the `putStrLn "Name: Your Name"` line to
  `putStrLn "Name: Noor Kasem"`, then compiled the program with
  `ghc -o my_program "merge sort.hs"` and ran `./my_program > output.txt` to
  capture the real program output.
- I also asked Claude what to type in the terminal so I could run that
  compile/run process myself, and it gave me the exact commands.
- Claude pointed out that the compiled binary and intermediate build files
  (`my_program`, `merge sort.o`, `merge sort.hi`) aren't source files and
  suggested removing them before submitting.

In short: Claude Code was used to check my finished code against the
assignment instructions, fix a placeholder I forgot to update, and compile
and run the program to produce `output.txt` — it did not write the `merge`,
`splitInHalf`, or `msort` algorithm.
