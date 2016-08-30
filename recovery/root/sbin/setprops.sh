#!/sbin/sh

# This sets the props for ro.build.fingerprint and 
# and ro.build.description to the values from the 
# current build.prop.
#
# This will allow OTA zips to see the correct
# fingerprint when trying to install with TWRP.
#
# Note that this will not allow the firmware from the OTA
# to install, nor will it allow an OTA to install on
# a non-stock system.

# Mount system (read-only)
mount -t ext4 -o ro /dev/block/bootdevice/by-name/system /system

# Set variables based on props
# PROP_NAME=`cat /system/build.prop | grep ro.prop.name | cut -d'=' -f2` # This is another way to do it
BUILD_FINGERPRINT=`sed '/^\#/d' /system/build.prop | grep ro.build.fingerprint  | tail -n 1 | sed 's/^.*=//'`
PRODUCT_DEVICE=`sed '/^\#/d' /system/build.prop | grep ro.product.device  | tail -n 1 | sed 's/^.*=//'`

# Set props to systm/build.prop values
setprop ro.build.fingerprint $BUILD_FINGERPRINT
setprop ro.product.device $PRODUCT_DEVICE

# Unmount system
umount -l /system
