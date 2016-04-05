#ifndef __kernel_vga_h
#define __kernel_vga_h

#include <stddef.h> // size_t
#include <stdint.h> // uint16_t
#include <types.h>  // vga_entry_t, vga_attrib_t

// The size in entries of the VGA buffer. That makes the VGA text memory 80*25=2000 entries long.
// 2000 entries of 2 bytes each = 4000 bytes.
static const size_t VGA_SCREEN_WIDTH = 80;
static const size_t VGA_SCREEN_HEIGHT = 25;

// A pointer to the start of the VGA text memory.
static vga_entry_t *const VGA_TEXT_MEMORY = (vga_entry_t *)0xb8000;

// VGA can represent 16 different colors, which are enumerated here.
enum vga_color {
    VGA_COLOR_BLACK         = 0x0,
    VGA_COLOR_BLUE          = 0x1,
    VGA_COLOR_GREEN         = 0x2,
    VGA_COLOR_CYAN          = 0x3,
    VGA_COLOR_RED           = 0x4,
    VGA_COLOR_MAGENTA       = 0x5,
    VGA_COLOR_BROWN         = 0x6,
    VGA_COLOR_LIGHT_GREY    = 0x7,
    VGA_COLOR_DARK_GREY     = 0x8,
    VGA_COLOR_LIGHT_BLUE    = 0x9,
    VGA_COLOR_LIGHT_GREEN   = 0xa,
    VGA_COLOR_LIGHT_CYAN    = 0xb,
    VGA_COLOR_LIGHT_RED     = 0xc,
    VGA_COLOR_LIGHT_MAGENTA = 0xd,
    VGA_COLOR_LIGHT_BROWN   = 0xe,
    VGA_COLOR_WHITE	        = 0xf
};

/* Creates a VGA attribute (letter color + background color).
 * It takes a 'foreground' color from the vga_color enum and a 'background' color, still
 * from the vga_color enum.
 */
static inline vga_attrib_t make_vga_attrib(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

/* Creates a VGA entry from a character and its attribute. A VGA entry is organized as:
 * |<-8bits: attributes->||<-8bits: character->|
 */
static inline vga_entry_t make_vga_entry(char c, vga_attrib_t attrib) {

    uint16_t c16 = c;
    uint16_t attrib16 = attrib;
    return c16 | attrib16 << 8;
}

#endif // __kernel_vga_h
