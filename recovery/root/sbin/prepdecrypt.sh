#!/sbin/sh

SCRIPTNAME="PrepDecrypt"
LOGFILE=/tmp/recovery.log
venbin="/vendor/bin"
venlib="/vendor/lib"

log_info()
{
	echo "I:$SCRIPTNAME:$1" >> "$LOGFILE"
}

log_error()
{
	echo "E:$SCRIPTNAME:$1" >> "$LOGFILE"
}

relink()
{
	if [ -f "$1" ]; then
		fname=$(basename "$1")
		target="/sbin/$fname"
		sed 's|/system/bin/linker|///////sbin/linker|' "$1" > "$target"
		chmod 755 "$target"
	fi
}

finish()
{
	setprop crypto.ready 1
	log_info "Script complete. Device ready for decryption."
	exit 0
}

abi=$(getprop ro.product.cpu.abi)

case "$abi" in
	*64*)
		venlib="/vendor/lib64"
		;;
esac

log_info "Running prepdecrypt script for TWRP..."
relink "$venbin/qseecomd"
relink "$venbin/hw/android.hardware.keymaster@3.0-service"
relink "$venbin/hw/android.hardware.keymaster@3.0-service-qti"
relink "$venbin/hw/android.hardware.keymaster@4.0-service-qti"
relink "$venlib/libQSEEComAPI.so"

osver=$(getprop ro.build.version.release)
osver_orig=$(getprop ro.build.version.release_orig)
sdkver=$(getprop ro.build.version.sdk)
patchlevel=$(getprop ro.build.version.security_patch)
patchlevel_orig=$(getprop ro.build.version.security_patch_orig)

if [ "$sdkver" -lt 26 ]; then
	DEFAULTPROP=default.prop
else
	DEFAULTPROP=prop.default
fi

# Be sure to increase the PLATFORM_VERSION in build/core/version_defaults.mk to override Google's anti-rollback features to something rather insane
if [ -z "$osver" ]; then
	if [ -n "$osver_orig" ]; then
		setprop ro.build.version.release "$osver_orig"
		echo "ro.build.version.release=$osver_orig" >> "/$DEFAULTPROP";
	else
		osver="20.1.0"
		setprop ro.build.version.release "$osver"
		echo "ro.build.version.release=$osver" >> "/$DEFAULTPROP";
	fi
fi
if [ -z "$patchlevel" ]; then
	if [ -n "$patchlevel_orig" ]; then
		setprop ro.build.version.security_patch "$patchlevel_orig"
		echo "ro.build.version.security_patch=$patchlevel_orig" >> "/$DEFAULTPROP";
		finish
	else
		patchlevel="2099-12-31"
		setprop ro.build.version.security_patch "$patchlevel"
		echo "ro.build.version.security_patch=$patchlevel" >> "/$DEFAULTPROP";
		finish
	fi
else
	finish
fi

