#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/murphy.kernel isodir/boot/murphy.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "murphy" {
    multiboot /boot/murphy.kernel
}
EOF
grub-mkrescue -o murphy.iso isodir
