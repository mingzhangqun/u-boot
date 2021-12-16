/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration header file for K3 J721E EVM
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - https://www.ti.com/
 *	Lokesh Vutla <lokeshvutla@ti.com>
 */

#ifndef __CONFIG_J721E_EVM_H
#define __CONFIG_J721E_EVM_H

#include <linux/sizes.h>
#include <config_distro_bootcmd.h>
#include <environment/ti/mmc.h>
#include <environment/ti/k3_rproc.h>
#include <environment/ti/ufs.h>
#include <environment/ti/k3_dfu.h>

/* DDR Configuration */
#define CONFIG_SYS_SDRAM_BASE1		0x880000000

/* SPL Loader Configuration */
#if defined(CONFIG_TARGET_J721E_A72_EVM) || defined(CONFIG_TARGET_J7200_A72_EVM)
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SPL_TEXT_BASE +	\
					 CONFIG_SYS_K3_NON_SECURE_MSRAM_SIZE)
#define CONFIG_SYS_UBOOT_BASE		0x50280000
/* Image load address in RAM for DFU boot*/
#else
#define CONFIG_SYS_UBOOT_BASE		0x50080000
/*
 * Maximum size in memory allocated to the SPL BSS. Keep it as tight as
 * possible (to allow the build to go through), as this directly affects
 * our memory footprint. The less we use for BSS the more we have available
 * for everything else.
 */
#define CONFIG_SPL_BSS_MAX_SIZE		0xA000
/*
 * Link BSS to be within SPL in a dedicated region located near the top of
 * the MCU SRAM, this way making it available also before relocation. Note
 * that we are not using the actual top of the MCU SRAM as there is a memory
 * location filled in by the boot ROM that we want to read out without any
 * interference from the C context.
 */
#define CONFIG_SPL_BSS_START_ADDR	(CONFIG_SYS_K3_BOOT_PARAM_TABLE_INDEX -\
					 CONFIG_SPL_BSS_MAX_SIZE)
/* Set the stack right below the SPL BSS section */
#define CONFIG_SYS_INIT_SP_ADDR         CONFIG_SPL_BSS_START_ADDR
/* Configure R5 SPL post-relocation malloc pool in DDR */
#define CONFIG_SYS_SPL_MALLOC_START	0x84000000
#define CONFIG_SYS_SPL_MALLOC_SIZE	SZ_16M
/* Image load address in RAM for DFU boot*/
#endif

#ifdef CONFIG_SYS_K3_SPL_ATF
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME	"tispl.bin"
#endif

#define CONFIG_SPL_MAX_SIZE		CONFIG_SYS_K3_MAX_DOWNLODABLE_IMAGE_SIZE

#define CONFIG_SYS_BOOTM_LEN		SZ_64M
#define CONFIG_CQSPI_REF_CLK		133333333

/* HyperFlash related configuration */
#define CONFIG_SYS_MAX_FLASH_BANKS_DETECT 1

