LOCAL_PATH := $(call my-dir)

DV_PREBUILTS := \
    librtk_dolby_vision \
    libcontrol_path \
    libdmfxp \
    libdv_ves_dmx \
    librpu

define define-dv-prebuilt
include $$(CLEAR_VARS)
LOCAL_MODULE := $1
LOCAL_SRC_FILES_32 := lib/$1.so
LOCAL_SRC_FILES_64 := lib64/$1.so
LOCAL_INSTALLED_MODULE_STEM := $1.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := both
LOCAL_PROPRIETARY_MODULE := true
include $$(BUILD_PREBUILT)
endef

$(foreach prebuilt,$(DV_PREBUILTS),\
    $(eval $(call define-dv-prebuilt,$(prebuilt))))

