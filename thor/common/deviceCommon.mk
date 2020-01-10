#gms
$(call inherit-product-if-exists, vendor/google/products/gms.mk)
#PRODUCT_PROPERTY_OVERRIDES += ro.com.google.clientidbase=android-realtek

#PRODUCT_PROPERTY_OVERRIDES += ro.product.first_api_level=28
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.vndk.version=28.1.0
PRODUCT_SHIPPING_API_LEVEL := 28
PRODUCT_FULL_TREBLE_OVERRIDE := true
#PRODUCT_RESTRICT_VENDOR_FILES := true

# FIXME: should use esdfs instead?
# Enable sdcardfs
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.sys.sdcardfs=1

# By default, enable zram; experiment can toggle the flag,
# which takes effect on boot
PRODUCT_PROPERTY_OVERRIDES += persist.sys.zram_enabled=1

# Default OMX service to non-Treble
#PRODUCT_PROPERTY_OVERRIDES += persist.media.treble_omx=true

# setup dalvik vm configs.
ifneq ($(TARGET_PRODUCT),atv1gb)
# atv1gb heap size is defined in go_defaults_common.mk
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapsize=384m
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapgrowthlimit=128m
endif
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapstartsize=8m
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heaptargetutilization=0.75
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapminfree=512k
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapmaxfree=8m

# setup dex2oat compiler options: everything|speed|balanced|space|interpret-only|verify-none
#PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.dex2oat-filter=speed
#PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.image-dex2oat-filter=speed

# pre-optimization options
#PRODUCT_DEX_PREOPT_BOOT_FLAGS := --compiler-filter=speed
#PRODUCT_DEX_PREOPT_DEFAULT_FLAGS := --compiler-filter=speed
#$(call add-product-dex-preopt-module-config,services,--compiler-filter=space)

PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.sys.timezone=Asia/Taipei
PRODUCT_PROPERTY_OVERRIDES += wifi.interface=wlan0
PRODUCT_PROPERTY_OVERRIDES += wifi.direct.interface=p2p0
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += wifi.supplicant_scan_interval=120
PRODUCT_PROPERTY_OVERRIDES += ro.opengles.version=196610
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.zygote.disable_gl_preload=true
#PRODUCT_PROPERTY_OVERRIDES += ro.kernel.android.checkjni=false
PRODUCT_PROPERTY_OVERRIDES += keyguard.no_require_sim=true
PRODUCT_PROPERTY_OVERRIDES += persist.sys.strictmode.visual=0
PRODUCT_PROPERTY_OVERRIDES += persist.sys.strictmode.disable=1
PRODUCT_PROPERTY_OVERRIDES += debug.hwui.use_buffer_age=false
PRODUCT_PROPERTY_OVERRIDES += debug.hwui.use_partial_updates=false
#PRODUCT_PROPERTY_OVERRIDES += net.dns1 = 168.95.192.1
#PRODUCT_PROPERTY_OVERRIDES += net.dns2 = 8.8.8.8
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.pppoe.coldboot.conn=true

ifeq ($(ENABLE_VMX_BOOT_FLOW), YES)
PRODUCT_PROPERTY_OVERRIDES += vendor.vmx.boot=1
endif

PRODUCT_COPY_FILES += device/realtek/thor/common/ueventd.rc:$(TARGET_COPY_OUT_VENDOR)/ueventd.rc

PRODUCT_COPY_FILES += device/realtek/thor/common/init.thor.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.thor.rc
PRODUCT_COPY_FILES += device/realtek/thor/common/init.thor_vmx.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.thor.rc
PRODUCT_COPY_FILES += device/realtek/thor/common/init.thor.usb.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.thor.usb.rc
PRODUCT_COPY_FILES += device/realtek/thor/common/init.fschk.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.fschk.rc
PRODUCT_COPY_FILES += device/realtek/thor/common/init.e2fsck.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.e2fsck.rc

#PRODUCT_COPY_FILES += device/realtek/thor/common/init.emmc.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.emmc.rc
#PRODUCT_COPY_FILES += device/realtek/thor/common/init.nand.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.nand.rc
#PRODUCT_COPY_FILES += device/realtek/thor/common/init.sata.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.sata.rc
#PRODUCT_COPY_FILES += device/realtek/thor/common/init.vmx.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.vmx.rc
#PRODUCT_COPY_FILES += device/realtek/thor/common/init.xen.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.xen.rc

