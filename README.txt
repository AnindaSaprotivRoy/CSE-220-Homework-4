CSE 220 Homework 4 Spring 2026
==================

Overview
--------
This submission implements the required string functions and Caesar cipher functions in C without using string.h or ctype.h.Using the knowledge of pointer to do this.

Implemented Functions
---------------------
Part 1 in strgPtr.c:
- strgLen
- strgCopy
- strgChangeCase
- strgDiff
- strgInterleave
- strgReverseLetters

Part 2 in cse_caesar.c:
- encryptCaesar
- decryptCaesar

Behavior Notes
--------------
- strgLen returns -1 for NULL.
- strgDiff returns -1 for identical strings and -2 if either input is NULL.
- strgCopy and strgInterleave respect the destination size and always leave room for a null terminator when size is nonzero.
- strgChangeCase flips only letters that are not adjacent to digits.
- strgReverseLetters reverses only letters and leaves digits, spaces, and punctuation in place.

Caesar Cipher Notes
-------------------
- The cipher is position-aware.
- Letters are shifted by (key + index) mod 26.
- Digits are shifted by (key + 2 * index) mod 10.
- The index increases for every character processed.
- encryptCaesar appends __EOM__ on success.
- encryptCaesar returns the number of encrypted alphanumeric characters, -1 when the destination capacity is insufficient, and -2 for NULL input.
- decryptCaesar returns the number of decrypted alphanumeric characters stored, 0 when the plaintext buffer has zero initial capacity, -1 when __EOM__ is missing, and -2 for NULL input.

Testing
-------
- test.c contains a local test harness.
- tests/test_strg.c and tests/test_caesar.c contain Criterion tests.
- The local harness passes in this environment.

Build
-----
- make local builds the local test harness.
- ./build/local_test runs the local tests.
- make test builds and runs the Criterion suite when Criterion is installed.
