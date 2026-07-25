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
Valentina and Dmitry are exchanging secret messages. Every message they send to each other contains a single number -- the real information they want to share.

To keep an eavesdropper from reading the real number, they agreed in advance on one secret prime P. Before sending a message, the sender does not transmit the real number x directly. Instead they transmit the disguised value

m = x * P
So every intercepted message is the product of the shared secret prime P and some real number x (the real numbers are different from message to message and are never revealed).

You are an interceptor. You have captured several of these disguised messages. Your job is to recover the secret prime P.

Task
Given n intercepted messages m_1, m_2, ..., m_n, where each

m_i = x_i * P
for some positive integer x_i (unknown to you) and the same secret prime P, recover P.

It is guaranteed that:

P is a prime number,
every message is divisible by P,
the numbers x_i taken together share no common prime factor
Constraints
2 <= n <= 100
2 <= m_i <= 10^18
P is prime and 2 <= P <= 10^18.
Input format
The first line contains a single integer n -- the number of intercepted messages (2 <= n <= 100).
The second line contains n space-separated integers m_1 m_2 ... m_n -- the intercepted messages (2 <= m_i <= 10^18).
Output format
Print a single integer -- the secret prime P.