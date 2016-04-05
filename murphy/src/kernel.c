#define WAIT_FOREVER() while (1) {}

void kmain() {

    // Put the kernel in idle (since kmain should not return)
    WAIT_FOREVER();
}
