#include <stdio.h>
#include "strgPtr.h"
#include "cse_caesar.h"

// Color codes for output
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int tests_passed = 0;
int tests_failed = 0;

void assert_int_equal(int actual, int expected, const char *test_name) {
    if (actual == expected) {
        printf(GREEN "✓ PASS" RESET ": %s (expected %d, got %d)\n", test_name, expected, actual);
        tests_passed++;
    } else {
        printf(RED "✗ FAIL" RESET ": %s (expected %d, got %d)\n", test_name, expected, actual);
        tests_failed++;
    }
}

void assert_string_equal(const char *actual, const char *expected, const char *test_name) {
    if (actual == NULL && expected == NULL) {
        printf(GREEN "✓ PASS" RESET ": %s\n", test_name);
        tests_passed++;
        return;
    }
    if (actual == NULL || expected == NULL) {
        printf(RED "✗ FAIL" RESET ": %s (NULL mismatch)\n", test_name);
        tests_failed++;
        return;
    }
    
    int match = 1;
    int i = 0;
    while (actual[i] != '\0' || expected[i] != '\0') {
        if (actual[i] != expected[i]) {
            match = 0;
            break;
        }
        i++;
    }
    
    if (match) {
        printf(GREEN "✓ PASS" RESET ": %s (expected \"%s\", got \"%s\")\n", test_name, expected, actual);
        tests_passed++;
    } else {
        printf(RED "✗ FAIL" RESET ": %s (expected \"%s\", got \"%s\")\n", test_name, expected, actual);
        tests_failed++;
    }
}

// strgLen TESTS

void test_strgLen() {
    printf("\n=== Testing strgLen (10 cases) ===\n");
    
    assert_int_equal(strgLen("Stony Brook"), 11, "strgLen: 'Stony Brook'");
    assert_int_equal(strgLen("CSE 220"), 7, "strgLen: 'CSE 220'");
    assert_int_equal(strgLen("C"), 1, "strgLen: 'C'");
    assert_int_equal(strgLen("System Fundamental"), 18, "strgLen: 'System Fundamental'");
    assert_int_equal(strgLen("1"), 1, "strgLen: '1'");
    assert_int_equal(strgLen(""), 0, "strgLen: empty string");
    assert_int_equal(strgLen(NULL), -1, "strgLen: NULL pointer");
    assert_int_equal(strgLen("Hello World"), 11, "strgLen: 'Hello World'");
    assert_int_equal(strgLen("123456789"), 9, "strgLen: '123456789'");
    assert_int_equal(strgLen("a"), 1, "strgLen: 'a'");
}


// strgCopy TESTS

void test_strgCopy() {
    printf("\n=== Testing strgCopy (10 cases) ===\n");
    
    char dest[50];
    
    // Test 1: Normal copy
    strgCopy("Computer Science", dest, 50);
    assert_string_equal(dest, "Computer Science", "strgCopy: 'Computer Science'");
    
    // Test 2: Copy with dashes
    strgCopy("CSE-220", dest, 50);
    assert_string_equal(dest, "CSE-220", "strgCopy: 'CSE-220'");
    
    // Test 3: Copy with truncation
    strgCopy("Computer Science", dest, 5);
    assert_string_equal(dest, "Comp", "strgCopy: truncate to 'Comp'");
    
    // Test 4: Single character
    strgCopy("1", dest, 50);
    assert_string_equal(dest, "1", "strgCopy: '1'");
    
    // Test 5: Empty string
    strgCopy("", dest, 50);
    assert_string_equal(dest, "", "strgCopy: empty string");
    
    // Test 6: NULL source (should not change dest)
    strgCopy("test", dest, 50);
    strgCopy(NULL, dest, 50);
    assert_string_equal(dest, "test", "strgCopy: NULL source (unchanged)");
    
    // Test 7: Size = 1 (only null terminator)
    strgCopy("Hello", dest, 1);
    assert_string_equal(dest, "", "strgCopy: size=1 (null only)");
    
    // Test 8: Exact fit
    strgCopy("Hello", dest, 6);
    assert_string_equal(dest, "Hello", "strgCopy: exact fit 'Hello'");
    
    // Test 9: copy with spaces
    strgCopy("Hello World", dest, 50);
    assert_string_equal(dest, "Hello World", "strgCopy: 'Hello World'");
    
    // Test 10: Long string truncation
    strgCopy("The quick brown fox", dest, 8);
    assert_string_equal(dest, "The qui", "strgCopy: truncate long string");
}


// strgChangeCase TESTS

