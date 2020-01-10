#!/sbin/busybox sh
if [ ! -d "/data/lib" ]
then
	mkdir "/data/lib"
        chmod 755 "/data/lib"
fi

if [ ! -d "/data/libTmp" ]
then
	mkdir "/data/libTmp"
	cp /system/vendor/lib/mediadrm/*.rsa /data/libTmp
fi

if [ -f "/vendor/bin/rtk_aes_file_decrypt" ]
then
	/vendor/bin/rtk_aes_file_decrypt
fi

if [ -f "/vendor/bin/rtk_lib_decryptor" ]
then
	/vendor/bin/rtk_lib_decryptor /system/vendor/lib/mediadrm/rsa_lib_2048.pub
fi
