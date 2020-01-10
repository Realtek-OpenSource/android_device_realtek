LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libIDVControlPathService.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libIDVControlPathService
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

#######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libRealtekDVControlPathService.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libRealtekDVControlPathService
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := DVControlPath_server
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := DVControlPath_server
LOCAL_INIT_RC := DVControlPathService-android8.rc
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

#################################################

