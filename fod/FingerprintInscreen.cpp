/*
 * Copyright (C) 2019 The LineageOS Project
 * Copyright (C) 2019 The MoKee Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "FingerprintInscreenService"

#include "FingerprintInscreen.h"
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <fstream>

#define FINGERPRINT_ACQUIRED_VENDOR 6

#define NOTIFY_FINGER_DOWN 1536
#define NOTIFY_FINGER_UP 1537
#define NOTIFY_UI_READY 1607
#define NOTIFY_UI_DISAPPER 1608
// #define NOTIFY_ENABLE_PAY_ENVIRONMENT 1609
// #define NOTIFY_DISABLE_PAY_ENVIRONMENT 1610

#define BOOST_ENABLE_PATH "/sys/class/meizu/fp/qos_set"
#define HBM_ENABLE_PATH "/sys/class/meizu/lcm/display/hbm"

#define DIM_MIN 26
#define DIM_MAX 648

namespace vendor {
namespace mokee {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_0 {
namespace implementation {

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

FingerprintInscreen::FingerprintInscreen() {
    this->mGoodixFpDaemon = IGoodixFingerprintDaemon::getService();
}

Return<int32_t> FingerprintInscreen::getPositionX() {
    return 447;
}

Return<int32_t> FingerprintInscreen::getPositionY() {
    return 1812;
}

Return<int32_t> FingerprintInscreen::getSize() {
    return 186;
}

Return<void> FingerprintInscreen::onStartEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    set(HBM_ENABLE_PATH, 1);
    notifyHal(NOTIFY_FINGER_DOWN);
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    set(HBM_ENABLE_PATH, 0);
    notifyHal(NOTIFY_FINGER_UP);
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    set(BOOST_ENABLE_PATH, 1);
    notifyHal(NOTIFY_UI_READY);
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    notifyHal(NOTIFY_UI_DISAPPER);
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t acquiredInfo, int32_t vendorCode) {
    std::lock_guard<std::mutex> _lock(mCallbackLock);
    if (mCallback == nullptr) {
        return false;
    }

    if (acquiredInfo == FINGERPRINT_ACQUIRED_VENDOR) {
        if (vendorCode == 2) {
            Return<void> ret = mCallback->onFingerDown();
            if (!ret.isOk()) {
                LOG(ERROR) << "FingerDown() error: " << ret.description();
            }
            return true;
        }

        if (vendorCode == 3) {
            Return<void> ret = mCallback->onFingerUp();
            if (!ret.isOk()) {
                LOG(ERROR) << "FingerUp() error: " << ret.description();
            }
            return true;
        }
    }

    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t, int32_t) {
    return false;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t) {
    return 0;
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
    return false;
}

Return<void> FingerprintInscreen::setCallback(const sp<IFingerprintInscreenCallback>& callback) {
    {
        std::lock_guard<std::mutex> _lock(mCallbackLock);
        mCallback = callback;
    }
    return Void();
}

void FingerprintInscreen::notifyHal(int32_t cmd) {
    hidl_vec<int8_t> data;
    Return<void> ret = this->mGoodixFpDaemon->sendCommand(cmd, data, [&](int32_t resultCode, const hidl_vec<int8_t>&) {
        LOG(INFO) << "notifyHal(" << cmd << ") result: " << resultCode;
    });
    if (!ret.isOk()) {
        LOG(ERROR) << "notifyHal(" << cmd << ") error: " << ret.description();
    }
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace mokee
}  // namespace vendor
