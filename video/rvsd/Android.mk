LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

RVSD_TOP := $(LOCAL_PATH)

ifeq ($(filter kylin hercules thor hank, $(TARGET_BOARD_PLATFORM)),)
$(warning ---------- unsupported platform $(TARGET_BOARD_PLATFORM), no Android.mk under $(LOCAL_PATH) will be included ----------)
else
include $(RVSD_TOP)/$(TARGET_BOARD_PLATFORM)/Android.mk
endif
