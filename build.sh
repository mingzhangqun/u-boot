#!/bin/bash

#add: bc bison flex libssl-dev u-boot-tools python3-pycryptodome python3-pyelftools
#binutils-arm-linux-gnueabihf binutils-aarch64-linux-gnu
#gcc-arm-linux-gnueabihf gcc-aarch64-linux-gnu

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- j721e_evm_r5_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig

rm -r ti-blobs/tiboot3.bin || true
make ARCH=arm -j4 CROSS_COMPILE=arm-linux-gnueabihf-
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- savedefconfig
cp -v defconfig ./configs/j721e_evm_r5_defconfig
cp -v tiboot3.bin ti-blobs/

make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- distclean
make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- j721e_evm_a72_defconfig
make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- menuconfig

rm -f ti-blobs/tispl.bin || true
rm -f ti-blobs/u-boot.img || true
make ARCH=arm -j4 CROSS_COMPILE=aarch64-linux-gnu- ATF=ti-blobs/bl31.bin TEE=ti-blobs/tee-pager_v2.bin DM=ti-blobs/ipc_echo_testb_mcu1_0_release_strip.xer5f
make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- savedefconfig
cp -v defconfig ./configs/j721e_evm_a72_defconfig
cp -v tispl.bin ti-blobs/
cp -v u-boot.img ti-blobs/
