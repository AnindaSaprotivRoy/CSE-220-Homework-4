#ifndef STRGPTR_H
#define STRGPTR_H
#include <stddef.h>

int  strgLen(const char *s);
void strgCopy(const char *source, char *destination, size_t size);
void strgChangeCase(char *s);
int  strgDiff(const char *s1, const char *s2);
void strgInterleave(const char *s1, const char *s2, char *d, size_t size);
void strgReverseLetters(char *s);

#endif
