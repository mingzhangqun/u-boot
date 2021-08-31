#!/bin/bash

#add: bc bison flex libssl-dev u-boot-tools python3-pycryptodome python3-pyelftools
#binutils-arm-linux-gnueabihf binutils-aarch64-linux-gnu
#gcc-arm-linux-gnueabihf gcc-aarch64-linux-gnu

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- j721e_evm_r5_defconfig
make ARCH=arm -j2 CROSS_COMPILE=arm-linux-gnueabihf-
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- savedefconfig
cp -v defconfig ./configs/j721e_evm_r5_defconfig
