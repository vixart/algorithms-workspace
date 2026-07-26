# secret_number

Recover a shared secret prime from several numbers that are all multiples of it:
take the **gcd** of all messages, then its **largest prime factor**.

## Legend

Valentina and Dmitry exchange secret messages. Every message carries a single
number — the real information they want to share.

To keep an eavesdropper from reading it, they agreed in advance on one secret
prime `P`. Instead of sending the real number `x`, the sender transmits the
disguised value:

```
m = x * P
```

So every intercepted message is the product of the shared secret prime `P` and
some real number `x` (the `x` values differ from message to message and are
never revealed).

You are the interceptor. You have captured several disguised messages, and your
job is to recover the secret prime `P`.

## Task

Given `n` intercepted messages `m_1, m_2, ..., m_n`, where each
`m_i = x_i * P` for some positive integer `x_i` (unknown to you) and the same
secret prime `P`, recover `P`.

Guarantees:

- `P` is prime;
- every message is divisible by `P`;
- the `x_i` taken together share **no** common prime factor.

That last guarantee is what makes the problem solvable: it means
`gcd(m_1, ..., m_n) = P * gcd(x_1, ..., x_n)`, and since the `x_i` share no
common prime, `gcd(x_i) = 1` — so the gcd of the messages *is* `P`.

## Constraints

| Quantity | Range |
|----------|-------------------------|
| `n`      | `2 <= n <= 100`         |
| `m_i`    | `2 <= m_i <= 10^18`     |
| `P`      | prime, `2 <= P <= 10^18`|

## Input format

```
n                        # number of intercepted messages
m_1 m_2 ... m_n          # the messages, space-separated
```

## Output format

A single integer — the secret prime `P`.

### Example

```
input           output
-----           ------
3               7
21 35 28
```

`gcd(21, 35, 28) = 7`, and the largest prime factor of `7` is `7`.

## Approach

Two steps, in `secret_number.hpp`:

1. **`secret_number(n, messages)`** — folds `std::gcd` over all messages.
   Because every `m_i` is divisible by `P` and the cofactors `x_i` share no
   common prime, the result is exactly `P`. Cost: `n` gcds, i.e.
   `O(n · log(max m_i))`.
2. **`max_prime_factor(v)`** — trial division that returns the largest prime
   divisor. Kept as a separate function so the answer is still correct if the
   guarantee "`gcd(x_i) = 1`" is relaxed (then the gcd is `P` times something
   and we need its largest prime factor).

`max_prime_factor` peels off the factors 2 and 3 first, then tests only
candidates of the form `6k ± 1` — every prime greater than 3 has that shape, so
this does about a third of the iterations of a naive scan. The loop condition is
written `i <= v / i` rather than `i * i <= v`, because `i * i` overflows
`long long` for values near `10^18`. Worst case (gcd is prime) is `O(sqrt(v))`.

## Files

- `secret_number.hpp` — header-only implementation (`algo::secret_number`,
  `algo::max_prime_factor`).
- `secret_number_test.cpp` — unit tests (doctest).
- `main.cpp` — demo driver.
- `input.txt` — sample input for the demo.

> See also `_one_file_solution/` in the repo root: the same algorithm packed
> into a single file with no header.

## Commands (run from the workspace root)

```
task test -- secret_number   # build & run this subproject's unit tests
task run  -- secret_number   # build & run the demo (main.cpp)
```

The demo reads two lines — `n`, then the messages — from `input.txt` next to
the executable if that file exists, otherwise from standard input. Commas are
accepted as separators too, so `21, 35, 28` and `21 35 28` both work.
