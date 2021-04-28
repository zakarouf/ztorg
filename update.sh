#!/bin/sh

echo "Updating Libraries"
git clone --depth=1 git://github.com/zakarouf/z_

rm -rf src/zse/common/z_
echo "Installing"
cp -R z_/src src/zse/common/z_
rm -rf z_
