LOCAL_PATH := $(call my-dir)
#BUILD_AUDIOREDIRECTOR := true

include $(CLEAR_VARS)

LOCAL_SRC_FILES := AudioRedirectService.cpp
LOCAL_SRC_FILES += RtkAudioRedirect.cpp
LOCAL_SRC_FILES += RtkAudioCap.cpp
LOCAL_SRC_FILES += RtkAudioRender.cpp
LOCAL_SRC_FILES += RtkBypassRender.cpp

LOCAL_SHARED_LIBRARIES := libstagefright
LOCAL_SHARED_LIBRARIES += libstagefright_foundation
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES += libmedia
LOCAL_SHARED_LIBRARIES += libtinyalsa
LOCAL_SHARED_LIBRARIES += libaudioutils
LOCAL_SHARED_LIBRARIES += libaudioclient
LOCAL_SHARED_LIBRARIES += libhidlbase
LOCAL_SHARED_LIBRARIES += libhidltransport
LOCAL_SHARED_LIBRARIES += vendor.realtek.audioredirectutil@1.0
LOCAL_SHARED_LIBRARIES += android.hidl.memory@1.0
LOCAL_SHARED_LIBRARIES += libhidlmemory
LOCAL_SHARED_LIBRARIES += android.hidl.allocator@1.0

LOCAL_C_INCLUDES := frameworks/av/media/libstagefright
#LOCAL_C_INCLUDES += frameworks/native/include/media/openmax
LOCAL_C_INCLUDES += system/core/include/cutils
LOCAL_C_INCLUDES += hardware/realtek/realtek_omx/osal_rtk
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include/xdr
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/src/xdr
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/OSAL/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/OSAL/include/OSAL
LOCAL_C_INCLUDES += external/tinyalsa/include
LOCAL_C_INCLUDES += $(call include-path-for, audio-utils)
LOCAL_C_INCLUDES += system/core/libion/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion

LOCAL_CFLAGS += -Wno-multichar

LOCAL_MODULE_TAGS := optional
#LOCAL_PROPRIETARY_MODULE := true

ifeq ($(BUILD_AUDIOREDIRECTOR),true)
LOCAL_SRC_FILES += main.cpp
LOCAL_MODULE := AudioRedirector
LOCAL_INIT_RC := AudioRedirector.rc
include $(BUILD_EXECUTABLE)
else
LOCAL_MODULE:= libRtkAudioRedirect
include $(BUILD_STATIC_LIBRARY)
endif


###################################################################################################

#include $(CLEAR_VARS)
#
#LOCAL_SRC_FILES := main.cpp
#LOCAL_CFLAGS := -Werror -Wall
#LOCAL_SHARED_LIBRARIES := liblog libbinder libutils libRtkAudioRedirect
#LOCAL_MODULE := AudioRedirector
#LOCAL_PROPRIETARY_MODULE := true
#LOCAL_32_BIT_ONLY := true
#LOCAL_INIT_RC := AudioRedirector.rc
#
#include $(BUILD_EXECUTABLE)