### must copy one fstab.herclues only
PRODUCT_COPY_FILES += device/realtek/thor/common/fstab.thor.emmc:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thor
#PRODUCT_COPY_FILES += device/realtek/thor/common/fstab.thor.sata:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thor
#PRODUCT_COPY_FILES += device/realtek/thor/common/fstab.thor.vmx:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thor
#PRODUCT_COPY_FILES += device/realtek/thor/common/fstab.thor.xen:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thor

### must copy one sys.part.rc only
#PRODUCT_COPY_FILES += device/realtek/thor/common/sys.part.rc.emmc:$(TARGET_COPY_OUT_VENDOR)/etc/sys.part.rc.emmc
#PRODUCT_COPY_FILES += device/realtek/thor/common/sys.part.rc.sata:$(TARGET_COPY_OUT_VENDOR)/etc/sys.part.rc.sata
#PRODUCT_COPY_FILES += device/realtek/thor/common/sys.part.rc.vmx:$(TARGET_COPY_OUT_VENDOR)/etc/sys.part.rc.vmx
#PRODUCT_COPY_FILES += device/realtek/thor/common/sys.part.rc.xen:$(TARGET_COPY_OUT_VENDOR)/etc/sys.part.rc.xen

PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.location.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.location.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.wifi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.wifi.direct.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.direct.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.usb.host.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.host.xml
#PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.camera.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.xml
#PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.camera.autofocus.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.autofocus.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.camera.external.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.external.xml
#PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.flash-autofocus.xml
#PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.camera.front.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.front.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.ethernet.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.ethernet.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.opengles.aep.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.opengles.aep.xml
#PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.pppoe.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.pppoe.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.hdmi.cec.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.hdmi.cec.xml
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.software.verified_boot.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.verified_boot.xml

PRODUCT_COPY_FILES += device/realtek/thor/common/dhcpcd.conf:$(TARGET_COPY_OUT_VENDOR)/etc/dhcpcd/dhcpcd.conf
PRODUCT_COPY_FILES += device/realtek/thor/common/media_profiles_V1_0.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles_V1_0.xml
PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs.xml
#ifeq ($(TARGET_PRODUCT),atv1gb)
#PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs_rtk_video-1080p.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_rtk_video.xml
#else
PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs_rtk_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_rtk_video.xml
#endif
PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs_rtk_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_rtk_audio.xml
PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs_rtk_audio_sec.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_rtk_audio_sec.xml
PRODUCT_COPY_FILES += device/realtek/thor/common/media_codecs_performance.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_performance.xml
PRODUCT_COPY_FILES += frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_audio.xml
PRODUCT_COPY_FILES += frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video.xml
PRODUCT_COPY_FILES += device/realtek/thor/common/mixer_paths.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths.xml
PRODUCT_COPY_FILES += device/realtek/thor/common/content-types.properties:$(TARGET_COPY_OUT_VENDOR)/lib/content-types.properties

# keylayout
PRODUCT_COPY_FILES += device/realtek/thor/common/venus_IR_input.kl:$(TARGET_COPY_OUT_VENDOR)/usr/keylayout/venus_IR_input.kl
#PRODUCT_COPY_FILES += device/realtek/thor/common/venus_IR_input.kcm:$(TARGET_COPY_OUT_VENDOR)/usr/keychars/venus_IR_input.kcm
PRODUCT_COPY_FILES += device/realtek/thor/common/gpio_cmd.kl:$(TARGET_COPY_OUT_VENDOR)/usr/keylayout/gpio_cmd.kl

# Vendor seccomp policy files for media components:
PRODUCT_COPY_FILES += device/realtek/thor/common/mediacodec.policy:$(TARGET_COPY_OUT_VENDOR)/etc/seccomp_policy/mediacodec.policy

# For audio policy
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/audiopolicy,$(TARGET_COPY_OUT_VENDOR)/etc)
# For audio effect
PRODUCT_COPY_FILES += device/realtek/thor/common/audio_effects.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_effects.xml

# For DvdPlayer
PRODUCT_COPY_FILES += frameworks/base/data/fonts/DroidSansFallbackFull.ttf:$(TARGET_COPY_OUT_SYSTEM)/fonts/DroidSansFallback.ttf

# prebuilt binaries / modules / libraries
#PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/prebuilt/system,$(TARGET_COPY_OUT_SYSTEM))
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/prebuilt/root/sbin,$(TARGET_COPY_OUT_ROOT)/sbin)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/prebuilt/vendor,$(TARGET_COPY_OUT_VENDOR))

