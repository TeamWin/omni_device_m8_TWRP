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
	log_info "crypto.ready=$(getprop crypto.ready)"
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
relink "$venlib/libQSEEComAPI.so"
relink "$venbin/hw/android.hardware.keymaster@3.0-service"
relink "$venbin/hw/android.hardware.keymaster@3.0-service-qti"
finish
