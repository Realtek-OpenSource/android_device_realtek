LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := fwdbg
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := fwdbg
LOCAL_PROPRIETARY_MODULE := true
LOCAL_INIT_RC := fwdbg.rc

include $(BUILD_PREBUILT)

