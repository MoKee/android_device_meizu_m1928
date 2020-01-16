#
# Copyright (C) 2019-2020 The MoKee Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

$(call inherit-product, vendor/meizu/m1928/m1928-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay \
    $(LOCAL_PATH)/overlay-mokee

# Init
PRODUCT_PACKAGES += \
    init.target.rc

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/vendor_fstab.qcom:$(TARGET_COPY_OUT_SYSTEM)/etc/vendor_fstab.qcom

# Manifest
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/vendor_manifest.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/vendor_manifest.xml

# Power
PRODUCT_PACKAGES += \
    android.hardware.power@1.2-service-qti.m1928

# Inherit from sm8150-common
$(call inherit-product, device/meizu/sm8150-common/common.mk)