/* U-Boot general configuration */
#define EXTRA_ENV_J721E_BOARD_SETTINGS					\
	"default_device_tree=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0"	\
	"findfdt="							\
		"echo board_name=[$board_name] ...;"			\
		"setenv name_fdt ${default_device_tree};"		\
		"if test $board_name = J721EX-PM1-SOM; then "		\
			"setenv name_fdt k3-j721e-proc-board-tps65917.dtb; " \
		"elif test $board_name = J721EX-PM2-SOM; then "		\
			"setenv name_fdt k3-j721e-beagleboneai64.dtb; " \
		"elif test $board_name = BBONEAI-64-B0-; then "		\
			"setenv name_fdt k3-j721e-beagleboneai64.dtb; " \
		"elif test $board_name = j721e; then "			\
			"setenv name_fdt k3-j721e-common-proc-board.dtb; " \
		"elif test $board_name = j721e-eaik; then "		\
			"setenv name_fdt k3-j721e-eaik.dtb; "		\
		"else " \
			"setenv name_fdt k3-j721e-beagleboneai64.dtb; "	\
		"fi; " \
		"echo name_fdt=[${name_fdt}] ...;"			\
		"setenv fdtfile ${name_fdt}\0"				\
	"eeprom_dump=i2c dev 0; "					\
		"i2c md 0x50 0x00.1 20; "				\
		"\0"							\
	"eeprom_dump_51=i2c dev 0; "					\
		"i2c md 0x51 0x00.1 20; "				\
		"\0"							\
	"eeprom_bbai=i2c dev 0; "					\
		"i2c md 0x50 0x00.1 20; "				\
		"i2c mw 0x50 0x00.1 aa; "				\
		"i2c mw 0x50 0x01.1 55; "				\
		"i2c mw 0x50 0x02.1 33; "				\
		"i2c mw 0x50 0x03.1 ee; "				\
		"i2c mw 0x50 0x04.1 01; "				\
		"i2c mw 0x50 0x05.1 37; "				\
		"i2c mw 0x50 0x06.1 00; "				\
		"i2c mw 0x50 0x07.1 10; "				\
		"i2c mw 0x50 0x08.1 2e; "				\
		"i2c mw 0x50 0x09.1 00; "				\
		"i2c mw 0x50 0x0a.1 42; "				\
		"i2c mw 0x50 0x0b.1 42; "				\
		"i2c mw 0x50 0x0c.1 4f; "				\
		"i2c mw 0x50 0x0d.1 4e; "				\
		"i2c mw 0x50 0x0e.1 45; "				\
		"i2c mw 0x50 0x0f.1 41; "				\
		"i2c mw 0x50 0x10.1 49; "				\
		"i2c mw 0x50 0x11.1 2d; "				\
		"i2c mw 0x50 0x12.1 36; "				\
		"i2c mw 0x50 0x13.1 34; "				\
		"i2c mw 0x50 0x14.1 2d; "				\
		"i2c mw 0x50 0x15.1 42; "				\
		"i2c mw 0x50 0x16.1 30; "				\
		"i2c mw 0x50 0x17.1 2d; "				\
		"i2c md 0x50 0x00.1 20; "				\
		"\0"							\
	"eeprom_bbai_erase=i2c dev 0; "					\
		"i2c md 0x50 0x00.1 20; "				\
		"i2c mw 0x50 0x00.1 ff; "				\
		"i2c mw 0x50 0x01.1 ff; "				\
		"i2c mw 0x50 0x02.1 ff; "				\
		"i2c mw 0x50 0x03.1 ff; "				\
		"i2c mw 0x50 0x04.1 ff; "				\
		"i2c mw 0x50 0x05.1 ff; "				\
		"i2c mw 0x50 0x06.1 ff; "				\
		"i2c mw 0x50 0x07.1 ff; "				\
		"i2c mw 0x50 0x08.1 ff; "				\
		"i2c mw 0x50 0x09.1 ff; "				\
		"i2c mw 0x50 0x0a.1 ff; "				\
		"i2c mw 0x50 0x0b.1 ff; "				\
		"i2c mw 0x50 0x0c.1 ff; "				\
		"i2c mw 0x50 0x0d.1 ff; "				\
		"i2c mw 0x50 0x0e.1 ff; "				\
		"i2c mw 0x50 0x0f.1 ff; "				\
		"i2c mw 0x50 0x10.1 ff; "				\
		"i2c mw 0x50 0x11.1 ff; "				\
		"i2c mw 0x50 0x12.1 ff; "				\
		"i2c mw 0x50 0x13.1 ff; "				\
		"i2c mw 0x50 0x14.1 ff; "				\
		"i2c mw 0x50 0x15.1 ff; "				\
		"i2c mw 0x50 0x16.1 ff; "				\
		"i2c mw 0x50 0x17.1 ff; "				\
		"i2c md 0x50 0x00.1 20; "				\
		"\0"							\
	"eeprom_bbai_51=i2c dev 0; "					\
		"i2c md 0x51 0x00.1 20; "				\
		"i2c mw 0x51 0x00.1 aa; "				\
		"i2c mw 0x51 0x01.1 55; "				\
		"i2c mw 0x51 0x02.1 33; "				\
		"i2c mw 0x51 0x03.1 ee; "				\
		"i2c mw 0x51 0x04.1 01; "				\
		"i2c mw 0x51 0x05.1 37; "				\
		"i2c mw 0x51 0x06.1 00; "				\
		"i2c mw 0x51 0x07.1 10; "				\
		"i2c mw 0x51 0x08.1 2e; "				\
		"i2c mw 0x51 0x09.1 00; "				\
		"i2c mw 0x51 0x0a.1 42; "				\
		"i2c mw 0x51 0x0b.1 42; "				\
		"i2c mw 0x51 0x0c.1 4f; "				\
		"i2c mw 0x51 0x0d.1 4e; "				\
		"i2c mw 0x51 0x0e.1 45; "				\
		"i2c mw 0x51 0x0f.1 41; "				\
		"i2c mw 0x51 0x10.1 49; "				\
		"i2c mw 0x51 0x11.1 2d; "				\
		"i2c mw 0x51 0x12.1 36; "				\
		"i2c mw 0x51 0x13.1 34; "				\
		"i2c mw 0x51 0x14.1 2d; "				\
		"i2c mw 0x51 0x15.1 42; "				\
		"i2c mw 0x51 0x16.1 30; "				\
		"i2c mw 0x51 0x17.1 2d; "				\
		"i2c md 0x51 0x00.1 20; "				\
		"\0"							\
	"eeprom_bbai_51_erase=i2c dev 0; "				\
		"i2c md 0x51 0x00.1 20; "				\
		"i2c mw 0x51 0x00.1 ff; "				\
		"i2c mw 0x51 0x01.1 ff; "				\
		"i2c mw 0x51 0x02.1 ff; "				\
		"i2c mw 0x51 0x03.1 ff; "				\
		"i2c mw 0x51 0x04.1 ff; "				\
		"i2c mw 0x51 0x05.1 ff; "				\
		"i2c mw 0x51 0x06.1 ff; "				\
		"i2c mw 0x51 0x07.1 ff; "				\
		"i2c mw 0x51 0x08.1 ff; "				\
		"i2c mw 0x51 0x09.1 ff; "				\
		"i2c mw 0x51 0x0a.1 ff; "				\
		"i2c mw 0x51 0x0b.1 ff; "				\
		"i2c mw 0x51 0x0c.1 ff; "				\
		"i2c mw 0x51 0x0d.1 ff; "				\
		"i2c mw 0x51 0x0e.1 ff; "				\
		"i2c mw 0x51 0x0f.1 ff; "				\
		"i2c mw 0x51 0x10.1 ff; "				\
		"i2c mw 0x51 0x11.1 ff; "				\
		"i2c mw 0x51 0x12.1 ff; "				\
		"i2c mw 0x51 0x13.1 ff; "				\
		"i2c mw 0x51 0x14.1 ff; "				\
		"i2c mw 0x51 0x15.1 ff; "				\
		"i2c mw 0x51 0x16.1 ff; "				\
		"i2c mw 0x51 0x17.1 ff; "				\
		"i2c md 0x51 0x00.1 20; "				\
		"\0"							\
	"emmc_boot0_bbai=mmc partconf 0 1 1 1; "			\
		"mmc dev 0 1; "						\
		"mmc erase 0 0x2400; "					\
		"fatload mmc 1 ${loadaddr} tiboot3.bin; "		\
		"mmc write ${loadaddr} 0x0 0x300; "			\
		"fatload mmc 1 ${loadaddr} tispl.bin; "			\
		"mmc write ${loadaddr} 0x300 0x600; "			\
		"fatload mmc 1 ${loadaddr} u-boot.img; "		\
		"mmc write ${loadaddr} 0x900 0x1000; "			\
		"fatload mmc 1 ${loadaddr} sysfw.itb; "			\
		"mmc write ${loadaddr} 0x1900 0x300; "			\
		"mmc bootbus 0 2 0 0; "					\
		"\0"							\
	"name_kern=Image\0"						\
	"console=ttyS2,115200n8\0"					\
	"args_all=setenv optargs earlycon=ns16550a,mmio32,0x02800000 "	\
		"${mtdparts}\0"						\
	"run_kern=booti ${loadaddr} ${rd_spec} ${fdtaddr}\0"

