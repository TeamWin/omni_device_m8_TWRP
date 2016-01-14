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
# 0P6B41000 - Chinese (China Telecom) LTE/EV-DO/CDMA + GSM version
# 0P6B61000 - Chinese (China Unicom) LTE/WCDMA/GSM + GSM version
# 0P6B64000 / 0P6B68000 - International LTE/WCDMA/GSM + GSM version

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
BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=30 msm_rtb.filter=0x3b7 ehci-hcd.park=3 androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x00000000
BOARD_KERNEL_PAGESIZE := 2048
BOARD_KERNEL_SEPARATED_DT := true
BOARD_MKBOOTIMG_ARGS := --kernel_offset 0x00008000 --ramdisk_offset 0x02000000 --dt device/htc/m8/recovery/dt.img --tags_offset 0x01e00000
BOARD_CUSTOM_BOOTIMG_MK := device/htc/m8/recovery/mkbootimg.mk

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216
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
BOARD_SUPPRESS_SECURE_ERASE := true
BOARD_USES_MMCUTILS := true
TARGET_PREBUILT_KERNEL := device/htc/m8/recovery/kernel
TARGET_RECOVERY_DEVICE_MODULES := chargeled # strace twrpdec
#TW_RECOVERY_ADDITIONAL_RELINK_FILES := $(OUT)/utilities/strace $(OUT)/recovery/root/sbin/twrpdec
#TARGET_USES_LOGD := true

# TWRP Build Flags
BOARD_RECOVERY_BLDRMSG_OFFSET := 2048
TW_EXCLUDE_DEFAULT_USB_INIT := true
TW_THEME := portrait_hdpi
TW_INCLUDE_DUMLOCK := true
TW_INCLUDE_CRYPTO := true
TW_INCLUDE_NTFS_3G := true
TW_NO_EXFAT_FUSE := true
#TWRP_EVENT_LOGGING := true
#TWRP_INCLUDE_LOGCAT := true

# Vendor Init
TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_msm
TARGET_LIBINIT_DEFINES_FILE := device/htc/m8/recovery/init/init_m8.cpp
