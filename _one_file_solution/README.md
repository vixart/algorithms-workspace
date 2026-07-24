# secret_number (single-file variant)

Given several messages (integers), the "secret number" is the largest prime
factor of the greatest common divisor (gcd) of all the messages.

Same algorithm as `secret_number/`, but packed into a **single file with no
header**: `main.cpp` holds both the `algo::` functions and the demo `main()`.
This folder is prefixed with `_` so it is skipped by `task test-all` /
`task projects` (like `_template/`); build it by name instead.

## Files
- `main.cpp` — algorithm (`namespace algo`) **and** the demo driver in one file.
  `main()` is wrapped in `#ifndef SECRET_NUMBER_SIMPLE_NO_MAIN`.
- `secret_number_test.cpp` — unit tests (doctest). They `#include "main.cpp"`
  after defining `SECRET_NUMBER_SIMPLE_NO_MAIN`, so the algorithm is tested
  directly from the same file while its `main()` is skipped.

## Commands (run from the workspace root)
```
task test -- _one_file_solution   # build & run this subproject's unit tests
task run  -- _one_file_solution   # build & run the demo
```

The demo reads two lines — `n`, then the comma-separated messages — from
`input.txt` next to the executable if present, otherwise from standard input.
