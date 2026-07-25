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
An AI agent encrypts its outbound messages with a classic (and weak) repeating-key XOR cipher. A secret key of K bytes is chosen once. To encrypt a plaintext message P (a sequence of bytes), each plaintext byte is XOR-ed with a key byte that cycles through the key:

cipher[i] = plain[i] XOR key[i mod K]
The ciphertext is then transmitted as a lowercase hexadecimal string (two hex digits per byte).

The protocol has a fatal flaw: every message begins with the same fixed handshake string H (a banner or protocol header). You know H, and you know the key length K (with K <= len(H)). This is a textbook known-plaintext attack: the first K plaintext bytes are known, which is enough to recover the whole key.

You have intercepted M messages, all encrypted with the same key and all starting with H. Recover the key and decrypt every message.

Task
Given the key length K, the known plaintext prefix H, and M hex-encoded ciphertexts, recover the K-byte key and print the full decrypted plaintext of each message.

Input format
The first line contains two integers K and M (1 <= K <= 64, 1 <= M <= 100).
The second line contains the known handshake string H, given verbatim (it may contain spaces) with K <= len(H) <= 1000.
Each of the next M lines contains one ciphertext as a lowercase hexadecimal string of even length. Each message is between K and 100000 bytes (up to 200000 hex characters).
Output format
Print M lines. Line t is the decrypted plaintext of the t-th ciphertext, printed as raw text. Every plaintext is guaranteed to consist of printable ASCII characters (bytes 32..126), possibly including spaces.