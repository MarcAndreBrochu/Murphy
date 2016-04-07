#include <stddef.h>
#include <string.h>

#include <kprint.h>
#include <tty.h>

static void kwrite_string(const char *str) {

    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        kterm_write(&c, sizeof c);
    }
}

void kprint(const char *str) {
    kwrite_string(str);
}
