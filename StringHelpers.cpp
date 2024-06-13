#include "StringHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Splits a string by a delimiter and returns an array of tokens
char** SplitString(const char* line, char delimiter) {
    int tokenCount = 0;
    const char* position = line;
    while (*position != '\0') {
        if (*position++ == delimiter) {
            tokenCount++;
        }
    }

    char** tokens = (char**)malloc(sizeof(char*) * (tokenCount + 2));
    int tokenIndex = 0;
    position = line;
    char* token = (char*)malloc(strlen(line) + 1);
    int charIndex = 0;
    while (*position != '\0') {
        if (*position == delimiter) {
            token[charIndex] = '\0';
            tokens[tokenIndex++] = strdup(token);
            charIndex = 0;
        } else {
            token[charIndex++] = *position;
        }
        position++;
    }
    token[charIndex] = '\0';
    tokens[tokenIndex++] = strdup(token);
    tokens[tokenIndex] = NULL;
    free(token);
    return tokens;
}

// Converts a string to an integer and returns success or failure
int intGetFromString(const char* str, int* value) {
    char* endptr;
    *value = strtol(str, &endptr, 10);
    if (endptr == str) {
        return 0;
    }
    return 1;
}

// Converts a string to a double and returns success or failure
int toDouble(const char* str, double* value) {
    char* endptr;
    *value = strtod(str, &endptr);
    if (endptr == str) {
        return 0;
    }
    return 1;
}
