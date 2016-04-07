#include <tty.h>
#include <kprint.h>

#define WAIT_FOREVER() while (1) {}

void kmain() {

    kterm_initialize();
    kprint("Hello from kernel! :)\n");

    // Put the kernel in idle (since kmain should not return)
    WAIT_FOREVER();
}
