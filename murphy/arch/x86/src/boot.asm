; For loading with GRUB, we must respect the Multiboot Specification.
; (See: http://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
;
; Declare constants used for creating a Multiboot-compliant header.
; * If bit 0 in the ‘flags’ word is set, then all boot modules loaded along
;   with the operating system must be aligned on page (4KB) boundaries.
; * If bit 1 in the ‘flags’ word is set, then information on available memory
;   via at least the ‘mem_*’ fields of the Multiboot information structure
;   must be included. If the boot loader is capable of passing a memory map
;   and one exists, then it may be included as well.
MBALIGN    equ 1 << 0                 ; Set bit 0 of flags.
MBMEMINFO  equ 1 << 1                 ; Set bit 1 of flags.
MBFLAGS    equ MBALIGN | MBMEMINFO    ; Set the flags.
MBMAGIC    equ 0x1badb002             ; The 'magic number': let the bootloader find the header.
MBCHECKSUM equ -(MBMAGIC + MBFLAGS)   ; Checksum of above, to prove we are multiboot.


; ============================================================================================
; Declare a header as in the Multiboot Standard.
; This section is declared so that we can manipulate it in the link step. Indeed,
; we want to ensure that this section is one of the first things in the final image,
; as required by the MB specification.
section .multiboot
align 4 ; Advances the location counter until it is a multiple of 4.
dd MBMAGIC
dd MBFLAGS
dd MBCHECKSUM


; ============================================================================================
; Reserve a stack for the initial thread. This stack is 16KiB in size (0x4000).
; This section will be located at the end of the executable image.
section .bootstrap_stack, nobits
align 4 ; Advances the location counter until it is a multiple of 4.
stack_bottom:
resb 0x4000
stack_top:


; ============================================================================================
section .text

extern kmain
global _start
_start:
    ; We put the stack's top into esp (the stack grows downwards).
    mov esp, stack_top

    ; Transfer control to the main kernel.
    call kmain

    ; Hang with an infinite loop if kmain unexpectedly end.
    cli
.hang:
    hlt
    jmp .hang
