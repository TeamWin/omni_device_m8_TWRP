#
# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -gt 23; echo $$?),0)
    LOCAL_CFLAGS += -DGETPROP_RETURNS_STRING
endif

LOCAL_SRC_FILES := init_$(TARGET_DEVICE).cpp
LOCAL_MODULE := libinit_$(TARGET_DEVICE)

include $(BUILD_STATIC_LIBRARY)
