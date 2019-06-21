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

#define NOTIFY_FINGER_DOWN 1536
#define NOTIFY_FINGER_UP 1537
#define NOTIFY_UI_READY 1607
#define NOTIFY_UI_DISAPPER 1608
// #define NOTIFY_ENABLE_PAY_ENVIRONMENT 1609
// #define NOTIFY_DISABLE_PAY_ENVIRONMENT 1610

#define BOOST_ENABLE_PATH "/sys/class/meizu/fp/qos_set"
#define HBM_ENABLE_PATH "/sys/class/meizu/lcm/display/hbm"

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
    hidl_vec<uint8_t> data;
    set(HBM_ENABLE_PATH, 1);
    this->mGoodixFpDaemon->sendCommand(NOTIFY_FINGER_DOWN, data, [&](int, const hidl_vec<uint8_t>&) {
    });
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    hidl_vec<uint8_t> data;
    set(HBM_ENABLE_PATH, 0);
    this->mGoodixFpDaemon->sendCommand(NOTIFY_FINGER_UP, data, [&](int, const hidl_vec<uint8_t>&) {
    });
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    hidl_vec<uint8_t> data;
    set(BOOST_ENABLE_PATH, 1);
    this->mGoodixFpDaemon->sendCommand(NOTIFY_UI_READY, data, [&](int, const hidl_vec<uint8_t>&) {
    });
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    hidl_vec<uint8_t> data;
    this->mGoodixFpDaemon->sendCommand(NOTIFY_UI_DISAPPER, data, [&](int, const hidl_vec<uint8_t>&) {
    });
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t, int32_t) {
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

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace mokee
}  // namespace vendor
