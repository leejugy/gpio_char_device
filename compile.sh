set -e

export CC=arm-linux-gnueabihf-gcc
make -j
cp gpio ~/share