void test_strgChangeCase() {
    printf("\n=== Testing strgChangeCase (10 cases) ===\n");
    
    char s[50];
    
    // Test 1: Normal case change
    sprintf(s, "Stony Brook");
    strgChangeCase(s);
    assert_string_equal(s, "sTONY bROOK", "strgChangeCase: 'Stony Brook'");
    
    // Test 2: With digits (digit-adjacent letters should not change)
    sprintf(s, "CSE220");
    strgChangeCase(s);
    assert_string_equal(s, "csE220", "strgChangeCase: 'CSE220'");
    
    // Test 3: Digit-adjacent letters (should not change)
    sprintf(s, "a1b");
    strgChangeCase(s);
    assert_string_equal(s, "a1b", "strgChangeCase: 'a1b' (no change)");
    
    // Test 4: Complex case
    sprintf(s, "System Fundamental220");
    strgChangeCase(s);
    assert_string_equal(s, "sYSTEM fUNDAMENTAl220", "strgChangeCase: complex");
    
    // Test 5: Single digit
    sprintf(s, "1");
    strgChangeCase(s);
    assert_string_equal(s, "1", "strgChangeCase: '1'");
    
    // Test 6: Empty string
    s[0] = '\0';
    strgChangeCase(s);
    assert_string_equal(s, "", "strgChangeCase: empty");
    
    // Test 7: All uppercase
    sprintf(s, "HELLO");
    strgChangeCase(s);
    assert_string_equal(s, "hello", "strgChangeCase: 'HELLO' to 'hello'");
    
    // Test 8: All lowercase
    sprintf(s, "hello");
    strgChangeCase(s);
    assert_string_equal(s, "HELLO", "strgChangeCase: 'hello' to 'HELLO'");
    
    // Test 9: With punctuation
    sprintf(s, "Hello, World!");
    strgChangeCase(s);
    assert_string_equal(s, "hELLO, wORLD!", "strgChangeCase: 'Hello, World!'");
    
    // Test 10: First letter adjacent to digit
    sprintf(s, "1a2");
    strgChangeCase(s);
    assert_string_equal(s, "1a2", "strgChangeCase: '1a2' (no change)");
}

// strgDiff TESTS

void test_strgDiff() {
    printf("\n=== Testing strgDiff (10 cases) ===\n");
    
    assert_int_equal(strgDiff("Hello", "Hello"), -1, "strgDiff: identical 'Hello'");
    assert_int_equal(strgDiff("CSE-220", "CSE220"), 3, "strgDiff: differ at index 3");
    assert_int_equal(strgDiff("CSE220", "SE220"), 0, "strgDiff: differ at index 0");
    assert_int_equal(strgDiff("", ""), -1, "strgDiff: both empty");
    assert_int_equal(strgDiff("abc", "abcd"), 3, "strgDiff: different lengths");
    assert_int_equal(strgDiff(NULL, "test"), -2, "strgDiff: NULL first param");
    assert_int_equal(strgDiff("test", NULL), -2, "strgDiff: NULL second param");
    assert_int_equal(strgDiff("", "test"), 0, "strgDiff: empty vs non-empty");
    assert_int_equal(strgDiff("test", "test"), -1, "strgDiff: identical 'test'");
    assert_int_equal(strgDiff("a", "b"), 0, "strgDiff: single char differ");
}


// strgInterleave TESTS

void test_strgInterleave() {
    printf("\n=== Testing strgInterleave (10 cases) ===\n");
    
    char d[100];
    
    // Test 1: Basic interleave
    strgInterleave("abc", "123", d, 100);
    assert_string_equal(d, "a1b2c3", "strgInterleave: 'abc' + '123'");
    
    // Test 2: Unequal lengths (first longer)
    strgInterleave("abcdef", "123", d, 100);
    assert_string_equal(d, "a1b2c3def", "strgInterleave: 'abcdef' + '123'");
    
    // Test 3: Second longer
    strgInterleave("cse", "12345", d, 100);
    assert_string_equal(d, "c1s2e345", "strgInterleave: 'cse' + '12345'");
    
    // Test 4: First longer
    strgInterleave("1234", "cs", d, 100);
    assert_string_equal(d, "1c2s34", "strgInterleave: '1234' + 'cs'");
    
    // Test 5: Both empty
    strgInterleave("", "", d, 100);
    assert_string_equal(d, "", "strgInterleave: both empty");
    
    // Test 6: First empty
    strgInterleave("", "123", d, 100);
    assert_string_equal(d, "123", "strgInterleave: empty + '123'");
    
    // Test 7: Buffer limit
    strgInterleave("abc", "123", d, 5);
    assert_string_equal(d, "a1b2", "strgInterleave: buffer truncate");
    
    // Test 8: Single characters
    strgInterleave("a", "1", d, 100);
    assert_string_equal(d, "a1", "strgInterleave: 'a' + '1'");
    
    // Test 9: Longer strings
    strgInterleave("hello", "world", d, 100);
    assert_string_equal(d, "hweolrllod", "strgInterleave: 'hello' + 'world'");
    
    // Test 10: Second empty
    strgInterleave("abc", "", d, 100);
    assert_string_equal(d, "abc", "strgInterleave: 'abc' + empty");
}


