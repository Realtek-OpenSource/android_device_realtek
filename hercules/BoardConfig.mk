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

# common setting
include device/realtek/hercules/common/BoardConfigCommon.mk

# Use mke2fs to create ext4 images
TARGET_USES_MKE2FS := true

BOARD_FLASH_BLOCK_SIZE := 4096
TARGET_USERIMAGES_USE_EXT4 := true
#BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE := squashfs
#BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824

#default is 8gb_emmc_partition
BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1610612736

BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_VENDORIMAGE_PARTITION_SIZE := 268435456

BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 16777216

BOARD_XENIMAGE_PARTITION_SIZE := 66108864
BOARD_XENIMAGE_FILE_SYSTEM_TYPE := ext4

BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16793600

#FIXME: customer must use their own AVB key!
BOARD_AVB_KEY_PATH := device/realtek/hercules/avb_testkey_rsa4096.pem
BOARD_AVB_ALGORITHM := SHA512_RSA4096
BOARD_AVB_ENABLE := true

ifeq ($(DMVERITY_ENABLE), NO)
BOARD_BUILD_DISABLED_VBMETAIMAGE := true
BOARD_AVB_MAKE_VBMETA_IMAGE_ARGS += --flag 2
endif

WIFI_DRIVER_MODULE_PATH := "/vendor/lib/modules"
WIFI_DRIVER_MODULE_NAME := 8821cu
WIFI_DRIVER_MODULE_ARG := "ifname=wlan0 if2name=p2p0"
# wifi setting
BOARD_WIFI_VENDOR := realtek
ifeq ($(BOARD_WIFI_VENDOR), realtek)
WPA_SUPPLICANT_VERSION := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
#CONFIG_DRIVER_WEXT :=y
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_rtl
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_rtl
BOARD_HOSTAPD_DRIVER := NL80211
#
BOARD_WLAN_DEVICE := realtek
#
endif

