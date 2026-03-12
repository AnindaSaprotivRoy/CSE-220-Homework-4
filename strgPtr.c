#include "strgPtr.h"


// Helper function to check if a character is a letter
static int isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Helper function to check if a character is a digit
static int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int strgLen(const char *s) {
    if (s == NULL) {
        return -1;
    }
    int length = 0;
    while (*s != '\0') {
        length+=1;
        s++; 
    }
    return length;
}

void strgCopy(const char *source, char *destination, size_t size) {
    if (source == NULL || destination == NULL || size == 0) {
        return;
    }
    
    size_t i = 0;
    // Copy characters until we hit null terminator or reach size-1
    while (i < size - 1 && *(source+i) != '\0') {
        *(destination+i) = *(source+i);
        i++;
    }
    // Null-terminate the destination
    destination[i] = '\0';
}

void strgChangeCase(char *s) {
    if (s == NULL) {
        return;
    }
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (isLetter(s[i])) {
            // Check if adjacent to a digit
            int leftHasDigit = (i > 0) && isDigit(s[i - 1]);
            int rightHasDigit = (s[i + 1] != '\0') && isDigit(s[i + 1]);
            
            // Only change case if NOT adjacent to a digit
            if (!leftHasDigit && !rightHasDigit) {
                if (s[i] >= 'a' && s[i] <= 'z') {
                    s[i] = s[i] - 'a' + 'A';  // Convert to uppercase
                } else {
                    s[i] = s[i] - 'A' + 'a';  // Convert to lowercase
                }
            }
        }
    }
}

int strgDiff(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -2;
    }
    
    for (int i = 0; ; i++) {
        if (s1[i] != s2[i]) {
            return i;
        }
        // If both reached null terminator, they're equal
        if (s1[i] == '\0') {
            return -1;
        }
    }
}

void strgInterleave(const char *s1, const char *s2, char *b, size_t size) {
    if (s1 == NULL || s2 == NULL || b == NULL || size == 0) {
        return;
    }
    
    size_t i1 = 0, i2 = 0, di = 0;
    
    // Interleave characters from s1 and s2
    while (di < size - 1) {
        // Add character from s1
        if (s1[i1] != '\0') {
            b[di++] = s1[i1++];
        } else if (s2[i2] != '\0') {
            // s1 is done, copy remaining from s2
            b[di++] = s2[i2++];
        } else {
            // Both strings exhausted
            break;
        }
        
        // Add character from s2 if we see that s1 is not exhausted and we have room
        if (di < size - 1 && s1[i1] != '\0') {
            if (s2[i2] != '\0') {
                b[di++] = s2[i2++];
            } else {
                // s2 is done, continue copying from s1
                b[di++] = s1[i1++];
            }
        } else if (di < size - 1 && s2[i2] != '\0') {
            b[di++] = s2[i2++];
        }
    }
    
    b[di] = '\0';
}

void strgReverseLetters(char *s) {
    if (s == NULL) {
        return;
    }
    
    // Find out the letters and their position
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    
    // Find the indices of all letters
    int letterIndexes[len];
    char letterChars[len];
    int letterCount = 0;
    
    for (int i = 0; i < len; i++) {
        if (isLetter(s[i])) {
            letterIndexes[letterCount] = i;
            letterChars[letterCount] = s[i];
            letterCount+=1;
        }
    }
    
    // Reverse the letters and place them back to its original position
    for (int i = 0; i < letterCount; i++) {
        s[letterIndexes[i]] = letterChars[letterCount - 1 - i];
    }
}
