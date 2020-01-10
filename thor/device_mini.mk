PRODUCT_AAPT_CONFIG := normal large tvdpi mdpi hdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

# setup dex2oat compiler options: everything|speed|balanced|space|interpret-only|verify-none
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.dex2oat-filter=speed
PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.image-dex2oat-filter=speed

# pre-optimization options
PRODUCT_DEX_PREOPT_BOOT_FLAGS := --compiler-filter=speed
PRODUCT_DEX_PREOPT_DEFAULT_FLAGS := --compiler-filter=speed
#$(call add-product-dex-preopt-module-config,services,--compiler-filter=space)

PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.sys.timezone=Asia/Taipei
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += wifi.interface=wlan0
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += wifi.supplicant_scan_interval=120
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.opengles.version=196610
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.zygote.disable_gl_preload=true
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.kernel.android.checkjni=false
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += keyguard.no_require_sim=true
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.sys.strictmode.visual=0
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.sys.strictmode.disable=1
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += debug.hwui.use_buffer_age=false
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += debug.hwui.use_partial_updates=false
#PRODUCT_PROPERTY_OVERRIDES += net.dns1 = 168.95.192.1
#PRODUCT_PROPERTY_OVERRIDES += net.dns2 = 8.8.8.8

##USE_LAYOUT_UI_1080 := true
#ifeq ($(IMAGE_DRAM_SIZE), 1GB)
#USE_LAYOUT_MEM_LOW := true
#endif

USE_RT_MEDIA_PLAYER := true
ENABLE_LIGHTTPD := false
USE_SETTINGS_SERVICE := false
USE_RTK_GPIO := false
# For DRM code flow
ENABLE_DRM_PLUGIN_SERVICE := false
# For TEE OS, video used physical Address
ENABLE_TEE_DRM_FLOW	:= false

USE_RTK_HDCP1x_CONTROL := NO
USE_RTK_HDCP22_CONTROL := NO
USE_RTK_VOUT_UTIL := YES
USE_RTK_AOUT_UTIL := YES
USE_XML_AUDIO_POLICY_CONF := 1


USE_RTK_PPPOE := NO

