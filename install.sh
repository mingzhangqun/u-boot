#!/bin/bash

if ! id | grep -q root; then
	echo "./install.sh must be run as root:"
	echo "sudo ./install.sh"
	exit
fi

if [ -d /boot/firmware/ ] ; then
	if [ -f /boot/firmware/tiboot3.bin ] ; then
		rm -f /boot/firmware/tiboot3.bin || true
		sync
	fi

	if [ -f /boot/firmware/tispl.bin ] ; then
		rm -f /boot/firmware/tispl.bin || true
		sync
	fi

	if [ -f /boot/firmware/u-boot.img ] ; then
		rm -f /boot/firmware/u-boot.img || true
		sync
	fi

	cp -v ./ti-blobs/tiboot3.bin /boot/firmware/
	sync

	cp -v ./ti-blobs/tispl.bin /boot/firmware/
	sync

	cp -v ./ti-blobs/u-boot.img /boot/firmware/
	sync
fi
