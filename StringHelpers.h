#ifndef STRING_HELPERS_H_
#define STRING_HELPERS_H_

// Splits a string by a delimiter and returns an array of tokens
char** SplitString(const char* line, char delimiter);

// Converts a string to an integer and returns success or failure
int intGetFromString(const char* str, int* value);

// Converts a string to a double and returns success or failure
int toDouble(const char* str, double* value);


#endif
