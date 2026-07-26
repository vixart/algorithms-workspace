# xor_key

Break a repeating-key XOR cipher with a **known-plaintext attack**: every
message starts with the same handshake string, which hands you the key.

## Legend

An AI agent encrypts its outbound messages with a classic (and weak)
repeating-key XOR cipher. A secret key of `K` bytes is chosen once; each
plaintext byte is XOR-ed with a key byte that cycles through the key:

```
cipher[i] = plain[i] XOR key[i mod K]
```

The ciphertext is then transmitted as a lowercase hexadecimal string, two hex
digits per byte.

The protocol has a fatal flaw: **every message begins with the same fixed
handshake string `H`** (a banner or protocol header). You know `H`, and you know
the key length `K` (with `K <= len(H)`). That is enough to recover the whole key.

## Why the attack works

XOR is its own inverse, so from `cipher[i] = plain[i] XOR key[i mod K]` it
follows that:

```
key[i mod K] = plain[i] XOR cipher[i]
```

For the first `K` bytes of any message the plaintext is known — it is the start
of `H` — so:

```
key[i] = H[i] XOR cipher[i]        for i = 0 .. K-1
```

One intercepted message is therefore enough to recover all `K` key bytes; every
other message then decrypts by XOR-ing against the cycling key.

## Task

Given the key length `K`, the known plaintext prefix `H`, and `M` hex-encoded
ciphertexts, recover the `K`-byte key and print the full decrypted plaintext of
each message.

## Constraints

| Quantity        | Range |
|-----------------|--------------------------------------------------|
| `K`             | `1 <= K <= 64`                                   |
| `M`             | `1 <= M <= 100`                                  |
| `len(H)`        | `K <= len(H) <= 1000` (may contain spaces)       |
| message size    | `K` to 100000 bytes (up to 200000 hex chars)     |
| plaintext bytes | printable ASCII, `32..126`                       |

## Input format

```
K M              # key length and number of messages
H                # the known handshake string, verbatim
<hex 1>          # one lowercase hex ciphertext per line, even length
...
<hex M>
```

## Output format

`M` lines: line `t` is the decrypted plaintext of the `t`-th ciphertext, printed
as raw text.

### Example

```
input                                                   output
-----                                                   ------
3 1                                                     key: activate protocol now
key
0000005145180811101d040d0e4509190a0d0406160745170412
```

Here the first three ciphertext bytes are `00 00 00`, so the key is
`"key" XOR 00 00 00` = `"key"` itself.

## Approach

`xor_key.hpp` is four small functions:

| Function | Does |
|----------|------|
| `hex_to_bytes(hex)` | decodes a hex string into raw bytes, two chars at a time; throws `std::invalid_argument` on odd length. |
| `xor_strings(a, b, n)` | XORs the first `n` bytes of two strings. |
| `find_key(K, H, cipher)` | decodes the ciphertext's leading `len(H)` bytes and XORs them against `H`, keeping `K` bytes — the key. |
| `decipher_text(key, cipher)` | decodes the whole ciphertext and XORs byte `i` against `key[i % K]`. |

Everything is a single linear pass: `O(total hex length)`. `decipher_text`
reserves the output up front so decrypting a 100000-byte message does not
reallocate its way there.

Note that `find_key` needs only **one** ciphertext — `main.cpp` derives the key
from the first message and reuses it for all of them, which is exactly what the
shared-key assumption allows.

## Files

- `xor_key.hpp` — header-only implementation.
- `xor_key_test.cpp` — unit tests (doctest).
- `main.cpp` — demo driver: prompts for `K`/`M`, the handshake, then the
  ciphertexts, and prints each plaintext.

## Commands (run from the workspace root)

```
task test -- xor_key   # build & run this subproject's unit tests
task run  -- xor_key   # build & run the demo (main.cpp)
```

The demo reads from standard input and prints a prompt before each field, so it
is usable interactively; when feeding it a file the prompts are simply
interleaved with the output:

```powershell
task run -- xor_key < messages.txt
```
