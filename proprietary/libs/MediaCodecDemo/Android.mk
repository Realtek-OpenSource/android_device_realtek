LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libRtkMediaCodecPlayer.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libRtkMediaCodecPlayer

include $(BUILD_PREBUILT)

##########################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkCamera
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := RtkCamera

include $(BUILD_PREBUILT)


########################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkPlayer
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := RtkPlayer

include $(BUILD_PREBUILT)

#######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := RtkTranscoder
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := RtkTranscoder

include $(BUILD_PREBUILT)

######################################################

