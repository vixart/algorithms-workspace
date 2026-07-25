# <subproject name>

Short description of the algorithm / mechanism implemented here.

## Files
- `solution.hpp` — header-only implementation.
- `solution_test.cpp` — unit tests (doctest).
- `main.cpp` — optional demo driver.

## Commands (run from the workspace root)
```
task test -- <folder-name>   # build & run this subproject's unit tests
task run  -- <folder-name>   # build & run the demo (main.cpp)
```

Legend
An AI platform issues API tokens to its agents. To catch typos and obviously forged tokens before doing any expensive lookup, every token ends with a check digit computed with the Luhn algorithm (the same checksum used by credit-card numbers).

A token is a string of decimal digits, possibly written with - or space separators for readability (for example 4539-1488-0343-6467). The separators carry no meaning and must be ignored. After removing separators the token must consist only of digits.

The security gateway wants to quickly reject any token that fails the checksum.

Luhn algorithm
Given a string of digits d_1 d_2 ... d_n (left to right), the check is:

Starting from the rightmost digit and moving left, double the value of every second digit (i.e. the digits in positions 2nd-from-right, 4th-from-right, and so on).
If doubling a digit gives a number greater than 9, subtract 9 from it (equivalently, add the two decimal digits of the product).
Sum all the resulting values (the doubled-and-adjusted digits together with the untouched digits).
The token is valid if and only if this total is a multiple of 10.
Task
You are given M candidate tokens. For each token:

remove all - and space separator characters;
if what remains is empty or contains any non-digit character, the token is INVALID;
otherwise apply the Luhn check and output VALID if the checksum passes and INVALID otherwise.
Input format
The first line contains a single integer M -- the number of tokens (1 <= M <= 100000).
Each of the next M lines contains one candidate token. A token line has length between 1 and 100 characters and may contain digits, -, and spaces. Tokens are given verbatim (a token never has leading/trailing content other than the separators described).
Output format
Print M lines. Line t is VALID or INVALID for the t-th token.

