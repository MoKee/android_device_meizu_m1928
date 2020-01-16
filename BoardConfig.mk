#
# Copyright (C) 2019-2020 The MoKee Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from meizu sm8150-common
-include device/meizu/sm8150-common/BoardConfigCommon.mk

DEVICE_PATH := device/meizu/m1928

# Assertion
TARGET_OTA_ASSERT_DEVICE := m1928,meizu16T

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth/include

# Kernel
TARGET_PREBUILT_KERNEL := $(DEVICE_PATH)/prebuilt/Image.gz-dtb

# HAX: Remove ASAP
BOARD_KERNEL_CMDLINE += androidboot.selinux=permissive

# Fingerprint
SOONG_CONFIG_MEIZU_SM8150_FOD_POS_X := 447
SOONG_CONFIG_MEIZU_SM8150_FOD_POS_Y := 1812
SOONG_CONFIG_MEIZU_SM8150_FOD_SIZE := 186
SOONG_CONFIG_MEIZU_SM8150_FOD_INPUT := event3

# Light
SOONG_CONFIG_MEIZU_SM8150_LIGHT_MX_LED_PATH := /sys/class/leds/mx-led

# Power
TARGET_TAP_TO_WAKE_NODE := /dev/mokee.touch@1.0/dt2w

# Properties
TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# Releasetools
TARGET_BOARD_INFO_FILE := $(DEVICE_PATH)/board-info.txt

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += $(DEVICE_PATH)

# inherit from the proprietary version
-include vendor/meizu/m1928/BoardConfigVendor.mk
