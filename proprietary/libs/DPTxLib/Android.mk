LOCAL_PATH:= $(call my-dir)

#######################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libDPTxLib.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
#LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libDPTxLib

include $(BUILD_PREBUILT)
######################################################
