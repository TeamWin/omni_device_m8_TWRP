# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# Model Ids
# 0P6B10000 - International
# 0P6B12000 - AT&T/Dev Edition
# 0P6B13000 - T-Mobile
# 0P6B16000 - Telus/Rogers (Canada)
# 0P6B20000 - Verizon
# 0P6B70000 - Sprint

# Model Ids (Dual SIM variants)
# 0P6B41000 - Chinese CDMA version
# 0P6B61000 - Chinese GSM version
# 0P6B64000 - European GSM version

BOARD_VENDOR := htc

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := MSM8974
TARGET_NO_BOOTLOADER := true

# Platform
TARGET_BOARD_PLATFORM := msm8974
TARGET_BOARD_PLATFORM_GPU := qcom-adreno330

# Architecture
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_SMP := true
TARGET_CPU_VARIANT := krait
TARGET_USE_KRAIT_BIONIC_OPTIMIZATION := true

# Kernel
BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=31 ehci-hcd.park=3 zcache androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x00000000
BOARD_KERNEL_PAGESIZE := 2048
BOARD_KERNEL_SEPARATED_DT := true
BOARD_MKBOOTIMG_ARGS := --kernel_offset 0x00008000 --ramdisk_offset 0x02008000 --dt device/htc/m8/recovery/dt.img --tags_offset 0x01e00000
BOARD_CUSTOM_BOOTIMG_MK := device/htc/m8/recovery/mkbootimg.mk

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 274464768
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 25165824
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2818572288
BOARD_USERDATAIMAGE_PARTITION_SIZE := 11676942336
BOARD_FLASH_BLOCK_SIZE := 131072 # (BOARD_KERNEL_PAGESIZE * 64)
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

# Recovery
BOARD_HAS_LARGE_FILESYSTEM := true
BOARD_HAS_NO_MISC_PARTITION := true
BOARD_HAS_NO_SELECT_BUTTON := true
BOARD_RECOVERY_SWIPE := true
BOARD_USE_CUSTOM_RECOVERY_FONT := \"roboto_23x41.h\"
BOARD_USES_MMCUTILS := true
TARGET_PREBUILT_KERNEL := device/htc/m8/recovery/kernel
TARGET_RECOVERY_INITRC := device/htc/m8/recovery/init.rc
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"
RECOVERY_GRAPHICS_USE_LINELENGTH := true

# TWRP Build Flags
BOARD_RECOVERY_BLDRMSG_OFFSET := 2048
TW_THEME := portrait_hdpi
TW_INCLUDE_DUMLOCK := true
TW_INCLUDE_CRYPTO := true
TW_NO_EXFAT_FUSE := true
TW_NO_SCREEN_BLANK := true

# USB
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/msm_dwc3/f9200000.dwc3/gadget/lun%d/file

# Vendor Init
TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_m8
TARGET_LIBINIT_DEFINES_FILE := device/htc/m8/init/init_m8.c
