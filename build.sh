#!/bin/bash

#add: bc bison flex libssl-dev u-boot-tools python3-pycryptodome python3-pyelftools
#binutils-arm-linux-gnueabihf binutils-aarch64-linux-gnu
#gcc-arm-linux-gnueabihf gcc-aarch64-linux-gnu

echo "make CROSS_COMPILE=arm-linux-gnueabihf- distclean"
make CROSS_COMPILE=arm-linux-gnueabihf- distclean

echo "make CROSS_COMPILE=arm-linux-gnueabihf- j721e_evm_r5_defconfig O=/tmp/r5"
make CROSS_COMPILE=arm-linux-gnueabihf- j721e_evm_r5_defconfig O=/tmp/r5

echo "make -j2 CROSS_COMPILE=arm-linux-gnueabihf- O=/tmp/r5"
make -j2 CROSS_COMPILE=arm-linux-gnueabihf- O=/tmp/r5

