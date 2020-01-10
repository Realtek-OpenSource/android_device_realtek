LOCAL_PATH := $(call my-dir)

#### 32 bit ####
include $(CLEAR_VARS)
OS_BIT := 32
LOCAL_MULTILIB := $(OS_BIT)
LOCAL_MODULE := RTKRevision_$(OS_BIT)
LOCAL_MODULE_TAGS := optional tests
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -DLOG_TAG=\"RTKRevision_$(OS_BIT)\"
LOCAL_CFLAGS += -DMODULE_NAME=\"RTKRevision_$(OS_BIT)\"
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SRC_FILES := src/main.cpp

LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/bin/$(LOCAL_MODULE) device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/bin

include $(BUILD_EXECUTABLE)

#### 64 bit ####
include $(CLEAR_VARS)
OS_BIT := 64
LOCAL_MULTILIB := $(OS_BIT)
LOCAL_MODULE := RTKRevision_$(OS_BIT)
LOCAL_MODULE_TAGS := optional tests
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -DLOG_TAG=\"RTKRevision_$(OS_BIT)\"
LOCAL_CFLAGS += -DMODULE_NAME=\"RTKRevision_$(OS_BIT)\"
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SRC_FILES := src/main.cpp

LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/bin/$(LOCAL_MODULE) device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/bin

include $(BUILD_EXECUTABLE)
