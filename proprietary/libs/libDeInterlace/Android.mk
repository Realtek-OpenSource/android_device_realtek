LOCAL_PATH:= $(call my-dir)

################################################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES += VoDeInterlaceHelper.cpp
LOCAL_SRC_FILES += DeInterlaceCallback.cpp

LOCAL_C_INCLUDES += frameworks/base/include/ui
LOCAL_C_INCLUDES += frameworks/base/include/utils
LOCAL_C_INCLUDES += frameworks/av/include
LOCAL_C_INCLUDES += frameworks/av/include/media/stagefright
LOCAL_C_INCLUDES += frameworks/native/include
LOCAL_C_INCLUDES += frameworks/native/include/media/openmax
LOCAL_C_INCLUDES += frameworks/native/include/media/hardware
LOCAL_C_INCLUDES += frameworks/native/libs/nativewindow/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
#LOCAL_C_INCLUDES += hardware/libhardware/include
LOCAL_C_INCLUDES += system/core/include
LOCAL_C_INCLUDES += system/core/libsync
LOCAL_C_INCLUDES += system/core/libcutils/include

#LOCAL_C_INCLUDES += frameworks/native/libs/gui
#LOCAL_C_INCLUDES += frameworks/native/libs/gui/include

LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libRTKAllocator
LOCAL_SHARED_LIBRARIES += libRTK_lib

LOCAL_32_BIT_ONLY := true

LOCAL_CFLAGS += -DUSE_RT_ION

LOCAL_MODULE:= libDeInterlace
LOCAL_MODULE_TAGS:= optional
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)

################################################################################

