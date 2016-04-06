#include <kprintf.h>

#define WAIT_FOREVER() while (1) {}

void kmain() {

    kprintf("Hello from kernel! :)\n");

    // Put the kernel in idle (since kmain should not return)
    WAIT_FOREVER();
}