# prebuilt widevine tee files
ifeq ($(ENABLE_TEE_DRM_FLOW),true)
ifeq ($(TARGET_PRODUCT),RealtekSTB)
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/wv_for_keybox_RealtekSTB/a2b91020-083e-11e5-9aed0002a5d5c51b.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/a2b91020-083e-11e5-9aed0002a5d5c51b.ta
else
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/wv_for_keybox_RealtekATV/a2b91020-083e-11e5-9aed0002a5d5c51b.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/a2b91020-083e-11e5-9aed0002a5d5c51b.ta
endif

PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/prebuilt/tee/widevine,$(TARGET_COPY_OUT_VENDOR))
else
PRODUCT_COPY_FILES += device/realtek/thor/common/prebuilt/tee/widevine/bin/tee-supplicant:$(TARGET_COPY_OUT_VENDOR)/bin/tee-supplicant
PRODUCT_COPY_FILES += device/realtek/thor/common/prebuilt/tee/widevine/bin/tee_secure_store_agent:$(TARGET_COPY_OUT_VENDOR)/bin/tee_secure_store_agent
endif

# Copy prebuilt hdcp ta files
ifeq ($(USE_RTK_HDCP_TEE), YES)
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/hdcp/87ef28e8-f581-4e3d-b2b2d7e3d48b2321.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/87ef28e8-f581-4e3d-b2b2d7e3d48b2321.ta
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/hdcp/8baaf200-2450-11e4-abe20002a5d5c51b.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/8baaf200-2450-11e4-abe20002a5d5c51b.ta
endif
ifeq ($(USE_RTK_HDCPRX_TEE), YES)
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/hdcp/0df2fadb-b2e0-4345-a491ef0acfaed184.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/0df2fadb-b2e0-4345-a491ef0acfaed184.ta
PRODUCT_COPY_FILES += $(LOCAL_PATH)/common/prebuilt/tee/hdcp/80d173e0-0db9-11e6-a25c0002a5d5c51b.ta:$(TARGET_COPY_OUT_VENDOR)/lib/teetz/80d173e0-0db9-11e6-a25c0002a5d5c51b.ta
endif

# using BOARD_VENDOR_KERNEL_MODULES will remove vendor/lib/modules directory
BOARD_VENDOR_KERNEL_MODULES := $(shell find device/realtek/thor/common/prebuilt/modules -name "*.ko" -type f)
#PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/thor/common/prebuilt/modules,$(TARGET_COPY_OUT_VENDOR)/lib/modules)

# prebuilt mali library
PRODUCT_COPY_FILES += device/realtek/thor/common/prebuilt/mali/vendor/lib/egl/egl.cfg:$(TARGET_COPY_OUT_VENDOR)/lib/egl/egl.cfg

# prebuilt/dailybuild
PRODUCT_PACKAGES += DvdPlayer
PRODUCT_PACKAGES += RtkKeyset
PRODUCT_PACKAGES += fb_init
PRODUCT_PACKAGES += fwdbg
PRODUCT_PACKAGES += gatord

# prebuilt/mali
PRODUCT_PACKAGES += libbccArm.so.32
PRODUCT_PACKAGES += egl/libGLES_mali.so.32
PRODUCT_PACKAGES += libRSDriverArm.so.32
PRODUCT_PACKAGES += libbcc.so.32
PRODUCT_PACKAGES += libLLVM_android.so.32
PRODUCT_PACKAGES += liboffline_compiler_api_gles.so.32
#PRODUCT_PACKAGES += cl_stub/libOpenCL.so.32
PRODUCT_PACKAGES += hw/gralloc.thor.so.32

PRODUCT_PACKAGES += libbccArm.so.64
PRODUCT_PACKAGES += egl/libGLES_mali.so.64
PRODUCT_PACKAGES += libRSDriverArm.so.64
PRODUCT_PACKAGES += liboffline_compiler_api_gles.so.64
#PRODUCT_PACKAGES += cl_stub/libOpenCL.so.64
PRODUCT_PACKAGES += hw/gralloc.thor.so.64

PRODUCT_SUPPORTS_VERITY := false
PRODUCT_SUPPORTS_VERITY_FEC := false
PRODUCT_COPY_FILES += device/realtek/thor/common/fake_kernel:kernel

#For Settings
#0:RAW, 1:LPCM 2ch, 2:LPCM Multi-ch, 3:Auto
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.audio.hdmioutput=1
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.audio.spdifoutput=0
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.audio.playbackeffect=off
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.audio.forcesdaudio=false
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.hdmi.ignoreplugout=false
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.video.auto1080p24=true
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.video.auto2997hz=false
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.miracast.reminder=true
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.hdmi.cecpoweronfromtv=1
