#!/bin/sh

BUILD_INC_FOLDER="./build/include/zse"
SRC="src/zse"

echo "Getting Headers\n"
echo "Extracting in ./build/include/"

find $SRC -name '*.h' | cpio -pdm  ./build/include/

rm -rf $BUILD_INC_FOLDER
mv "./build/include/$SRC" $BUILD_INC_FOLDER
rm -rf "./build/include/src"

echo "Extration Complete"
echo "\nAt $BUILD_INC_FOLDER"
