LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libsideband.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES 
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libsideband
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

######################################################### 

#########################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := sideband
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := sideband
LOCAL_INIT_RC := sideband.rc
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

########################################################

