LOCAL_PATH := $(call my-dir)

DAILYBUILD_PREBUILTS := \
    ALSADaemon \
    DvdPlayer \
    RtkKeyset \
    fb_init \
    gatord \

define define-dailybuild-prebuilt
include $$(CLEAR_VARS)
#$$(warning LOCAL_MODULE := $1)
LOCAL_MODULE := $1
LOCAL_SRC_FILES := package5/system/bin/$1
LOCAL_INIT_RC := package5/system/bin/$1.rc
LOCAL_INSTALLED_MODULE_STEM := $1
#LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional
#LOCAL_MULTILIB := both
LOCAL_PROPRIETARY_MODULE := true
include $$(BUILD_PREBUILT)
endef

$(foreach prebuilt,$(DAILYBUILD_PREBUILTS),\
    $(eval $(call define-dailybuild-prebuilt,$(prebuilt))))

