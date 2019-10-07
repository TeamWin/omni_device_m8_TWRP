/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/properties.h>
#include <android-base/logging.h>

#include "property_service.h"

namespace android {
namespace init {

void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[],
    char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties() {
    std::string platform = android::base::GetProperty("ro.board.platform", "");
    std::string bootmid;
    std::string device;

    if (platform != ANDROID_TARGET)
        return;

    bootmid = android::base::GetProperty("ro.boot.mid", "");
 
    if (bootmid.rfind("0P6B", 0) == 0) {
        if (bootmid == "0P6B20000") {
            /* m8vzw (m8wl) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8wl");
            property_override("ro.build.product", "htc_m8wl");
            property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC6525LVW");
        } else if (bootmid == "0P6B41000") {
            /* China Telecom (m8dwg) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8dwg");
            property_override("ro.build.product", "htc_m8dwg");
            property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC M8d");
        } else if (bootmid == "0P6B61000") {
            /* China Unicom (m8dug) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8dug");
            property_override("ro.build.product", "htc_m8dug");
            property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC M8e");
        } else if (bootmid == "0P6B64000" || bootmid == "0P6B68000") {
            /* International (m8dug) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8dug");
            property_override("ro.build.product", "htc_m8dug");
            property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_M8 dual sim");
        } else if (bootmid == "0P6B70000") {
            /* m8spr (m8whl) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8whl");
            property_override("ro.build.product", "htc_m8whl");
            property_override_dual("ro.product.model", "ro.vendor.product.model", "831C");
        } else {
            /* US/Int'l/GPE GSM m8 (m8) */
            property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_m8");
            property_override("ro.build.product", "htc_m8");
        }
    } else {
        if (bootmid.rfind("0PAJ", 0) == 0) {
            if (bootmid == "0PAJ10000") {
                /* China Mobile (mectl) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mectl");
                property_override("ro.build.product", "htc_mectl");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8");
            } else if (bootmid == "0PAJ20000" || bootmid == "0PAJ21000" || bootmid == "0PAJ22000") {
                /* China Unicom/Bangladesh (mecdugl) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mecdugl");
                property_override("ro.build.product", "htc_mecdugl");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8 Dual Sim");
            } else if (bootmid == "0PAJ30000") {
                /* Europe (mecul_emea) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mecul_emea");
                property_override("ro.build.product", "htc_mecul_emea");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8");
            } else if (bootmid == "0PAJ31000") {
                /* Singapore/Vietnam/Europe MMR (mecul) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mecul");
                property_override("ro.build.product", "htc_mecul");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8");
            } else if (bootmid == "0PAJ40000") {
                /* China Telecom (mecdwgl) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mecdwgl");
                property_override("ro.build.product", "htc_mecdwgl");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8 Dual Sim");
            } else if (bootmid == "0PAJ50000") {
                /* Sprint (mecwhl) */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mecwhl");
                property_override("ro.build.product", "htc_mecwhl");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "0PAJ5");
            } else {
                /* E8 */
                property_override_dual("ro.product.device", "ro.vendor.product.device", "htc_mec");
                property_override("ro.build.product", "htc_mec");
                property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC One_E8");
            }
        }
    }
    device = android::base::GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootmid '" << bootmid.c_str() <<
        "' setting build properties for '" << device.c_str() << "' device\n";
}
}  // namespace init
} // namespace android

