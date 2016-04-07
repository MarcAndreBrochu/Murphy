HOST?=i386
HOSTARCH:=x86

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
ASFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra -Werror
CPPFLAGS:=$(CPPFLAGS) -Iinclude
LDFLAGS:=$(LDFLAGS)
ASFLAGS:=$(ASFLAGS)
LIBS:=$(LIBS) -nostdlib -lgcc

ARCHDIR:=arch/$(HOSTARCH)

include $(ARCHDIR)/src/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_CFLAGS)
ASFLAGS:=$(ASFLAGS) $(KERNEL_ARCH_ASFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_CFLAGS)

OBJS:=\
$(KERNEL_ARCH_OBJS) \
src/kernel.o \
src/kprint.o \
src/string.o \

CRTI_OBJ:=$(ARCHDIR)/src/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCHDIR)/src/crtn.o

ALL_OUR_OBJS:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ) \

OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ) \

all: murphy.kernel

.PHONY: all clean install install-headers install-kernel

murphy.kernel: $(OBJ_LINK_LIST) $(ARCHDIR)/src/linker.ld
	$(CC) -T $(ARCHDIR)/src/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(AS) $< -o $@ $(ASFLAGS)

clean:
	rm -f murphy.kernel $(OBJS) $(ALL_OUR_OBJS) *.o */*.o */*/*.o

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv ../include $(DESTDIR)$(INCLUDEDIR)

install-kernel: murphy.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp murphy.kernel $(DESTDIR)$(BOOTDIR)
