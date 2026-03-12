#include "cse_caesar.h"
#include "strgPtr.h"

// Check whether a character is an English alphabet letter.
// We treat uppercase and lowercase separately for readability.
static int isLetter(char c) {
    int isUppercase = (c >= 'A' && c <= 'Z');
    int isLowercase = (c >= 'a' && c <= 'z');

    if (isUppercase || isLowercase) {
        return 1;
    }

    return 0;
}

// A method that checks whether a character is a digit from 0 to 9.
static int isDigit(char c) {
    int inDigitRange = (c >= '0' && c <= '9');

    if (inDigitRange) {
        return 1;
    }

    return 0;
}

// Keep modulo results non-negative (important when key is negative).
static int normalizeMod(int value, int mod) {
    int result = value % mod;
    if (result < 0) {
        result += mod;
    }
    return result;
}

// Getting the string length using this function
static int myStrLen(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    while (s[length] != '\0') {
        length+=1;
    }

    return length;
}

// Return 1 if "__EOM__" starts at ciphertext[index], otherwise 0.
static int hasEomAt(const char *ciphertext, int index) {
    static const char eom[] = "__EOM__";

    for (int offset = 0; offset < 7; offset++) {
        if (ciphertext[index + offset] == '\0' || ciphertext[index + offset] != eom[offset]) {
            return 0;
        }
    }

    return 1;
}

int encryptCaesar(const char *plaintext, char *ciphertext, int key) {
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }

    // Spec says capacity comes from the initial string length in ciphertext.
    int ciphertextCapacity = myStrLen(ciphertext);
    int encrypted_count = 0;
    int index = 0;     // Position-aware index used by the Caesar rules.
    int writePos = 0;  // Where we write into ciphertext.

    for (int readPos = 0; plaintext[readPos] != '\0'; readPos++) {
        char current = plaintext[readPos];
        char encoded;

        if (isLetter(current)) {
            int shift = normalizeMod(key + index, 26);

            if (current >= 'A' && current <= 'Z') {
                encoded = 'A' + (current - 'A' + shift) % 26;
            } else {
                encoded = 'a' + (current - 'a' + shift) % 26;
            }

            encrypted_count++;
        } else if (isDigit(current)) {
            int shift = normalizeMod(key + 2 * index, 10);
            encoded = '0' + (current - '0' + shift) % 10;
            encrypted_count++;
        } else {
            // Non-alphanumeric characters are copied as-is.
            encoded = current;
        }

        // Leave room for final null terminator.
        if (writePos >= ciphertextCapacity - 1) {
            return -1;
        }

        ciphertext[writePos] = encoded;
        writePos++;
        index++;
    }

    // Need enough room to append "__EOM__" (7 chars, no null yet).
    if (writePos + 7 > ciphertextCapacity) {
        return -1;
    }

    const char *eom = "__EOM__";
    for (int i = 0; i < 7; i++) {
        ciphertext[writePos] = eom[i];
        writePos++;
    }

    ciphertext[writePos] = '\0';
    return encrypted_count;
}

int decryptCaesar(const char *ciphertext, char *plaintext, int key) {
    if (ciphertext == NULL || plaintext == NULL) {
        return -2;
    }

    // Capacity is based on plaintext's initial length (per assignment spec).
    int plaintextCapacity = myStrLen(plaintext);
    if (plaintextCapacity == 0) {
        return 0;
    }

    int eom_pos = -1;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (hasEomAt(ciphertext, i)) {
            eom_pos = i;
            break;
        }
    }

    if (eom_pos == -1) {
        return -1;
    }

    int decrypted_count = 0;
    int index = 0;     // Position-aware index (same rule used in encryption).
    int writePos = 0;  // Where we write in plaintext.
    int maxPlainChars = plaintextCapacity - 1;

    for (int readPos = 0; readPos < eom_pos && writePos < maxPlainChars; readPos++) {
        char current = ciphertext[readPos];
        char decoded;

        if (isLetter(current)) {
            int shift = normalizeMod(key + index, 26);

            if (current >= 'A' && current <= 'Z') {
                decoded = 'A' + (current - 'A' - shift + 26) % 26;
            } else {
                decoded = 'a' + (current - 'a' - shift + 26) % 26;
            }
        } else if (isDigit(current)) {
            int shift = normalizeMod(key + 2 * index, 10);
            decoded = '0' + (current - '0' - shift + 10) % 10;
        } else {
            decoded = current;
        }

        plaintext[writePos] = decoded;
        writePos++;

        if (isLetter(current) || isDigit(current)) {
            decrypted_count++;
        }

        index++;
    }

    plaintext[writePos] = '\0';
    return decrypted_count;
}
