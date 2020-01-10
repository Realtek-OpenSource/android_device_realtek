LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := test-alloc-time
LOCAL_MODULE_TAGS := optional tests
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -DLOG_TAG=\"TestAllocTime\"
LOCAL_CFLAGS += -DMODULE_NAME=\"test-alloc-time\"

LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libRTKAllocator

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include

include $(BUILD_EXECUTABLE)
