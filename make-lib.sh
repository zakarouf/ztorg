#!/bin/sh

CC=gcc
AR=ar
OUT="libzkzse.a"
LDFLAGS="-I/usr/local/include -L/usr/local/lib -lzkcollection"
CFILES="$(find src/zse -name '*.c')"

echo "Compiling\n"
CC -Wall -Wextra -Os -O2 -c $CFILES

echo "Creating Library $OUT\n"
AR -q $OUT *.o
rm *.o

echo "Installing library\n"
rm -rf ./build/lib
mkdir build
mkdir ./build/lib
mv "$OUT" ./build/lib/

sh extract-headers.sh