// strgReverseLetters TESTS

void test_strgReverseLetters() {
    printf("\n=== Testing strgReverseLetters (10 cases) ===\n");
    
    char s[100];
    
    // Test 1: Basic reverse
    sprintf(s, "Hello");
    strgReverseLetters(s);
    assert_string_equal(s, "olleH", "strgReverseLetters: 'Hello'");
    
    // Test 2: With dash
    sprintf(s, "ab-cd");
    strgReverseLetters(s);
    assert_string_equal(s, "dc-ba", "strgReverseLetters: 'ab-cd'");
    
    // Test 3: With digits
    sprintf(s, "a1b2c");
    strgReverseLetters(s);
    assert_string_equal(s, "c1b2a", "strgReverseLetters: 'a1b2c'");
    
    // Test 4: Empty
    s[0] = '\0';
    strgReverseLetters(s);
    assert_string_equal(s, "", "strgReverseLetters: empty");
    
    // Test 5: Single letter
    sprintf(s, "a");
    strgReverseLetters(s);
    assert_string_equal(s, "a", "strgReverseLetters: 'a'");
    
    // Test 6: No letters
    sprintf(s, "123");
    strgReverseLetters(s);
    assert_string_equal(s, "123", "strgReverseLetters: '123'");
    
    // Test 7: With spaces
    sprintf(s, "a b c");
    strgReverseLetters(s);
    assert_string_equal(s, "c b a", "strgReverseLetters: 'a b c'");
    
    // Test 8: Mixed case
    sprintf(s, "AaBbCc");
    strgReverseLetters(s);
    assert_string_equal(s, "cCbBaA", "strgReverseLetters: 'AaBbCc'");
    
    // Test 9: With punctuation
    sprintf(s, "a,b.c");
    strgReverseLetters(s);
    assert_string_equal(s, "c,b.a", "strgReverseLetters: 'a,b.c'");
    
    // Test 10: Complex string
    sprintf(s, "Hello123World");
    strgReverseLetters(s);
    assert_string_equal(s, "dlroW123olleH", "strgReverseLetters: 'Hello123World'");
}

// ============================================================================
// encryptCaesar TESTS
// ============================================================================
void test_encryptCaesar() {
    printf("\n=== Testing encryptCaesar (10 cases) ===\n");
    
    char ciphertext[200];
    
    // Test 1: Basic encryption (key=2)
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    int result = encryptCaesar("abc", ciphertext, 2);
    assert_int_equal(result, 3, "encryptCaesar: 'abc' key=2 returns 3");
    assert_string_equal(ciphertext, "ceg__EOM__", "encryptCaesar: 'abc' key=2 = 'ceg__EOM__'");
    
    // Test 2: Mixed case (key=3)
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("Ayb", ciphertext, 3);
    assert_int_equal(result, 3, "encryptCaesar: 'Ayb' key=3 returns 3");
    assert_string_equal(ciphertext, "Dcg__EOM__", "encryptCaesar: 'Ayb' key=3 = 'Dcg__EOM__'");
    
    // Test 3: With digits (key=1)
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("Cse220", ciphertext, 1);
    assert_int_equal(result, 6, "encryptCaesar: 'Cse220' key=1 returns 6");
    
    // Test 4: Key=0
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("CS", ciphertext, 0);
    assert_int_equal(result, 2, "encryptCaesar: 'CS' key=0 returns 2");
    assert_string_equal(ciphertext, "CT__EOM__", "encryptCaesar: 'CS' key=0 = 'CT__EOM__'");
    
    // Test 5: Empty string
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("", ciphertext, 0);
    assert_int_equal(result, 0, "encryptCaesar: empty string returns 0");
    assert_string_equal(ciphertext, "__EOM__", "encryptCaesar: empty = '__EOM__'");
    
    // Test 6: NULL plaintext
    result = encryptCaesar(NULL, ciphertext, 2);
    assert_int_equal(result, -2, "encryptCaesar: NULL plaintext returns -2");
    
    // Test 7: NULL ciphertext
    result = encryptCaesar("abc", NULL, 2);
    assert_int_equal(result, -2, "encryptCaesar: NULL ciphertext returns -2");
    
    // Test 8: Insufficient space
    sprintf(ciphertext, "%s", "test");
    result = encryptCaesar("abc", ciphertext, 2);
    assert_int_equal(result, -1, "encryptCaesar: insufficient space returns -1");
    
    // Test 9: With spaces
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("a b", ciphertext, 1);
    assert_int_equal(result, 2, "encryptCaesar: 'a b' key=1 returns 2");
    
    // Test 10: Large key (wraps around)
    sprintf(ciphertext, "%s", "                                                                                                                                                                                                  ");
    result = encryptCaesar("abc", ciphertext, 26);
    assert_int_equal(result, 3, "encryptCaesar: 'abc' key=26 returns 3");
    assert_string_equal(ciphertext, "ace__EOM__", "encryptCaesar: 'abc' key=26 = 'ace__EOM__'");
}

