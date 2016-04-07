#include <stddef.h>
#include <string.h>

#include <kprint.h>
#include <tty.h>

static const char *hex_digits = "0123456789abcdef";

static inline void kwrite_char(char c) {
    kterm_write(&c, sizeof c);
}

void kprint(const char *str) {
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
        kwrite_char(str[i]);
}

void kprint_hexu(unsigned int num) {

    // First print the '0x'.
    kwrite_char('0');
    kwrite_char('x');

    // Then transform the number that is in base 10 into hex. This is easy if we consider
    // the binary representation of the number in memory. We make groups of 4 bits that we
    // assign to a hex digit. There's sizeof (int) * 2 of these groups.
    unsigned int groups = sizeof (int) * 2;

    for (size_t curr_group = groups; curr_group > 0; curr_group--) {

        // We go from most significant group to least significant (printing from left to right).
        unsigned int group_value = num >> ((curr_group - 1) << 2) & 0xf;
        char digit = hex_digits[group_value];

        kwrite_char(digit);
    }
}

void kprint_hexi(int num) {

    if (num < 0) kwrite_char('-');
    kwrite_char('0');
    kwrite_char('x');

    // Then transform the number that is in base 10 into hex. This is easy if we consider
    // the binary representation of the number in memory. We make groups of 4 bits that we
    // assign to a hex digit. There's sizeof (int) * 2 of these groups.
    unsigned int groups = sizeof (int) * 2;

    // For the first group, we only take the first 3 bits of the 4 bits as the first one is
    // the sign bit.
    unsigned int first_group_value = num >> ((groups - 1) << 2) & 0x7;
    char first_digit = hex_digits[first_group_value];
    kwrite_char(first_digit);

    // We start with the second group.
    for (size_t curr_group = groups - 1; curr_group > 0; curr_group--) {

        // We go from most significant group to least significant (printing from left to right).
        unsigned int group_value = num >> ((curr_group - 1) << 2) & 0xf;
        char digit = hex_digits[group_value];

        kwrite_char(digit);
    }
}
