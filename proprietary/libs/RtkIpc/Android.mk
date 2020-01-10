LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libRtkIpc.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libRtkIpc
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

################################################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := seserver
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := seserver
LOCAL_PROPRIETARY_MODULE := true
LOCAL_INIT_RC := seserver.rc
include $(BUILD_PREBUILT)

########################################
