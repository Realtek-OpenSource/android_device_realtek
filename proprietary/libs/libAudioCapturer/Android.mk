###################################################################
# Copyright (c) 2019 Realtek Semiconductor Corp.
###################################################################

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DRTK_PLATFORM
LOCAL_CFLAGS += -DRX_RPC

LOCAL_SRC_FILES := AudioCapturer.cpp \

LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libcutils \
                       libRTKOMX_OSAL_RTK \
                       libRTK_lib \
                       libion \
                       librtk_ion \
                       libhardware_legacy \
                       libhardware \
                       libstagefright_foundation \
                       libsysutils

LOCAL_C_INCLUDES := \
                 device/realtek/proprietary/libs/Include \
                 device/realtek/proprietary/libs/rtk_libs/OSAL/include \
                 device/realtek/proprietary/libs/rtk_libs/OSAL/include/OSAL \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/include \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/include/xdr \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/src/xdr \
                 device/realtek/proprietary/libs/libaudioRedirect \
                 device/realtek/proprietary/libs/rtk_ion \
                 hardware/realtek/realtek_omx/osal_rtk \
                 frameworks/av/media/libstagefright/include \
                 frameworks/av/media/libmedia/include \
                 frameworks/av/media/libmedia/include/ \
                 hardware/libhardware/include

#LOCAL_CFLAGS += -Wno-multichar

LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE:= libAudioCapturer

include $(BUILD_STATIC_LIBRARY)