#define PARTS_DEFAULT \
	/* Linux partitions */ \
	"uuid_disk=${uuid_gpt_disk};" \
	"name=rootfs,start=0,size=-,uuid=${uuid_gpt_rootfs}\0"

#ifdef CONFIG_SYS_K3_SPL_ATF
#if defined(CONFIG_TARGET_J721E_R5_EVM)
#define EXTRA_ENV_R5_SPL_RPROC_FW_ARGS_MMC				\
	"addr_mcur5f0_0load=0x89000000\0"				\
	"name_mcur5f0_0fw=/lib/firmware/j7-mcu-r5f0_0-fw\0"
#elif defined(CONFIG_TARGET_J7200_R5_EVM)
#define EXTRA_ENV_R5_SPL_RPROC_FW_ARGS_MMC				\
	"addr_mcur5f0_0load=0x89000000\0"				\
	"name_mcur5f0_0fw=/lib/firmware/j7200-mcu-r5f0_0-fw\0"
#endif /* CONFIG_TARGET_J721E_R5_EVM */
#else
#define EXTRA_ENV_R5_SPL_RPROC_FW_ARGS_MMC ""
#endif /* CONFIG_SYS_K3_SPL_ATF */

/* U-Boot MMC-specific configuration */
#define EXTRA_ENV_J721E_BOARD_SETTINGS_MMC				\
	"boot=mmc\0"							\
	"mmcdev=0\0"							\
	"bootpart=0:2\0"						\
	"bootdir=/boot\0"						\
	EXTRA_ENV_R5_SPL_RPROC_FW_ARGS_MMC				\
	"rd_spec=-\0"							\
	"init_mmc=run args_all args_mmc\0"				\
	"get_fdt_mmc=load mmc ${bootpart} ${fdtaddr} ${bootdir}/${name_fdt}\0" \
	"get_overlay_mmc="						\
		"fdt address ${fdtaddr};"				\
		"fdt resize 0x100000;"					\
		"for overlay in $name_overlays;"			\
		"do;"							\
		"load mmc ${bootpart} ${dtboaddr} ${bootdir}/${overlay} && "	\
		"fdt apply ${dtboaddr};"				\
		"done;\0"						\
	"partitions=" PARTS_DEFAULT					\
	"get_kern_mmc=load mmc ${bootpart} ${loadaddr} "		\
		"${bootdir}/${name_kern}\0"				\
	"get_fit_mmc=load mmc ${bootpart} ${addr_fit} "			\
		"${bootdir}/${name_fit}\0"				\
	"partitions=" PARTS_DEFAULT

