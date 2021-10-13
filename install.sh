#!/bin/bash

if ! id | grep -q root; then
	echo "./install.sh must be run as root:"
	echo "sudo ./install.sh"
	exit
fi

if [ -d /boot/firmware/ ] ; then
	cp -v ./ti-blobs/tiboot3.bin /boot/firmware/
	cp -v ./ti-blobs/tispl.bin /boot/firmware/
	cp -v ./ti-blobs/u-boot.img /boot/firmware/
fi
