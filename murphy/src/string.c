#include <stddef.h> // size_t
#include <string.h>


// =================================================================================================
// memXX implementations
// =================================================================================================

void *memchr(const void *ptr, int value, size_t num) {

    const unsigned char *cptr = (const unsigned char *)ptr;
    unsigned char cval = (unsigned char)(value & 0xff); // We need to only consider value as a byte.

    for (size_t i = 0; i < num; i++, cptr++) {
        if (*cptr == cval)
            return (void *)cptr; // Get rid of the 'const' specifier.
    }

    return NULL;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {

    // We consider the pointers as a list of bytes.
    const unsigned char *cptr1 = (const unsigned char *)ptr1;
    const unsigned char *cptr2 = (const unsigned char *)ptr2;

    for (size_t i = 0; i < num; i++, cptr1++, cptr2++) {

        if (*cptr1 < *cptr2)
            return -1;
        else if (*cptr1 > *cptr2)
            return 1;
    }

    return 0;
}

void *memcpy(void *destination, const void *source, size_t num) {

    unsigned char *cdest = (unsigned char *)destination;
    const unsigned char *csrc = (const unsigned char *)source;

    // Just loop over the source, putting each byte into destination's place.
    for (size_t i = 0; i < num; i++, cdest++, csrc++)
        *cdest = *csrc;

    return destination;
}

void *memmove(void *destination, const void *source, size_t num) {

    // (note that we do nothing if destination == source).
    if (destination < source) {

        // If the destination is lower in memory than the source, we go over the
        // source in ascending order.
        unsigned char *cdest = (unsigned char *)destination;
        const unsigned char *csrc = (const unsigned char *)source;

        for (size_t i = 0; i < num; i++, cdest++, csrc++)
            *cdest = *csrc;
    }
    else if (destination > source) {

        // If the destination is higher in memory than the source, we go over the
        // source in descending order.
        unsigned char *cdest = (unsigned char *)(destination + num - 1);
        const unsigned char *csrc = (const unsigned char *)(source + num - 1);

        for (size_t i = num; i > 0; i--, cdest--, csrc--)
            *cdest = *csrc;
    }

    return destination;
}

void *memset(void *ptr, int value, size_t num) {

    unsigned char *cptr = (unsigned char *)ptr;
    unsigned char cvalue = (unsigned char)(value & 0xff); // We need to only consider value as a byte.

    for (size_t i = 0; i < num; i++, cptr++)
        *cptr = cvalue;

    return ptr;
}


// =================================================================================================
// strXX implementations
// =================================================================================================

size_t strlen(const char *str) {

    size_t len = 0;
    for (; str[len] != '\0'; len++);

    return len;
}

char *strcat(char *destination, const char *source) {
    return strncat(destination, source, strlen(source));
}

char *strncat(char *destination, const char *source, size_t num) {

    char *put = destination + strlen(destination); // 'put' points to the terminating 0 of 'destination'.

    // Until we see the terminating 0 of the source or we have copied 'num' bytes, we copy the current byte
    // of the source into the current byte of the destination.
    for (; *source != '\0' && num > 0; put++, source++, num--)
        *put = *source;

    // We add the terminating zero of the whole string.
    *(put + 1) = '\0';

    return destination;
}

char *strchr(const char *str, int character) {

    size_t num = strlen(str) + 1; // +1 to include the null terminator.
    return (char *)memchr((const void *)str, character, num);
}

int strcmp(const char *str1, const char *str2) {
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 < len2)
        return -1; // If str1 is shorter than str2, then it follow that str2 is bigger.
    else if (len1 > len2)
        return 1; // Same as above, except inverted.

    // The two strings are of the same length (len1 == len2).
    return memcmp((const void *)str1, (const void *)str2, len1);
}

int strncmp(const char *str1, const char *str2, size_t num) {

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    // If str1 is shorter than str2, AND the number of bytes that needs to be compared
    // is more than the total length of the biggest string, then it follow that str2 is bigger.
    if (len1 < len2 && len2 < num)
        return -1;
    // Same as above, except inverted.
    else if (len2 < len1 && len1 < num)
        return 1;

    // At least one of the string has a length which is bigger or equal to num.
    return memcmp((const void *)str1, (const void *)str2, num);
}

char *strcpy(char *destination, const char *source) {
    
    size_t num = strlen(source) + 1; // +1 to include the null terminator.
    return strncpy(destination, source, num);
}

char *strncpy(char *destination, const char *source, size_t num) {
    return (char *)memcpy((void *)destination, (const void *)source, num);
}

size_t strcspn(const char *str1, const char *str2) {

    size_t num1 = strlen(str1) + 1; // +1 to include the null terminator.

    for (size_t i = 0; i < num1; i++) {

        // Check if one of the characters inside str2 is equal to the current character of str1.
        int current = (int)str1[i];
        if (strchr(str2, current) != NULL) // If 'current' was found in str2.
            return i;
    }

    // Since str1 and str2 are C-strings (null terminated), this should be dead code.
    return num1;
}
