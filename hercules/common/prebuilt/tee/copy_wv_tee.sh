#!/bin/sh

option=0
dst=./widevine
DRM_TA_DIR=../../../../../../../qa_supplement/widevine/hercules
TEE_DIR=../../../../../../../qa_supplement/widevine/system

if [ ! -d "$dst" ]; then
    mkdir $dst
fi

if [ ! -d "$dst/lib/" ]; then
    echo create $dst/lib
    mkdir $dst/lib
fi

if [ ! -d "$dst/etc/" ]; then
    mkdir $dst/etc
fi

if [ ! -d "$dst/bin" ]; then
    mkdir $dst/bin
fi

if [ $option -eq 1 ]; then
	echo ==== Process: Copy files form OUT:$OUT =====
	rsync -a $OUT/vendor/lib/liboemcrypto.so	$dst/lib/
	rsync -a $OUT/vendor/lib/libwvhidl.so		$dst/lib/
	#rsync -a $OUT/vendor/lib/libteec.so		$dst/lib/
	rsync -a $OUT/vendor/lib/mediadrm/libwvdrmengine.so	$dst/lib/mediadrm/
	rsync -a $OUT/vendor/lib/teetz			$dst/lib/

	rsync -a $OUT/vendor/bin/tee-supplicant		$dst/bin/
	rsync -a $OUT/vendor/bin/tee_*			$dst/bin/

	rsync -a $OUT/vendor/etc/init/android.hardware.drm@1.1-service.widevine.rc	$dst/etc/init/
	rsync -a $OUT/vendor/bin/hw/android.hardware.drm@1.1-service.widevine		$dst/bin/hw/
	rsync -a $OUT/vendor/bin/hw/android.hardware.drm@1.0-service			$dst/bin/hw/
else
	echo === Process: Copy files form qa_supplement ====
	rsync -a ${TEE_DIR}/vendor/lib/9.0/liboemcrypto.so $dst/lib/
	rsync -a ${TEE_DIR}/vendor/lib/9.0/libwvhidl.so    $dst/lib/
	#rsync -a ${DRM_TA_DIR}/libteec.so		$dst/lib/
	rsync -a ${TEE_DIR}/vendor/lib/mediadrm/9.0/libwvdrmengine.so $dst/lib/mediadrm/
	rsync -a ${TEE_DIR}/vendor/lib/mediadrm/9.0/libPlayReadyDrmCryptoPlugin.so $dst/lib/mediadrm/
	rsync -a ${DRM_TA_DIR}/*ta			$dst/lib/teetz
	rsync -a ${DRM_TA_DIR}/wv_for_keybox_RealtekSTB/ $dst/../wv_for_keybox_RealtekSTB/
	rsync -a ${DRM_TA_DIR}/ATV_tee_api/              $dst/../TEEapi_for_1G_ATV/
	mv $dst/lib/teetz/a2* $dst/../wv_for_keybox_RealtekATV/
	mv $dst/lib/teetz/7a* $dst/../TEEapi_for_normal/

	rsync -a ${DRM_TA_DIR}/wv_for_9.0/tee-supplicant		$dst/bin/
	rsync -a ${DRM_TA_DIR}/tee_*			$dst/bin/

	rsync -a ${TEE_DIR}/vendor/drm/9.0/android.hardware.drm@1.1-service.widevine.rc	$dst/etc/init/
	rsync -a ${TEE_DIR}/vendor/drm/9.0/android.hardware.drm@1.1-service.widevine	$dst/bin/hw/
fi
ls -AR --color=auto $dst $dst/../wv_for_keybox_RealtekSTB/
