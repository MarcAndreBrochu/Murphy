#ifndef __kernel_kprintf_h
#define __kernel_kprintf_h

int kprintf(const char *__restrict, ...);
int kputchar(int);
int kputs(const char *);

#endif // __kernel_kprintf_h
