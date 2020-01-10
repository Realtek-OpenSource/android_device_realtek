#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TARGET_ARCH := arm64
TARGET_ARCH_VARIANT := armv8-a
TARGET_CPU_ABI := arm64-v8a
TARGET_CPU_ABI2 :=
TARGET_CPU_VARIANT := cortex-a53

TARGET_2ND_ARCH := arm
TARGET_2ND_ARCH_VARIANT := armv8-a
TARGET_2ND_CPU_ABI := armeabi-v7a
TARGET_2ND_CPU_ABI2 := armeabi
TARGET_2ND_CPU_VARIANT := generic

#TARGET_CPU_SMP := true
#TARGET_PREFER_32_BIT := true
TARGET_USES_64_BIT_BINDER := true
#ARCH_ARM_HAVE_TLS_REGISTER := true

TARGET_BOARD_PLATFORM := hercules
TARGET_BOOTLOADER_BOARD_NAME := lionskin

# VENDOR_SECURITY_PATCH must be equaled with PLATFORM_SECURITY_PATCH
VENDOR_SECURITY_PATCH := $(PLATFORM_SECURITY_PATCH)

TARGET_COPY_OUT_VENDOR := vendor

BOARD_PROPERTY_OVERRIDES_SPLIT_ENABLED := true

#System
TARGET_PRELINK_MODULE := true
TARGET_NO_BOOTLOADER := true
TARGET_NO_RECOVERY := true
TARGET_NO_KERNEL := false
TARGET_NO_RADIOIMAGE := true
BOARD_VNDK_VERSION := current
TARGET_PROVIDES_INIT_RC := true
TARGET_RUNNING_WITHOUT_SYNC_FRAMEWORK := true

# ---------------------------------------------------> Time
#
# |----------------------------|----------------------
# |<- A ->|----------------------------|--------------
#         |<- B ->|----------------------------|------
# ^       ^       ^
# |       |       |_ VSync for SurfaceFlinger
# |       |_ VSync for App UI
# |_ Hardware VSync
#
# A: VSYNC_EVENT_PHASE_OFFSET_NS
# B: SF_VSYNC_EVENT_PHASE_OFFSET_NS

TARGET_USES_OVERLAY := true
TARGET_FORCE_HWC_FOR_VIRTUAL_DISPLAYS := true
MAX_VIRTUAL_DISPLAY_DIMENSION := 4096
#TARGET_USES_GRALLOC1 := true
TARGET_USES_HWC2 := true
#VSYNC_EVENT_PHASE_OFFSET_NS := 2000000
#SF_VSYNC_EVENT_PHASE_OFFSET_NS := 6000000
VSYNC_EVENT_PHASE_OFFSET_NS := 0
SF_VSYNC_EVENT_PHASE_OFFSET_NS := 0
USE_VR_FLINGER := true

USE_OPENGL_RENDERER := true
#BOARD_USE_LEGACY_UI := true
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
#OVERRIDE_RS_DRIVER:= libRSDriver_adreno.so
#OVERRIDE_RS_DRIVER := libRSDriverArm.so

BOARD_USES_GENERIC_AUDIO := true

BOARD_USES_ALSA_AUDIO := true
#AUDIO_FEATURE_ENABLED_MULTI_VOICE_SESSIONS := true
#AUDIO_FEATURE_ENABLED_SND_MONITOR := true

#TARGET_USES_ION := true
#TARGET_USES_NEW_ION_API :=true

BOARD_PROPERTY_OVERRIDES_SPLIT_ENABLED := true

# For Widevine library level
BOARD_WIDEVINE_OEMCRYPTO_LEVEL:= 1

#FORCE_ARM_DEBUGGING := true

# pre-optimization options
#WITH_DEXPREOPT := true
#DONT_DEXPREOPT_PREBUILTS := true
#WITH_DEXPREOPT_BOOT_IMG_ONLY := true
#WITH_DEXPREOPT_PIC := true
#WITH_ART_SMALL_MODE := true

DEVICE_MANIFEST_FILE := device/realtek/hercules/common/manifest.xml
DEVICE_MATRIX_FILE   := device/realtek/hercules/common/compatibility_matrix.xml
DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := device/realtek/hercules/common/device_framework_matrix.xml

# Exclude serif fonts for saving system.img size.
EXCLUDE_SERIF_FONTS := true

BOARD_SEPOLICY_DIRS += device/realtek/hercules/common/sepolicy
#BOARD_PLAT_PRIVATE_SEPOLICY_DIR +=

BOARD_BUILD_SYSTEM_ROOT_IMAGE := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x0200000

