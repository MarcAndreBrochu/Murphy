#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#include <kprintf.h>
#include <tty.h>
#include <string.h>

static void kprint(const char *data, size_t data_length) {

    for (size_t i = 0; i < data_length; i++)
        kputchar((int)((const unsigned char *)data)[i]);
}

int kprintf(const char *restrict format, ...) {

    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while (*format != '\0') {

        if (*format != '%') {

            print_c:
                amount = 1;
                while (format[amount] && format[amount] != '%')
                    amount++;
                kprint(format, amount);
                format += amount;
                written += amount;
                continue;
        }

        const char *format_begun_at = format;

        if (*(++format) == '%')
            goto print_c;

        if (rejected_bad_specifier) {

            incomprehensible_conversion:
                rejected_bad_specifier = true;
                format = format_begun_at;
                goto print_c;
        }

        if (*format == 'c') {
            format++;
            char c = (char)va_arg(parameters, int);
            kprint(&c, sizeof c);
        }
        else if (*format == 's') {
            format++;
            const char *s = va_arg(parameters, const char *);
            kprint(s, strlen(s));
        }
        else {
            goto incomprehensible_conversion;
        }
    }

    va_end(parameters);

    return written;
}

int kputchar(int ic) {

    char c = (char)ic;
    kterm_write(&c, sizeof c);
    
    return ic;
}

int kputs(const char *string) {
    return kprintf("%s\n", string);
}
