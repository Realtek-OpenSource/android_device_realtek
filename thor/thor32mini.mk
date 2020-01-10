#
# Copyright 2013 The Android Open-Source Project
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


# Bruce some bad workaround here, define overlay at the same place.
DEVICE_PACKAGE_OVERLAYS := device/realtek/thor/overlay_common \
                        device/realtek/thor/overlay_ott

$(call inherit-product, device/realtek/thor/device_mini.mk)
$(call inherit-product, build/target/product/core_base.mk)

$(call inherit-product-if-exists, frameworks/base/data/fonts/fonts.mk)

PRODUCT_CHARACTERISTICS := nosdcard

PRODUCT_MODEL  := Realtek Thor 32-bit Mini
PRODUCT_DEVICE := thor32mini
PRODUCT_NAME   := thor32mini
PRODUCT_BRAND  := rtk
PRODUCT_MANUFACTURER := Realtek

PRODUCT_COPY_FILES += frameworks/native/data/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml

PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=240

PRODUCT_PACKAGES += local_time.default

