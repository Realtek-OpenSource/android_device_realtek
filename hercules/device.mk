# Set this to false will cause compilation error
USE_RT_MEDIA_PLAYER := true

USE_SETTINGS_SERVICE := true
# For DRM code flow
ENABLE_DRM_PLUGIN_SERVICE := true
# For TEE OS, video used physical Address
ifeq ($(ENABLE_TEE_DRM_FLOW),)
	ENABLE_TEE_DRM_FLOW := false
endif

ifeq ($(USE_RTK_HDCP1x_CONTROL),)
	# When not defined, the default is NO
	# ex : export USE_RTK_HDCP1x_CONTROL=YES && build android
	USE_RTK_HDCP1x_CONTROL := NO
endif
ifeq ($(USE_RTK_HDCP22_CONTROL),)
	# When not defined, the default is NO
	# ex : export USE_RTK_HDCP22_CONTROL=YES && build android
	USE_RTK_HDCP22_CONTROL := NO
endif
ifeq ($(USE_RTK_HDCP_TEE),)
	USE_RTK_HDCP_TEE := NO
endif
USE_RTK_VOUT_UTIL := YES
USE_RTK_AOUT_UTIL := YES
USE_XML_AUDIO_POLICY_CONF := 1
USE_RTK_PPPOE := YES
USE_RTK_OPENWRT := YES

