SYSTEM_HEADER_PROJECTS="murphy"
PROJECTS="murphy"

export MAKE=${MAKE:-make}
export HOST=i686-elf

export AR=${HOST}-ar
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''
export ASFLAGS=''

# Configure the cross-compiler to use the desired system root.
export CC="$CC --sysroot=$PWD/sysroot"
export CC="$CC -isystem=$INCLUDEDIR"
