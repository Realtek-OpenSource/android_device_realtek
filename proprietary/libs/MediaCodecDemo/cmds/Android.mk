###################################################################
# Copyright (c) 2016 Realtek Semiconductor Corp.
###################################################################


LOCAL_PATH:= $(call my-dir)

###################################################################
#
#               RtkCamera
#
###################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkCamera.cpp

LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libbinder \
                       libcamera_client \
                       libgui \
                       libui \
                       libmedia \
                       libstagefright \
                       libstagefright_foundation \
                       libaudioclient \
                       libRtkMediaCodecPlayer

LOCAL_C_INCLUDES := \
                 system/core/include/cutils \
                 device/realtek/proprietary/libs/MediaCodecDemo \
                 frameworks/av/include \
                 frameworks/av/media/libstagefright \
                 frameworks/native/include/media/openmax \
                 frameworks/native/include \
                 frameworks/av/media/libaudioclient/include

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := RtkCamera

include $(BUILD_EXECUTABLE)


####################################################################
##
##               RtkScreenRecorder
##
####################################################################
#include $(CLEAR_VARS)
#
#LOCAL_SRC_FILES := RtkScreenRecorder.cpp
#
#LOCAL_SHARED_LIBRARIES := \
#                       liblog \
#                       libutils \
#                       libbinder \
#                       libgui \
#                       libui \
#                       libmedia \
#                       libstagefright \
#                       libstagefright_foundation \
#                       libRtkMediaCodecPlayer
#
#LOCAL_C_INCLUDES := \
#                 system/core/include/cutils \
#                 device/realtek/proprietary/libs/MediaCodecDemo \
#                 frameworks/av/include \
#                 frameworks/av/media/libstagefright \
#                 frameworks/native/include/media/openmax \
#                 frameworks/native/include
#
#ifeq ($(SERVICE_MODE), true)
#LOCAL_CFLAGS += -DUSE_SERVICE_MODE
#LOCAL_SHARED_LIBRARIES += libRtkMediaCodecPlayerService
#endif
#
#LOCAL_MODULE_TAGS := optional
##LOCAL_PROPRIETARY_MODULE := true
#
#LOCAL_MODULE := RtkScreenRecorder
#
#include $(BUILD_EXECUTABLE)
#
#
###################################################################
#
#               RtkPlayer
#
###################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkPlayer.cpp

LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libbinder \
                       libgui \
                       libui \
                       libmedia \
                       libstagefright \
                       libstagefright_foundation \
                       libRtkMediaCodecPlayer

LOCAL_C_INCLUDES := \
                 system/core/include/cutils \
                 device/realtek/proprietary/libs/MediaCodecDemo \
                 frameworks/av/include \
                 frameworks/av/media/libstagefright \
                 frameworks/native/include/media/openmax \
                 frameworks/native/include
                 
LOCAL_MODULE_TAGS := optional
#LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE := RtkPlayer

include $(BUILD_EXECUTABLE)


###################################################################
#
#               RtkTranscoder
#
###################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkTranscoder.cpp

LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libbinder \
                       libgui \
                       libui \
                       libmedia \
                       libstagefright \
                       libstagefright_foundation \
                       libRtkMediaCodecPlayer

LOCAL_C_INCLUDES := \
                 system/core/include/cutils \
                 device/realtek/proprietary/libs/MediaCodecDemo \
                 frameworks/av/include \
                 frameworks/av/media/libstagefright \
                 frameworks/native/include/media/openmax \
                 frameworks/native/include

LOCAL_MODULE_TAGS := optional
#LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE := RtkTranscoder

include $(BUILD_EXECUTABLE)

