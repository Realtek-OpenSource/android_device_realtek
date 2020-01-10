LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULES_TAGS := optional
LOCAL_SRC_FILES := RtkHWMBinder
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE := RtkHWMBinder
LOCAL_INIT_RC := RtkHWMBinder.rc

LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
###################################

