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

# Permissions
PRODUCT_COPY_FILES += \
    vendor/mokee/config/permissions/vendor.mokee.biometrics.fingerprint.inscreen.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/permissions/vendor.mokee.biometrics.fingerprint.inscreen.xml

# Fingerprint
PRODUCT_PACKAGES += \
    mokee.biometrics.fingerprint.inscreen@1.0-service.m1928

# Init
PRODUCT_PACKAGES += \
    init.target.rc

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/vendor_fstab.qcom:$(TARGET_COPY_OUT_SYSTEM)/etc/vendor_fstab.qcom

# Manifest
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/vendor_manifest.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/vendor_manifest.xml

# Inherit from sm8150-common
$(call inherit-product, device/meizu/sm8150-common/common.mk)
