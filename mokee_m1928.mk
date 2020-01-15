#
# Copyright (C) 2018 The MoKee Open Source Project
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

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit from m1928 device
$(call inherit-product, device/meizu/m1928/device.mk)

# Inherit some common MoKee stuff.
$(call inherit-product, vendor/mokee/config/common_full_phone.mk)

PRODUCT_PROPERTY_OVERRIDES += \
    ro.mk.maintainer=XiNGRZ

PRODUCT_NAME := mokee_m1928
PRODUCT_BRAND := meizu
PRODUCT_DEVICE := m1928
PRODUCT_MANUFACTURER := meizu
PRODUCT_MODEL := 16T

PRODUCT_BUILD_PROP_OVERRIDES += \
    TARGET_DEVICE="meizu16T" \
    PRODUCT_NAME="meizu_16T_CN" \
    PRIVATE_BUILD_DESC="meizu_16T_CN-user 9 PKQ1.190616.001 1573644279 release-keys"

BUILD_FINGERPRINT := meizu/meizu_16T_CN/meizu16T:9/PKQ1.190616.001/1573644279:user/release-keys

PRODUCT_PRODUCT_PROPERTIES += \
    ro.sf.lcd_density=380

PRODUCT_PRODUCT_PROPERTIES += \
    fod.dimming.min=40 \
    fod.dimming.max=250
