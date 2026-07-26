# validate_token

Validate API tokens with the **Luhn checksum** — the same check digit scheme
used by credit-card numbers.

## Legend

An AI platform issues API tokens to its agents. To catch typos and obviously
forged tokens before doing any expensive lookup, every token ends with a check
digit computed with the Luhn algorithm.

A token is a string of decimal digits, optionally written with `-` or space
separators for readability (for example `4539-1488-0343-6467`). The separators
carry no meaning and must be ignored. After removing them, the token must
consist only of digits.

The security gateway wants to reject any token that fails the checksum, fast.

## The Luhn algorithm

Given a string of digits `d_1 d_2 ... d_n` (left to right):

1. Starting from the **rightmost** digit and moving left, double every second
   digit — the ones in positions 2nd-from-right, 4th-from-right, and so on.
2. If doubling gives a number greater than 9, subtract 9 (equivalently, add the
   two decimal digits of the product: `12 -> 1 + 2 = 3`).
3. Sum all resulting values — the doubled-and-adjusted digits together with the
   untouched ones.
4. The token is valid **iff** that total is a multiple of 10.

Worked example for `79927398713`:

```
digit :   7   9   9   2   7   3   9   8   7   1   3
double:       x       x       x       x       x       <- every 2nd from the right
value :   7  18   9   4   7   6   9  16   7   2   3
adjust:   7   9   9   4   7   6   9   7   7   2   3   <- 18-9=9, 16-9=7

sum = 70,  70 % 10 == 0  ->  VALID
```

## Task

You are given `M` candidate tokens. For each one:

- remove all `-` and space characters;
- if what remains is empty or contains any non-digit character, the token is
  `INVALID`;
- otherwise apply the Luhn check: print `VALID` if the checksum passes,
  `INVALID` if it does not.

## Constraints

| Quantity     | Range |
|--------------|-------------------------------------------------|
| `M`          | `1 <= M <= 100000`                              |
| token length | 1 to 100 characters                             |
| token chars  | digits, `-`, and spaces (given verbatim)        |

## Input format

```
M                # number of tokens
<token 1>        # one candidate token per line
...
<token M>
```

## Output format

`M` lines: line `t` is `VALID` or `INVALID` for the `t`-th token.

### Example

```
input                    output
-----                    ------
4                        VALID
4539-1488-0343-6467      INVALID
8273 1232 7352 0569      VALID
79927398713              INVALID
1234-5678-9012-345a
```

## Approach

`validate_token.hpp` splits the job into three small, separately testable steps,
composed by `algo::validate_token`:

| Function | Does |
|----------|------|
| `remove_special_characters` | erase–remove idiom over `-` and `' '`. |
| `is_digits_only`            | rejects the empty string and any non-digit. |
| `check_luhn_algorithm_is_valid` | walks the string **in reverse** (`rbegin`/`rend`) so "every second digit from the right" is just "odd index", with no dependence on the token's length parity. |

All three are `O(len)`, so the whole run is linear in the total input size.

## Files

- `validate_token.hpp` — header-only implementation.
- `validate_token_test.cpp` — unit tests (doctest).
- `main.cpp` — demo driver: reads `M` and then `M` tokens from standard input.

## Commands (run from the workspace root)

```
task test -- validate_token   # build & run this subproject's unit tests
task run  -- validate_token   # build & run the demo (main.cpp)
```

The demo reads from standard input, so you can either type the tokens in or feed
it a file:

```powershell
task run -- validate_token < tokens.txt
```
