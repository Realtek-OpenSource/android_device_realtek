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

# OTT common goes to rtk-ott.mk
$(call inherit-product, device/realtek/hercules/rtk-ott.mk)

PRODUCT_MODEL  := Realtek Hercules 32-bit OTT
PRODUCT_DEVICE := hercules32
PRODUCT_NAME   := hercules32
PRODUCT_BRAND  := rtk
PRODUCT_MANUFACTURER := Realtek