# used for recovery mode - apply for factory update
# example: RECOVERY_FACTORY_CMD0 := rm factory_test.txt
RECOVERY_FACTORY_CMD0 := cd ../../;cp -rf tmp/install_factory/* tmp/factory/;
RECOVERY_FACTORY_CMD1 :=
RECOVERY_SECUREBOOT := 0
LAYOUT := emmc
DTB_ENC := false

# Used for NAS OTA package
NAS_ENABLE := NO

# Used for XEN OTA package
XEN_ENABLE := NO

# Enable the following USE_RTK_HDCP1x_CONTROL := YES when HDCP is enabled.
#PRODUCT_PACKAGES += libteec
#USE_RTK_HDCP1x_CONTROL := YES
#USE_RTK_HDCP22_CONTROL := YES
#USE_RTK_HDCP_TEE := YES
ifeq ($(DISABLE_RTK_GUI), YES)
PRODUCT_PACKAGES += \
    android.hardware.graphics.allocator@2.0-impl \
    android.hardware.graphics.allocator@2.0-service
else
PRODUCT_PACKAGES += libgui_rtk
PRODUCT_PACKAGES += libsigchain_rtk
PRODUCT_PACKAGES += libsideband
PRODUCT_PACKAGES += sideband
PRODUCT_PACKAGES += libSidebandClient
PRODUCT_PACKAGES += librvsd
PRODUCT_PACKAGES += libRTMediaPlayer
# Rtk RVSD HAL
PRODUCT_PACKAGES += \
    vendor.realtek.rvsd@1.0-impl \
    vendor.realtek.rvsd@1.0-service
PRODUCT_PACKAGES += \
    vendor.realtek.allocator@1.0-impl \
    vendor.realtek.allocator@1.0-service
endif

ifeq ($(USE_RTK_HDCP1x_CONTROL), YES)
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.config.enablehdcp=true
else
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.config.enablehdcp=false
endif

ifeq ($(ENABLE_DRM_PLUGIN_SERVICE), true)
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=false
endif

$(warning config ENABLE_LOW_RAM=$(ENABLE_LOW_RAM))

user_variant := $(filter user userdebug,$(TARGET_BUILD_VARIANT))
ifneq (,$(user_variant))
# ro.adb.secure is required for passing CTS
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.adb.secure=1
else
# for eng build, no auth is required
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.adb.secure=0
endif

PRODUCT_PROPERTY_OVERRIDES += \
	persist.vendor.storage.resizefs=0 \
	persist.vendor.abstract_socket=true \
	ro.vendor.hdmi.cec_vendor_id=32640 \
	ro.vendor.hdmi.cec_osd_name=DMP \
	vendor.omx.hevc_performance_mode=0 \
	persist.vendor.rtk.performancemode=0 \
	persist.vendor.rtk.video.maxAcqCnt=1 \
	persist.vendor.rtk.hdmirx.version=1.4 \
	persist.vendor.rtk.vold.trymount=1 \
	persist.vendor.rtk.vold.checkvolume=0 \
	persist.vendor.rtk.vold.formatonerror=0 \
	# For Audio Secure Path using native_handle_t
	media.mediadrmservice.enable=true \
	ro.boot.wificountrycode=US \
	# USE S3 Suspend as default
	persist.vendor.suspend.mode=suspend

PRODUCT_SYSTEM_DEFAULT_PROPERTIES += \
	ro.config.media_vol_default=8 \
	ro.hdmi.device_type=4 \
	persist.sys.hdmi.addr.playback=4 \
	persist.sys.hdmi.keep_awake=false \
	config.override_forced_orient=true

# hercules supports Dovi
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.rtk.dovi.support=1
PRODUCT_PROPERTY_OVERRIDES += ro.vendor.rtk.hdcp.storage=/data/vendor/hdcp

###################################################
# built-in libraries
###################################################
PRODUCT_PACKAGES += audio.usb.default
PRODUCT_PACKAGES += audio.a2dp.default
PRODUCT_PACKAGES += audio.r_submix.default
PRODUCT_PACKAGES += audio.primary.hercules
PRODUCT_PACKAGES += hdmi.hercules
PRODUCT_PACKAGES += dptx.hercules
PRODUCT_PACKAGES += hdcp.hercules
PRODUCT_PACKAGES += libhwse.hercules

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
PRODUCT_PACKAGES += libOMX.realtek.video.dec.dovi
PRODUCT_PACKAGES += libOMX.realtek.audio.dec
#PRODUCT_PACKAGES += libRTKHDMIControl
PRODUCT_PACKAGES += libRTKVoutUtil
PRODUCT_PACKAGES += libRTKAoutUtil
PRODUCT_PACKAGES += libAudioUtil_internal
#PRODUCT_PACKAGES += libRTKSetupClass
PRODUCT_PACKAGES += libRT_IPC
PRODUCT_PACKAGES += libRtkTranscodePlayer
PRODUCT_PACKAGES += libRtkMediaCodecPlayer
PRODUCT_PACKAGES += libHDMIRxAudioSource
PRODUCT_PACKAGES += libRTDtvMediaPlayer
PRODUCT_PACKAGES += librvsd_sp
#PRODUCT_PACKAGES += libsettingsclient
PRODUCT_PACKAGES += libRtkRpcClientServer
PRODUCT_PACKAGES += librealtek_jni
PRODUCT_PACKAGES += librealtek_runtime
PRODUCT_PACKAGES += libaudioParser
PRODUCT_PACKAGES += libRtkAudioRedirect
PRODUCT_PACKAGES += libAudioCapturer
PRODUCT_PACKAGES += libiconv
PRODUCT_PACKAGES += librtksmb
PRODUCT_PACKAGES += libDLNADMPClass
PRODUCT_PACKAGES += libDLNADMRClass
PRODUCT_PACKAGES += libMCPControl
PRODUCT_PACKAGES += libRTKASFExtractor
PRODUCT_PACKAGES += libRTKAIFFExtractor
PRODUCT_PACKAGES += libRTKAllocator
PRODUCT_PACKAGES += libRTKFLVExtractor
PRODUCT_PACKAGES += libRTKDSDExtractor
PRODUCT_PACKAGES += libRTKAPEExtractor
PRODUCT_PACKAGES += vr_hwc

PRODUCT_PACKAGES += RtkDisplayDeviceCtrl
PRODUCT_PACKAGES += librtk-display_ctrl_jni

PRODUCT_PACKAGES += fs_config_files

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
PRODUCT_PACKAGES += libteec
PRODUCT_PACKAGES += libTEEapi
endif

PRODUCT_PACKAGES += rtwpriv
PRODUCT_PACKAGES += rtwpriv_org

#Wifi
PRODUCT_PACKAGES += \
 libwpa_client \
 wpa_supplicant \
 hostapd \
 wificond \
 wifilogd \
 wpa_supplicant.conf \
 hostapd.conf \
 libwifi-hal \
 android.hardware.wifi.supplicant@1.0-service \
 android.hardware.wifi.supplicant@1.1-service \
 android.hardware.wifi@1.0-service \
 android.hardware.wifi@1.0-service-lib \
 android.hardware.wifi.hostapd@1.0-service

PRODUCT_PACKAGES += DVControlPath_server
PRODUCT_PACKAGES += librtk_dolby_vision
PRODUCT_PACKAGES += libcontrol_path
PRODUCT_PACKAGES += libdmfxp
PRODUCT_PACKAGES += libdv_ves_dmx
PRODUCT_PACKAGES += librpu

PRODUCT_PACKAGES += libRTKHWMBinderapi
PRODUCT_PACKAGES += RtkHWMBinder
#PRODUCT_PACKAGES += audio_firmware
PRODUCT_PACKAGES += libfw_socket_client

PRODUCT_PACKAGES += libwfdisplay
PRODUCT_PACKAGES += rtk_wfd

ifeq ($(ENABLE_VMX_CA_CONTROL), YES)
PRODUCT_PACKAGES += librtksdk
PRODUCT_PACKAGES += librtksdk_jni
PRODUCT_PACKAGES += librtkALP
PRODUCT_PACKAGES += libvmxrelease
PRODUCT_PACKAGES += libvmxca
PRODUCT_PACKAGES += libvmxcatest
PRODUCT_PACKAGES += libvmxca_jni
PRODUCT_PACKAGES += librtksocket
endif
###################################################
# built-in binaries
###################################################
ifeq ($(ENABLE_VMX_CA_CONTROL), YES)
PRODUCT_PACKAGES += RTK_MIDDLEWARE_TEST_ANDROID
PRODUCT_PACKAGES += RTK_VMX_TEST
PRODUCT_PACKAGES += RTK_VMX_TEST_CNT
endif
PRODUCT_PACKAGES += coda980_dec_test
PRODUCT_PACKAGES += coda980_enc_test
PRODUCT_PACKAGES += w4_dec_test
PRODUCT_PACKAGES += vp9dec
PRODUCT_PACKAGES += vpuinit
PRODUCT_PACKAGES += jpurun

PRODUCT_PACKAGES += factory
PRODUCT_PACKAGES += multilan

#PRODUCT_PACKAGES += rvsd
PRODUCT_PACKAGES += settingsproxy
#PRODUCT_PACKAGES += AudioUtilServer
#PRODUCT_PACKAGES += VideoUtilServer
#PRODUCT_PACKAGES += recordbufferserver
PRODUCT_PACKAGES += seserver
#PRODUCT_PACKAGES += mdserver
#PRODUCT_PACKAGES += rtktranscodeplayerserve
#PRODUCT_PACKAGES += AudioRedirector

ifeq ($(TARGET_BUILD_VARIANT), eng)
PRODUCT_PACKAGES += gatord
endif

## add for Android L
#ifeq ($(BOARD_WIFI_VENDOR), realtek)
PRODUCT_PACKAGES += hostapd
PRODUCT_PACKAGES += hostapd_cli
#endif

ifeq ($(USE_RTK_PPPOE), YES)
PRODUCT_PACKAGES += pppoe
PRODUCT_PACKAGES += com.android.server.pppoe
endif

ifeq ($(USE_RTK_OPENWRT), YES)
PRODUCT_PACKAGES += com.rtk.net.ubusrpc
endif

PRODUCT_PACKAGES += RtkPlayer
PRODUCT_PACKAGES += RtkTranscoder
PRODUCT_PACKAGES += RtkCamera
PRODUCT_PACKAGES += RtkScreenRecorder

PRODUCT_PACKAGES += fwdbg

###################################################
# built-in host binaries
###################################################
PRODUCT_PACKAGES += mkbootimg

###################################################
# built-in files
###################################################
PRODUCT_PACKAGES += dhcpcd.conf

###################################################
# built-in applications
###################################################
PRODUCT_PACKAGES += RealtekGallery2
#PRODUCT_PACKAGES += RealtekInitialSettings
PRODUCT_PACKAGES += RealtekSoftwareUpdater
PRODUCT_PACKAGES += MediaBrowser
PRODUCT_PACKAGES += Browser2
PRODUCT_PACKAGES += Music
#PRODUCT_PACKAGES += RealtekQuickSearchBox
PRODUCT_PACKAGES += RTKControlPanel
#PRODUCT_PACKAGES += ApplicationsProvider
PRODUCT_PACKAGES += RealtekSystemUI
#PRODUCT_PACKAGES += SystemUI
PRODUCT_PACKAGES += RealtekSuspendHandler
PRODUCT_PACKAGES += RealtekPIP
#PRODUCT_PACKAGES += RealtekMediaRecoderDemo
#PRODUCT_PACKAGES += RealtekFloatingWindowDemo
#PRODUCT_PACKAGES += RxHdcp
PRODUCT_PACKAGES += Contacts
PRODUCT_PACKAGES += DeskClock
PRODUCT_PACKAGES += DownloadProvider
PRODUCT_PACKAGES += DownloadProviderUi
PRODUCT_PACKAGES += MediaProvider
PRODUCT_PACKAGES += RtkPartnerInterface

# Don't build these apps to save memory
ifneq ($(ENABLE_LOW_RAM), true)
PRODUCT_PACKAGES += DMR
PRODUCT_PACKAGES += RTKMiracastSink
PRODUCT_PACKAGES += RealtekEncoder
endif

# Hercules has no HDMI Rx, disable related apps
#PRODUCT_PACKAGES += RTKSourceIn
#PRODUCT_PACKAGES += RealtekHDMIRxTvInput
#PRODUCT_PACKAGES += RealtekTVDemo
PRODUCT_PACKAGES += TvProvider

ifeq ($(USE_VMX_DEMO_APK), true)
PRODUCT_PACKAGES += VmxRtkDemo
endif

# For Widevine
PRODUCT_PACKAGES += libwvhidl
PRODUCT_PACKAGES += liboemcrypto

# add HDMI/DPTX libraries
PRODUCT_PACKAGES += libHDMIServiceCore libHDMILib
#PRODUCT_PACKAGES += libDPTXServiceCore libDPTxLib

#PRODUCT_LOCALES := en_US zh_TW zh_CN

# add verity dependencies
$(call inherit-product, build/target/product/verity.mk)
PRODUCT_SUPPORTS_BOOT_SIGNER := false
PRODUCT_SYSTEM_VERITY_PARTITION := /dev/block/mmcblk0p1

PRODUCT_PACKAGES += \
    slideshow \
    verity_warning_images

# seamless update

PRODUCT_PACKAGES += \
    bootctrl.hercules
PRODUCT_PACKAGES_DEBUG += \
    bootctl

PRODUCT_PACKAGES += \
    android.hardware.boot@1.0-impl \
    android.hardware.boot@1.0-service

ifeq ($(ENABLE_AB_SYSTEM), NO)
AB_OTA_UPDATER := false
else
AB_OTA_UPDATER := true
#BOARD_PREBUILT_BL31 := device/realtek/hercules/rtkimages/bl31.bin
#BOARD_PREBUILT_TEEOS := device/realtek/hercules/rtkimages/tee.bin
#BOARD_PREBUILT_LK   := device/realtek/hercules/rtkimages/lk.bin
#BOARD_PREBUILT_DTBIMAGE := device/realtek/hercules/rtkimages/android.emmc.dtb
#BOARD_PREBUILT_RESCUEDTBIMAGE := device/realtek/hercules/rtkimages/rescue.emmc.dtb
#BOARD_PREBUILT_AUDIOFW := device/realtek/hercules/rtkimages/bluecore.audio
#BOARD_PREBUILT_AUDIOFW := device/realtek/hercules/rtkimages/bluecore.audio.enc.A00
#BOARD_PREBUILT_KERNELIMAGE:= device/realtek/hercules/rtkimages/emmc.uImage
#BOARD_PREBUILT_ROOTFS := device/realtek/hercules/rtkimages/android.root.emmc.cpio.gz_pad.img
#BOARD_PREBUILT_RESCUEROOTFS := device/realtek/hercules/rtkimages/rescue.root.emmc.cpio.gz_pad.img

AB_OTA_PARTITIONS := system vendor

ifdef BOARD_PREBUILT_BL31
AB_OTA_PARTITIONS += BL31
endif

ifdef BOARD_PREBUILT_TEEOS
AB_OTA_PARTITIONS += tee
endif

ifdef BOARD_PREBUILT_LK
AB_OTA_PARTITIONS += lk
endif

ifdef BOARD_PREBUILT_DTBIMAGE
AB_OTA_PARTITIONS += kernelDT
endif

ifdef BOARD_PREBUILT_RESCUEDTBIMAGE
AB_OTA_PARTITIONS += rescueDT
endif

ifdef BOARD_PREBUILT_AUDIOFW
AB_OTA_PARTITIONS += audioKernel
endif

ifdef BOARD_PREBUILT_KERNELIMAGE
AB_OTA_PARTITIONS += linuxKernel
endif

ifdef BOARD_PREBUILT_ROOTFS
AB_OTA_PARTITIONS += kernelRootFS
endif

ifdef BOARD_PREBUILT_RESCUEROOTFS
AB_OTA_PARTITIONS += rescueRootFS
endif
endif

PRODUCT_PACKAGES += \
  update_engine \
  update_verifier
PRODUCT_PACKAGES_DEBUG += update_engine_client

ifeq ($(ENABLE_AB_SYSTEM), YES)
#indicate cp odex from system_b to data
PRODUCT_PROPERTY_OVERRIDES += ro.cp_system_other_odex=1

#called by cppreopts.rc
PRODUCT_PACKAGES += cppreopts.sh

PRODUCT_PACKAGES += otapreopt_script

PRODUCT_PACKAGES += write_fwtable

#POSTINSTALL_OPTIONAL_vendor == false means update fwtable is a compusolry
#portion of ota update.If failed,the whole update was marked fail too
AB_OTA_POSTINSTALL_CONFIG += \
  RUN_POSTINSTALL_system=true \
  POSTINSTALL_PATH_system=usr/bin/postinst \
  FILESYSTEM_TYPE_system=ext4

PRODUCT_PACKAGES += otapreopt_script

AB_OTA_POSTINSTALL_CONFIG += \
    RUN_POSTINSTALL_system=true \
    POSTINSTALL_PATH_system=system/bin/otapreopt_script \
    FILESYSTEM_TYPE_system=ext4 \
    POSTINSTALL_OPTIONAL_system=true

BOARD_USES_SYSTEM_OTHER_ODEX := true
endif

# Gralloc HAL
PRODUCT_PACKAGES += \
    hwcomposer.hercules \
    android.hardware.graphics.mapper@2.0-impl-2.1 \
    android.hardware.graphics.composer@2.2-impl \
    android.hardware.graphics.composer@2.2-service

# Audio HAL
PRODUCT_PACKAGES += \
    android.hardware.audio@4.0-impl \
    android.hardware.audio.effect@4.0-impl \
    android.hardware.audio@2.0-service

# Health HAL
PRODUCT_PACKAGES += android.hardware.health@2.0-service.override
DEVICE_FRAMEWORK_MANIFEST_FILE += system/libhidl/vintfdata/manifest_healthd_exclude.xml
PRODUCT_PACKAGES += android.hardware.health@2.0-service

# Keymaster HAL
PRODUCT_PACKAGES += \
    android.hardware.keymaster@3.0-impl \
    android.hardware.keymaster@3.0-service 
ifeq ($(ENABLE_TEE_DRM_FLOW),true)
PRODUCT_PACKAGES +=  keystore.hercules 
endif

# Gatekeeper HAL
PRODUCT_PACKAGES += \
    gatekeeper.hercules \
    android.hardware.gatekeeper@1.0-impl \
    android.hardware.gatekeeper@1.0-service \

# Dumpstate HAL
PRODUCT_PACKAGES += \
    android.hardware.dumpstate@1.0-service

# Memtrack HAL
PRODUCT_PACKAGES += \
	android.hardware.memtrack@1.0-impl \
	android.hardware.memtrack@1.0-service \
	memtrack.hercules

# TV Input HAL
#PRODUCT_PACKAGES += \
#    tv_input.hercules \
#    android.hardware.tv.input@1.0-impl \
#    android.hardware.tv.input@1.0-service

# HDMI CEC HAL
PRODUCT_PACKAGES += \
    hdmi_cec.hercules \
    android.hardware.tv.cec@1.0-impl \
    android.hardware.tv.cec@1.0-service

# Camera
PRODUCT_PACKAGES += \
    camera.device@1.0-impl \
    camera.device@3.2-impl \
    camera.device@3.3-impl \
    camera.device@3.4-impl \
    camera.device@3.4-external-impl \
    android.hardware.camera.provider@2.4-impl \
    android.hardware.camera.provider@2.4-external-service
#       camera.hercules
##       camera.arm

# DRM
PRODUCT_PACKAGES += \
    android.hardware.drm@1.0-impl \
    android.hardware.drm@1.0-service \
	android.hardware.drm@1.1-service.widevine \
	android.hardware.drm@1.1-service.clearkey

# Power HAL
PRODUCT_PACKAGES += \
    android.hardware.power@1.0-service.rtk

# Rtk AudioRedirect HAL
#PRODUCT_PACKAGES += \
    vendor.realtek.audioredirect@1.0-impl \
    vendor.realtek.audioredirect@1.0-service

# Rtk AudioUtil HAL
PRODUCT_PACKAGES += \
    vendor.realtek.audioutil@1.0-impl \
    vendor.realtek.audioutil@1.0-service

# Rtk VoutUtil HAL
PRODUCT_PACKAGES += \
    vendor.realtek.voututil@1.0-impl \
    vendor.realtek.voututil@1.0-service

# Rtk HdmiUtil HAL
PRODUCT_PACKAGES += \
       vendor.realtek.hdmiutil.provider@1.0-impl \
       vendor.realtek.hdmiutil.provider@1.0-service


#PRODUCT_PACKAGES += \
       vendor.realtek.dptxutil.provider@1.0-impl \
       vendor.realtek.dptxutil.provider@1.0-service

# Rtk ScreenRecord HAL
#PRODUCT_PACKAGES += \
#       vendor.realtek.screenrecord@1.0-impl \
#       vendor.realtek.screenrecord@1.0-service

# Rtk FactoryUtil HAL
#PRODUCT_PACKAGES += \
#    vendor.realtek.factoryutil@1.0-impl \
#    vendor.realtek.factoryutil@1.0-service

# SoundTrigger HAL
#PRODUCT_PACKAGES += \
#	android.hardware.soundtrigger@2.0-impl \

# Thermal HAL
PRODUCT_PACKAGES += \
	thermal.hercules \
	android.hardware.thermal@1.0-service \
	android.hardware.thermal@1.0-impl

# USB HAL
# 1.0
#PRODUCT_PACKAGES += \
#	android.hardware.usb@1.0-service
#USB Hal 1.1
PRODUCT_PACKAGES += \
	android.hardware.usb@1.1-service.rtk
# Wi-Fi
#PRODUCT_PACKAGES += \
#    android.hardware.wifi@1.0-service \
#    libwpa_client \
#    hostapd \
#    wificond \
#    wifilogd \
#    wpa_supplicant \
#    wpa_supplicant.conf

# VTS
PRODUCT_PACKAGES += libxml2

# AudioRedirectUtil HAL
PRODUCT_PACKAGES += \
       vendor.realtek.audioredirectutil@1.0-impl \
       vendor.realtek.audioredirectutil@1.0-service

# Set Language via HDMI-CEC
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.hdmi.set_menu_language=true

# Include deviceCommon.mk at end of file for purpose
# If DvdPlayer exists in both common & hercules directoy,
# only DvdPlayer in hercules will be copied to /system/bin
include device/realtek/hercules/common/deviceCommon.mk

PRODUCT_PACKAGES += librtk-mediaplayer
PRODUCT_PACKAGES += vendor.realtek.rvsd@1.0
PRODUCT_PACKAGES += vendor.realtek.voututil@1.0
PRODUCT_PACKAGES += libkeystore-engine-wifi-hidl
PRODUCT_PACKAGES += libkeystore-wifi-hidl
PRODUCT_PACKAGES += libsync_rtk
PRODUCT_PACKAGES += libIDVControlPathService
PRODUCT_PACKAGES += libRealtekDVControlPathService
PRODUCT_PACKAGES += libRtkHWMBinderservice
PRODUCT_PACKAGES += libRtkHWMBinder
PRODUCT_PACKAGES += librtk_ion
PRODUCT_PACKAGES += libtinycompress
PRODUCT_PACKAGES += libVoutUtil_internal
PRODUCT_PACKAGES += keystore.hercules
PRODUCT_PACKAGES += vendor.realtek.rvsd@1.0-service
ENABLE_TEE_DRM_FLOW := true
PRODUCT_PACKAGES += test
