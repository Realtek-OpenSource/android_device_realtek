ifeq ($(TARGET_BOARD_PLATFORM),hercules)

LOCAL_PATH := $(call my-dir)

PREBUILT_LIBS := \
    hw/gralloc.hercules.so \
#    libRSDriverArm.so \
#    liboffline_compiler_api_gles.so \
#    cl_stub/libOpenCL.so \

define define-mali-prebuilt
include $$(CLEAR_VARS)
LOCAL_MODULE := $1.32
LOCAL_SRC_FILES := vendor/lib/$1
LOCAL_INSTALLED_MODULE_STEM := $$(notdir $1)
LOCAL_MODULE_RELATIVE_PATH := $$(dir $1)
LOCAL_MODULE_SUFFIX := $$(suffix $1)
LOCAL_MODULE_CLASS := $2
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_PROPRIETARY_MODULE := true
include $$(BUILD_PREBUILT)

ifneq ($$(TARGET_2ND_ARCH),)
include $$(CLEAR_VARS)
LOCAL_MODULE := $1.64
LOCAL_SRC_FILES := vendor/lib64/$1
LOCAL_INSTALLED_MODULE_STEM := $$(notdir $1)
LOCAL_MODULE_RELATIVE_PATH := $$(dir $1)
LOCAL_MODULE_SUFFIX := $$(suffix $1)
LOCAL_MODULE_CLASS := $2
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 64
LOCAL_PROPRIETARY_MODULE := true
include $$(BUILD_PREBUILT)
endif
endef

$(foreach prebuilt,$(PREBUILT_LIBS),\
    $(eval $(call define-mali-prebuilt,$(prebuilt),SHARED_LIBRARIES)))

############################# libbccArm.so ###########################

include $(CLEAR_VARS)
LOCAL_MODULE := libbccArm.so.32
LOCAL_SRC_FILES := vendor/lib/libbccArm.so
LOCAL_INSTALLED_MODULE_STEM := libbccArm.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_PROPRIETARY_MODULE := true
LOCAL_POST_INSTALL_CMD := cp -f $(LOCAL_PATH)/vendor/lib/libmalicore.bc $(TARGET_OUT_VENDOR)/lib
include $(BUILD_PREBUILT)

ifneq ($(TARGET_2ND_ARCH),)
include $(CLEAR_VARS)
LOCAL_MODULE := libbccArm.so.64
LOCAL_SRC_FILES := vendor/lib64/libbccArm.so
LOCAL_INSTALLED_MODULE_STEM := libbccArm.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 64
LOCAL_PROPRIETARY_MODULE := true
LOCAL_POST_INSTALL_CMD += cp -f $(LOCAL_PATH)/vendor/lib64/libmalicore.bc $(TARGET_OUT_VENDOR)/lib64
include $(BUILD_PREBUILT)
endif

############################# libGLES_mali.so ###########################

include $(CLEAR_VARS)
LOCAL_MODULE := egl/libGLES_mali.so.32
LOCAL_SRC_FILES := vendor/lib/egl/libGLES_mali.so
LOCAL_INSTALLED_MODULE_STEM := libGLES_mali.so
LOCAL_MODULE_RELATIVE_PATH := egl
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_PROPRIETARY_MODULE := true
LOCAL_POST_INSTALL_CMD := ln -sf egl/libGLES_mali.so $(TARGET_OUT_VENDOR)/lib/libOpenCL.so.1.1; \
                          ln -sf libOpenCL.so.1.1 $(TARGET_OUT_VENDOR)/lib/libOpenCL.so.1; \
                          ln -sf libOpenCL.so.1 $(TARGET_OUT_VENDOR)/lib/libOpenCL.so;
include $(BUILD_PREBUILT)

ifneq ($(TARGET_2ND_ARCH),)
include $(CLEAR_VARS)
LOCAL_MODULE := egl/libGLES_mali.so.64
LOCAL_SRC_FILES := vendor/lib64/egl/libGLES_mali.so
LOCAL_INSTALLED_MODULE_STEM := libGLES_mali.so
LOCAL_MODULE_RELATIVE_PATH := egl
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 64
LOCAL_PROPRIETARY_MODULE := true
LOCAL_POST_INSTALL_CMD += ln -sf egl/libGLES_mali.so $(TARGET_OUT_VENDOR)/lib64/libOpenCL.so.1.1; \
                          ln -sf libOpenCL.so.1.1 $(TARGET_OUT_VENDOR)/lib64/libOpenCL.so.1; \
                          ln -sf libOpenCL.so.1 $(TARGET_OUT_VENDOR)/lib64/libOpenCL.so;
include $(BUILD_PREBUILT)
endif

endif # TARGET_BOARD_PLATFORM
