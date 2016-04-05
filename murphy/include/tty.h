#ifndef __kernel_tty_h
#define __kernel_tty_h

#include <stddef.h> // for size_t

/* Initializes the kernel's terminal, putting the cursor at (0,0), choosing a default
 * foreground/background combo for the VGA attribute, pointing to the text memory, etc.
 * Must be called before anything is done with the terminal.
 */
void kterm_initialize();

/* Clears the screen of the terminal. Note that it does not change the emplacement of
 * the cursor.
 */
void kterm_clear_screen();

/* Acts as if the lines on the screen scolled up one line. The line that goes offscreen
 * at the top of the terminal is lost.
 */
void kterm_scroll();

/* Changes the position of the cursor on the screen at a specified row and column.
 */
void kterm_move_cursor(size_t row, size_t col);

/* Prints a character on the terminal in a serial way, meaning that the imprinted character
 * follows the one that went before it. This may trigger a newline or a scroll up.
 */
void kterm_putchar(char c);

/* Writes data of a specified length to the screen. The following function, write_string,
 * does the same thing but calculates the length of a null-terminated string itself.
 */
void kterm_write(const char *data, size_t size);
void kterm_write_string(const char *data);

#endif // __kernel_tty_h