# used for recovery mode - apply for factory update
# example: RECOVERY_FACTORY_CMD0 := rm factory_test.txt
RECOVERY_FACTORY_CMD0 := cd ../../;cp -rf tmp/install_factory/* tmp/factory/;
RECOVERY_FACTORY_CMD1 :=

RECOVERY_SECUREBOOT := 0
LAYOUT := nand

# Used for NAS OTA package
NAS_ENABLE := NO

ifeq ($(USE_RTK_VOUT_UTIL), YES)
PRODUCT_PROPERTY_OVERRIDES += ro.config.enablevoututilservice=true
else
PRODUCT_PROPERTY_OVERRIDES += ro.config.enablevoututilservice=false
endif

ifeq ($(USE_RTK_AOUT_UTIL), YES)
PRODUCT_PROPERTY_OVERRIDES += ro.config.enableaoututilservice=true
else
PRODUCT_PROPERTY_OVERRIDES += ro.config.enableaoututilservice=false
endif

# Enable the following USE_RTK_HDCP1x_CONTROL := YES when HDCP is enabled.
# USE_RTK_HDCP1x_CONTROL := YES
# USE_RTK_HDCP22_CONTROL := YES
USE_RTK_VOUT_UTIL := YES
PRODUCT_PROPERTY_OVERRIDES += ro.config.enablehdmiservice=false

ifeq ($(USE_RTK_HDCP1x_CONTROL), YES)
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.config.enablehdcp=false #FIXME
else
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.config.enablehdcp=false
endif

PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.hdmi.cec.xml:system/etc/permissions/android.hardware.hdmi.cec.xml

ifeq ($(ENABLE_DRM_PLUGIN_SERVICE), true)
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=false
endif

PRODUCT_PROPERTY_OVERRIDES += ro.config.eventdelayms=0
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.storage.resizefs=0
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.abstract_socket=true
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.hdmi.device_type=4
PRODUCT_PROPERTY_OVERRIDES += ro.hdmi.cec_vendor_id=32640
PRODUCT_PROPERTY_OVERRIDES += ro.hdmi.cec_osd_name=DMP
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.sys.hdmi.addr.playback=4
PRODUCT_PROPERTY_OVERRIDES += vendor.omx.hevc_performance_mode=0
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += config.override_forced_orient=true

user_variant := $(filter user userdebug,$(TARGET_BUILD_VARIANT))
ifneq (,$(user_variant))
# ro.adb.secure is required for passing CTS
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.adb.secure=1
else
# for eng build, no auth is required
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.adb.secure=0
endif

PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.video.maxAcqCnt=3
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.hdmirx.version=1.4
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.vold.trymount=1
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.vold.checkvolume=0
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.vold.formatonerror=0
#RTK USB Type C contorller
PRODUCT_PROPERTY_OVERRIDES += sys.usb.controller="98020000.dwc3_drd"

USE_AFBC := true
# GPU AFBC
ifeq ($(USE_AFBC), true)
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.gralloc.afbc.fb=1
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.gralloc.afbc.texture=1
else
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.gralloc.afbc.fb=0
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.gralloc.afbc.texture=0
endif

###################################################
# built-in libraries
###################################################
PRODUCT_PACKAGES += audio.usb.default
PRODUCT_PACKAGES += audio.a2dp.default
PRODUCT_PACKAGES += audio.r_submix.default
PRODUCT_PACKAGES += audio.primary.thor
# PRODUCT_PACKAGES += camera.thor
# PRODUCT_PACKAGES += hdmi.thor
# PRODUCT_PACKAGES += mhl.thor
#PRODUCT_PACKAGES += rtk_cec.thor
# PRODUCT_PACKAGES += hdmi_cec.thor
# PRODUCT_PACKAGES += tv_input.thor
# PRODUCT_PACKAGES += hdcp.thor
PRODUCT_PACKAGES += libhwse.thor
PRODUCT_PACKAGES += hwcomposer.thor

PRODUCT_PACKAGES += libsrec_jni
PRODUCT_PACKAGES += libaudioroute
PRODUCT_PACKAGES += libstagefrighthw
PRODUCT_PACKAGES += libRTK_lib
#PRODUCT_PACKAGES += libRTK_OSAL_memory
#PRODUCT_PACKAGES += libRTKOMX_OSAL
PRODUCT_PACKAGES += libRTKOMX_OSAL_RTK
PRODUCT_PACKAGES += libOMX_Core
PRODUCT_PACKAGES += libjpu
PRODUCT_PACKAGES += libvpu
PRODUCT_PACKAGES += libve3
PRODUCT_PACKAGES += libOMX.realtek.video.dec
PRODUCT_PACKAGES += libOMX.realtek.video
PRODUCT_PACKAGES += libOMX.realtek.video.enc
PRODUCT_PACKAGES += libOMX.realtek.image.dec
PRODUCT_PACKAGES += libOMX.realtek.image.enc
PRODUCT_PACKAGES += libOMX.realtek.audio.dec
PRODUCT_PACKAGES += libdecve1wrap
PRODUCT_PACKAGES += libdecve2wrap
PRODUCT_PACKAGES += libdecjpgwrap
PRODUCT_PACKAGES += libencve1wrap
PRODUCT_PACKAGES += libencjpgwrap
#PRODUCT_PACKAGES += libRTKHDMIControl
PRODUCT_PACKAGES += libRTKVoutUtil
PRODUCT_PACKAGES += libRTKAoutUtil
#PRODUCT_PACKAGES += libRTKSetupClass
PRODUCT_PACKAGES += libRT_IPC
PRODUCT_PACKAGES += libRtkTranscodePlayer
PRODUCT_PACKAGES += RtkTranscodeDemo
PRODUCT_PACKAGES += libRTMediaPlayer
PRODUCT_PACKAGES += libRTDtvMediaPlayer
#PRODUCT_PACKAGES += lib_driver_cmd_rtl
PRODUCT_PACKAGES += librvsd
#PRODUCT_PACKAGES += libsettingsclient
PRODUCT_PACKAGES += libRtkRpcClientServer
PRODUCT_PACKAGES += librealtek_runtime
PRODUCT_PACKAGES += libaudioParser
PRODUCT_PACKAGES += libRtkAudioRedirect
PRODUCT_PACKAGES += libiconv
# PRODUCT_PACKAGES += librtksmb
# PRODUCT_PACKAGES += libDLNADMPClass
PRODUCT_PACKAGES += libMCPControl
PRODUCT_PACKAGES += libRTKASFExtractor
PRODUCT_PACKAGES += libRTKAIFFExtractor
PRODUCT_PACKAGES += libRTKAllocator
PRODUCT_PACKAGES += libRTKFLVExtractor

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
PRODUCT_PACKAGES += libteec
PRODUCT_PACKAGES += libTEEapi
endif

ifeq ($(USE_RTK_GPIO), true)
PRODUCT_PACKAGES += rtk_gpio.thor
PRODUCT_PACKAGES += libRTKGPIO
PRODUCT_PACKAGES += gpioproxy
PRODUCT_PROPERTY_OVERRIDES += ro.config.enablegpioservice=true
else
PRODUCT_PROPERTY_OVERRIDES += ro.config.enablegpioservice=false
endif

PRODUCT_PACKAGES += libwpa_client
PRODUCT_PACKAGES += wpa_cli
PRODUCT_PACKAGES += wpa_supplicant
PRODUCT_PACKAGES += wpa_supplicant.conf
PRODUCT_PACKAGES += rtwpriv
PRODUCT_PACKAGES += rtwpriv_org

PRODUCT_PACKAGES += libsideband
PRODUCT_PACKAGES += sideband

PRODUCT_PACKAGES += libSidebandClient

PRODUCT_PACKAGES += libRTKHWMBinderapi
PRODUCT_PACKAGES += RtkHWMBinder
#PRODUCT_PACKAGES += audio_firmware
PRODUCT_PACKAGES += libfw_socket_client

PRODUCT_PACKAGES += libtinycompress

# PRODUCT_PACKAGES += libwfdisplay
# PRODUCT_PACKAGES += rtk_wfd

###################################################
# built-in binaries
###################################################
PRODUCT_PACKAGES += coda980_dec_test
PRODUCT_PACKAGES += coda980_enc_test
PRODUCT_PACKAGES += w4_dec_test
PRODUCT_PACKAGES += vp9dec
PRODUCT_PACKAGES += vpuinit
PRODUCT_PACKAGES += jpurun

PRODUCT_PACKAGES += factory
PRODUCT_PACKAGES += multilan
PRODUCT_PACKAGES += settingsproxy

ifeq ($(TARGET_BUILD_VARIANT), eng)
PRODUCT_PACKAGES += gatord
endif

## add for Android L
#ifeq ($(BOARD_WIFI_VENDOR), realtek)
PRODUCT_PACKAGES += hostapd
PRODUCT_PACKAGES += hostapd_cli
PRODUCT_PACKAGES += wifi_auto_insmod
#endif

ifeq ($(USE_RTK_PPPOE), YES)
PRODUCT_PACKAGES += pppoe
endif

###################################################
# built-in files
###################################################
PRODUCT_PACKAGES += dhcpcd.conf

###################################################
# built-in applications
###################################################
# PRODUCT_PACKAGES += RtkLauncher2
# PRODUCT_PACKAGES += TvProvider
# PRODUCT_PACKAGES += RTKSourceIn
# PRODUCT_PACKAGES += DMR
PRODUCT_PACKAGES += RealtekGallery2
#PRODUCT_PACKAGES += RealtekInitialSettings
PRODUCT_PACKAGES += RealtekSoftwareUpdater
PRODUCT_PACKAGES += Settings
PRODUCT_PACKAGES += Music
PRODUCT_PACKAGES += MediaBrowser
# PRODUCT_PACKAGES += Browser2
# PRODUCT_PACKAGES += RealtekQuickSearchBox
# PRODUCT_PACKAGES += RTKControlPanel
#PRODUCT_PACKAGES += ApplicationsProvider
# PRODUCT_PACKAGES += ToGo
# PRODUCT_PACKAGES += RTKMiracastSink
# PRODUCT_PACKAGES += RealtekSystemUI
# PRODUCT_PACKAGES += SystemUI
PRODUCT_PACKAGES += RealtekSuspendHandler
PRODUCT_PACKAGES += RealtekPIP
PRODUCT_PACKAGES += RealtekMediaRecoderDemo
# PRODUCT_PACKAGES += RealtekFloatingWindowDemo
PRODUCT_PACKAGES += RealtekEncoder

PRODUCT_LOCALES := en_US zh_TW zh_CN

PRODUCT_COPY_FILES += device/realtek/thor/venus_IR_input.kl:system/usr/keylayout/venus_IR_input.kl
PRODUCT_COPY_FILES += device/realtek/thor/venus_IR_input.kcm:system/usr/keychars/venus_IR_input.kcm

#Wifi Module Mapper
#PRODUCT_COPY_FILES += device/realtek/thor/wifi_module_list.cfg:system/etc/wifi/wifi_module_list.cfg
PRODUCT_COPY_FILES += device/realtek/thor/wifi_module_mapper.json:system/etc/wifi/wifi_module_mapper.json

ifeq ($(ENABLE_LIGHTTPD), true)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*.html,device/realtek/www/rtCGI/html,system/data/www/htdocs)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/www/rtCGI/images,system/data/www/htdocs/images)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/www/rtCGI/css,system/data/www/htdocs/css)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/www/rtCGI/javascript,system/data/www/htdocs/javascript)
PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,device/realtek/www/rtCGI/jslib,system/data/www/htdocs/jslib)
endif

#ifeq ($(USE_LAYOUT_MEM_LOW), true)
#  PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapsize=192m
#  PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapgrowthlimit=128m
#
#  PRODUCT_PROPERTY_OVERRIDES += ro.config.low_ram=true
#  PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.jit.codecachesize=0
#else
#  PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapsize=384m
#  PRODUCT_PROPERTY_OVERRIDES += dalvik.vm.heapgrowthlimit=128m
#endif

# Include deviceCommon.mk at end of file for purpose
# If DvdPlayer exists in both common & thor directoy,
# only DvdPlayer in thor will be copied to /system/bin
include device/realtek/thor/common/deviceCommon.mk

