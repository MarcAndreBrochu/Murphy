#include <tty.h>
#include <kprint.h>

#define WAIT_FOREVER() while (1) {}

void kmain() {

    kterm_initialize();
    kprint("Hello from kernel! :)\n");

    kprint_hexu(0x1);
    kprint("\n");
    kprint_hexu(0x10);
    kprint("\n");
    kprint_hexu(0xcafe);
    kprint("\n");
    kprint_hexu(0xcafebabe);
    kprint("\n");
    kprint_hexu(3735928559);
    kprint("\n");
    kprint_hexi(-70);
    kprint("\n");

    // Put the kernel in idle (since kmain should not return)
    WAIT_FOREVER();
}
