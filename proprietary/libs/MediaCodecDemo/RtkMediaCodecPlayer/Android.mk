###################################################################
# Copyright (c) 2016 Realtek Semiconductor Corp.
#
# libRtkMediaCodecPlayer.so
###################################################################

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DRTK_PLATFORM

LOCAL_SRC_FILES := \
                RtkBase.cpp \
                BaseDecoder.cpp \
                BaseEncoder.cpp \
                VideoDecoder.cpp \
                AudioDecoder.cpp \
                VideoTranscoder.cpp \
                AudioTranscoder.cpp \
                CameraRecorder.cpp \
                AudioRecordEncoder.cpp \
                AudioRxEncoder.cpp \
                RtkMediaCodecPlayer.cpp \
                RtkMediaMuxer.cpp \
                HdmiRxInfo.cpp \
#                VideoWritebackEncoder.cpp \
#                AudioWritebackEncoder.cpp \


LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libcutils \
                       libstagefright \
                       libstagefright_foundation \
                       libgui \
                       libui \
                       libbinder \
                       libmedia \
                       libmedia_omx \
                       libmediaextractor \
                       libcamera_client \
                       libion \
                       libaudioutils \
                       libaudioclient \
                       libhidlbase \
                       libhidltransport \
                       vendor.realtek.screenrecord@1.0 \
                       vendor.realtek.audioutil@1.0 \
                       android.hidl.allocator@1.0 \
                       android.hidl.memory@1.0 \
                       libhidlmemory

LOCAL_C_INCLUDES := \
                 frameworks/av/media/libstagefright \
                 frameworks/av/media/libstagefright/include \
                 frameworks/native/include/media/hardware/ \
                 frameworks/native/include/media/openmax \
                 frameworks/av/media/libaudioclient/include \
                 device/realtek/proprietary/libs/Include \
                 device/realtek/proprietary/libs/rtk_libs/OSAL/include \
                 device/realtek/proprietary/libs/rtk_libs/OSAL/include/OSAL \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/include \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/include/xdr \
                 device/realtek/proprietary/libs/rtk_libs/common/IPC/src/xdr \
                 device/realtek/proprietary/libs/libaudioRedirect \
                 device/realtek/proprietary/libs/MediaCodecDemo/RtkMediaCodecPlayerIpc \
                 device/realtek/proprietary/libs/rtk_ion \
                 device/realtek/proprietary/libs/MediaCodecDemo \
                 device/realtek/proprietary/libs/libHDMIRxAudioSource \
                 hardware/realtek/realtek_omx/osal_rtk

#LOCAL_CFLAGS += -Wno-multichar

LOCAL_MODULE_TAGS := optional
#LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE:= libRtkMediaCodecPlayer

include $(BUILD_SHARED_LIBRARY)
