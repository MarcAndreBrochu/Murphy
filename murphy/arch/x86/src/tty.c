#include <stddef.h> // size_t
#include <stdint.h> // uint8_t, uint16_t

#include <types.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/io.h>

size_t cursor_x, cursor_y; // The x and y pos of the cursor
uint8_t text_attrib;       // The background and foreground of a character
uint16_t *text_buffer;     // A 25*80 zone in memory that contains the VGA text

/* Sets the attribute to a new value.
 * This is a local (static) function that acts as an helper.
 */
static void kterm_set_attrib(vga_attrib_t attrib) {
    text_attrib = attrib;
}

/* Puts into the VGA text memory an entry.
 * This is a local (static) function that acts as an helper.
 */
static void kterm_put_entry_at(char c, vga_attrib_t attrib, size_t x, size_t y) {
    const size_t index = y * VGA_SCREEN_WIDTH + x;
    text_buffer[index] = make_vga_entry(c, attrib);
}

void kterm_initialize() {

    cursor_x = 0;
    cursor_y = 0;
    text_attrib = make_attrib(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    text_buffer = VGA_TEXT_MEMORY;

    kterm_clear_screen();
}

void kterm_clear_screen() {

    uint16_t blank = make_vgaentry(' ', text_attrib);

    for (size_t y = 0; y < VGA_SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_SCREEN_WIDTH; x++) {

            const size_t index = y * VGA_SCREEN_WIDTH + x;
            text_buffer[index] = blank;
        }
    }
}

void kterm_scroll() {

    uint16_t blank = make_vgaentry(' ', text_attrib);

    // Move the chunk of memory at VGA_MEMORY one line up.
    for (size_t y = 1; y <= VGA_SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_SCREEN_WIDTH; x++) {

            const size_t index = y * VGA_SCREEN_WIDTH + x;
            text_buffer[index - VGA_SCREEN_WIDTH] = text_buffer[index];
        }
    }
    
    // Then set the last line of the buffer to 'blank'.
    for (size_t x = 0; x < VGA_SCREEN_WIDTH; x++) {

        const size_t y = VGA_SCREEN_HEIGHT;
        const size_t index = y * VGA_SCREEN_WIDTH + x;

        text_buffer[index] = blank;
    }
}

void kterm_move_cursor(size_t row, size_t col) {

    uint16_t pos = row * VGA_SCREEN_WIDTH + col;

    outb(0x3d4, 0x0e);
    outb(0x3d5, (pos >> 8) & 0x00FF);
    outb(0x3d4, 0x0f);
    outb(0x3d5, pos & 0x00FF);
}

void kterm_putchar(char c) {

    switch (c) {

        case '\b':
        if (cursor_x != 0)
            cursor_x--;
        break;

        case '\n':
        cursor_x = 0;
        cursor_y++;
        break;

        case '\r':
        cursor_x = 0;
        break;

        case '\t':
        cursor_x = (cursor_x + 4) & ~(4 - 1);
        break;

        default:
        // Any character greater than a space is a printable character
        if (c >= ' ') {
            kterm_put_entry_at(c, text_attrib, cursor_x, cursor_y);
            cursor_x++;
        }
    }

    // Check if the cursor will get off the screen at the next entry.
    if (cursor_x == VGA_SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y == VGA_SCREEN_HEIGHT) {
        cursor_y = VGA_SCREEN_HEIGHT - 1;
        kterm_scroll();
    }

    kterm_move_cursor((uint16_t)(cursor_y * VGA_SCREEN_WIDTH + cursor_x));
}

void kterm_write(const char *data, size_t size) {

    for (size_t i = 0; i < size; i++)
        kterm_putchar(data[i]);
}

void kterm_write_string(const char *data) {
    kterm_write(data, strlen(data));
}
