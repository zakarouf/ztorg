#!/bin/sh

LIB_DIR="/usr/local/lib/"
INCLUDE_DIR="/usr/local/include/"

sh make-lib.sh

mv -ni build/lib/libzkzse.a "$LIB_DIR"
cp -Rf build/include/zse "$INCLUDE_DIR"

rm -rf build/include/zse
