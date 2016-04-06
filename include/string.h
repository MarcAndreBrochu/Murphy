#ifndef __string_h
#define __string_h

#include <stddef.h> // size_t

/* -- Locate character in block of memory. --
 * Searches within the first num bytes of the block of memory pointed by ptr for the first
 * occurrence of value (interpreted as an unsigned char), and returns a pointer to it.
 * If the value is not found, the function returns a null pointer.
 *
 * Both value and each of the bytes checked on the the ptr array are interpreted as unsigned
 * char for the comparison.
 */
void *memchr(const void *ptr, int value, size_t num);

/* -- Compare two blocks of memory. --
 * Compares the first num bytes of the block of memory pointed by ptr1 to the first num bytes
 * pointed by ptr2, returning zero if they all match or...
 *   A value < 0 if ptr1 < ptr2;
 *   A value > 0 if ptr1 > ptr2.
 */
int memcmp(const void *ptr1, const void *ptr2, size_t num);

/* -- Copy block of memory. --
 * Copies the values of num bytes from the location pointed to by source directly to the
 * memory block pointed to by destination. To avoid overflows, the size of the arrays pointed
 * to by both the destination and source parameters, shall be at least num bytes, and should
 * NOT overlap (for overlapping memory blocks, memmove is a safer approach).
 *
 * 'destination' is returned.
 */
void *memcpy(void *destination, const void *source, size_t num);

/* -- Move block of memory. --
 * Copies the values of num bytes from the location pointed by source to the memory block
 * pointed by destination. Copying takes place as if an intermediate buffer were used,
 * allowing the destination and source to overlap.
 *
 * 'destination' is returned.
 */
void *memmove(void *destination, const void *source, size_t num);

 /* -- Fill block of memory. --
  * Sets the first num bytes of the block of memory pointed by ptr to the specified value
  * (interpreted as an unsigned char).
  *
  * 'ptr' is returned.
  */
void *memset(void *ptr, int value, size_t num);

/* -- Get string length. --
 * Returns the length of the C string str. The length of a C string is determined by the
 * terminating null-character: A C string is as long as the number of characters between
 * the beginning of the string and the terminating null character (without including the
 * terminating null character itself).
 */
size_t strlen(const char *str);

/* -- Concatenate strings. --
 * Appends a copy of the source string to the destination string. The terminating null character
 * in destination is overwritten by the first character of source, and a null-character is
 * included at the end of the new string formed by the concatenation of both in destination.
 *
 * 'destination' and 'source' shall not overlap.
 */
char *strcat(char *destination, const char *source);

/* -- Append characters from string. --
 * Appends the first num characters of source to destination, plus a terminating null-character.
 * If the length of the C string in source is less than num, only the content up to the terminating
 * null-character is copied.
 *
 * 'destination' is returned.
 */
char *strncat(char *destination, const char *source, size_t num);

/* -- Locate first occurrence of character in string. --
 * Returns a pointer to the first occurrence of character in the C string str. The terminating
 * null-character is considered part of the C string. Therefore, it can also be located in
 * order to retrieve a pointer to the end of a string.
 *
 * If the character is not found, the function returns a null pointer.
 */
char *strchr(const char *str, int character);

/* -- Compare two strings. --
 * Compares the C string str1 to the C string str2. This function starts comparing the first
 * character of each string. If they are equal to each other, it continues with the following
 * pairs until the characters differ or until a terminating null-character is reached.
 *
 * It returns zero if all of the characters match or...
 *   A value < 0 if str1 < str2;
 *   A value > 0 if str1 > str2.
 */
int strcmp(const char *str1, const char *str2);

/* -- Compare characters of two strings. --
 * Compares up to num characters of the C string str1 to those of the C string str2. This
 * function starts comparing the first character of each string. If they are equal to each
 * other, it continues with the following pairs until the characters differ, until a termi-
 * nating null-character is reached, or until num characters match in both strings, whichever
 * happens first.
 *
 * It returns zero if all of the characters match or...
 *   A value < 0 if str1 < str2;
 *   A value > 0 if str1 > str2.
 */
int strncmp(const char *str1, const char *str2, size_t num);

/* -- Copy string. --
 * Copies the C string pointed by source into the array pointed by destination, including the
 * terminating null character (and stopping at that point).
 */
char *strcpy(char *destination, const char *source);

/* -- Copy characters from string. --
 * Copies the first num characters of source to destination. If the end of the source C string
 * (which is signaled by a null-character) is found before num characters have been copied, destination
 * is padded with zeros until a total of num characters have been written to it. No null-character is
 * implicitly appended at the end of destination if source is longer than num. Thus, in this case,
 * destination shall not be considered a null terminated C string (reading it as such would overflow).
 *
 * 'destination' is returned.
 */
char *strncpy(char *destination, const char *source, size_t num);

/* -- Get span until character in string. --
 * Scans str1 for the first occurrence of any of the characters that are part of str2, returning
 * the number of characters of str1 read before this first occurrence. The search includes the
 * terminating null-characters. Therefore, the function will return the length of str1 if none
 * of the characters of str2 are found in str1.
 */
size_t strcspn(const char *str1, const char *str2);

#endif // __string_h
