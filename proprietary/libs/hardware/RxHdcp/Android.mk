LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := RxHdcp
LOCAL_INIT_RC := RxHdcp.rc
LOCAL_PROPRIETARY_MODULE := true

LOCAL_SRC_FILES += RxHdcp.cpp

LOCAL_C_INCLUDES += device/realtek/proprietary/libs/RtkHWMBinderapi

LOCAL_SHARED_LIBRARIES += libRTKHWMBinderapi

LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils

#include $(BUILD_EXECUTABLE)
