#ifndef __kernel_kprint_h
#define __kernel_kprint_h

void kprint(const char *str);       // Prints a string on the kernel's terminal
void kprint_hexu(unsigned int num); // Prints an unsigned integer on the kernel's terminal as a hex number
void kprint_hexi(int num);          // Prints a signed integer on the kernel's terminal as a hex number

#endif // __kernel_kprint_h