/* Set the default list of remote processors to boot */
#if defined(CONFIG_TARGET_J721E_A72_EVM) || defined(CONFIG_TARGET_J7200_A72_EVM)
#ifdef DEFAULT_RPROCS
#undef DEFAULT_RPROCS
#endif
#endif

#ifdef CONFIG_TARGET_J721E_A72_EVM
#define DEFAULT_RPROCS	""						\
		"2 /lib/firmware/j7-main-r5f0_0-fw "			\
		"3 /lib/firmware/j7-main-r5f0_1-fw "			\
		"4 /lib/firmware/j7-main-r5f1_0-fw "			\
		"5 /lib/firmware/j7-main-r5f1_1-fw "			\
		"6 /lib/firmware/j7-c66_0-fw "				\
		"7 /lib/firmware/j7-c66_1-fw "				\
		"8 /lib/firmware/j7-c71_0-fw "
#endif /* CONFIG_TARGET_J721E_A72_EVM */

#ifdef CONFIG_TARGET_J7200_A72_EVM
#define EXTRA_ENV_CONFIG_MAIN_CPSW0_QSGMII_PHY				\
	"do_main_cpsw0_qsgmii_phyinit=1\0"				\
	"init_main_cpsw0_qsgmii_phy=gpio set gpio@22_17;"		\
		 "gpio clear gpio@22_16\0"				\
	"main_cpsw0_qsgmii_phyinit="					\
	"if test ${do_main_cpsw0_qsgmii_phyinit} -eq 1 && test ${dorprocboot} -eq 1 && " \
			"test ${boot} = mmc; then "			\
		"run init_main_cpsw0_qsgmii_phy;"			\
	"fi;\0"
#define DEFAULT_RPROCS ""						\
		"2 /lib/firmware/j7200-main-r5f0_0-fw "			\
		"3 /lib/firmware/j7200-main-r5f0_1-fw "
#endif /* CONFIG_TARGET_J7200_A72_EVM */

#ifndef EXTRA_ENV_CONFIG_MAIN_CPSW0_QSGMII_PHY
#define EXTRA_ENV_CONFIG_MAIN_CPSW0_QSGMII_PHY
#endif

/* set default dfu_bufsiz to 128KB (sector size of OSPI) */
#define EXTRA_ENV_DFUARGS \
	DFU_ALT_INFO_MMC \
	DFU_ALT_INFO_EMMC \
	DFU_ALT_INFO_RAM \
	DFU_ALT_INFO_OSPI

#if defined(CONFIG_TARGET_J721E_A72_EVM) || defined(CONFIG_TARGET_J7200_A72_EVM)
#define EXTRA_ENV_J721E_BOARD_SETTINGS_MTD				\
	"mtdids=" CONFIG_MTDIDS_DEFAULT "\0"				\
	"mtdparts=" CONFIG_MTDPARTS_DEFAULT "\0"
#else
#define EXTRA_ENV_J721E_BOARD_SETTINGS_MTD
#endif

/* Incorporate settings into the U-Boot environment */
#define CONFIG_EXTRA_ENV_SETTINGS					\
	DEFAULT_LINUX_BOOT_ENV						\
	DEFAULT_MMC_TI_ARGS						\
	DEFAULT_FIT_TI_ARGS						\
	EXTRA_ENV_J721E_BOARD_SETTINGS					\
	EXTRA_ENV_J721E_BOARD_SETTINGS_MMC				\
	EXTRA_ENV_RPROC_SETTINGS					\
	EXTRA_ENV_DFUARGS						\
	DEFAULT_UFS_TI_ARGS						\
	EXTRA_ENV_J721E_BOARD_SETTINGS_MTD				\
	EXTRA_ENV_CONFIG_MAIN_CPSW0_QSGMII_PHY

/* Now for the remaining common defines */
#include <configs/ti_armv7_common.h>

/* MMC ENV related defines */

#endif /* __CONFIG_J721E_EVM_H */