// ============================================================================
// decryptCaesar TESTS
// ============================================================================
void test_decryptCaesar() {
    printf("\n=== Testing decryptCaesar (10 cases) ===\n");
    
    char plaintext[200];
    
    // Test 1: Basic decryption
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    int result = decryptCaesar("ceg__EOM__", plaintext, 2);
    assert_int_equal(result, 3, "decryptCaesar: 'ceg__EOM__' key=2 returns 3");
    assert_string_equal(plaintext, "abc", "decryptCaesar: 'ceg__EOM__' key=2 = 'abc'");
    
    // Test 2: Mixed case
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("Dcg__EOM__", plaintext, 3);
    assert_int_equal(result, 3, "decryptCaesar: 'Dcg__EOM__' key=3 returns 3");
    assert_string_equal(plaintext, "Ayb", "decryptCaesar: 'Dcg__EOM__' key=3 = 'Ayb'");
    
    // Test 3: With digits
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("Duh911__EOM__", plaintext, 1);
    assert_int_equal(result, 6, "decryptCaesar: 'Duh911__EOM__' key=1 returns 6");
    assert_string_equal(plaintext, "Cse220", "decryptCaesar: 'Duh911__EOM__' key=1 = 'Cse220'");
    
    // Test 4: Key=0
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("CT__EOM__", plaintext, 0);
    assert_int_equal(result, 2, "decryptCaesar: 'CT__EOM__' key=0 returns 2");
    assert_string_equal(plaintext, "CS", "decryptCaesar: 'CT__EOM__' key=0 = 'CS'");
    
    // Test 5: Only EOM marker
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("__EOM__", plaintext, 0);
    assert_int_equal(result, 0, "decryptCaesar: '__EOM__' only returns 0");
    
    // Test 6: NULL ciphertext
    result = decryptCaesar(NULL, plaintext, 2);
    assert_int_equal(result, -2, "decryptCaesar: NULL ciphertext returns -2");
    
    // Test 7: NULL plaintext
    result = decryptCaesar("ceg__EOM__", NULL, 2);
    assert_int_equal(result, -2, "decryptCaesar: NULL plaintext returns -2");
    
    // Test 8: Missing EOM marker
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("abc", plaintext, 2);
    assert_int_equal(result, -1, "decryptCaesar: missing EOM returns -1");
    
    // Test 9: Zero length plaintext
    plaintext[0] = '\0';
    result = decryptCaesar("ceg__EOM__", plaintext, 2);
    assert_int_equal(result, 0, "decryptCaesar: zero length plaintext returns 0");
    
    // Test 10: Large key
    sprintf(plaintext, "%s", "                                                                                                                                                                                                  ");
    result = decryptCaesar("ace__EOM__", plaintext, 26);
    assert_int_equal(result, 3, "decryptCaesar: 'ace__EOM__' key=26 returns 3");
    assert_string_equal(plaintext, "abc", "decryptCaesar: 'ace__EOM__' key=26 = 'abc'");
}


// MAIN TEST RUNNER.Here wecall at the test functions.

int main() {
    printf("Starting tests for Homework 4...\n");
    
    test_strgLen();
    test_strgCopy();
    test_strgChangeCase();
    test_strgDiff();
    test_strgInterleave();
    test_strgReverseLetters();
    test_encryptCaesar();
    test_decryptCaesar();
    
    printf("\nTest summary:\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    
    return tests_failed > 0 ? 1 : 0;
}
//this file includes the test cases for all the functions.
