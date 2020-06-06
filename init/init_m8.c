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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_htcCommon.h"

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get_sdk23("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get_sdk23("ro.boot.mid", bootmid);

    if (strstr(bootmid, "0P6B")) {
        if (strstr(bootmid, "0P6B20000")) {
            /* m8vzw (m8wl) */
            property_set("ro.product.model", "HTC6525LVW");
            property_set("ro.build.product", "htc_m8wl");
        } else if (strstr(bootmid, "0P6B70000")) {
            /* m8spr (m8whl) */
            property_set("ro.product.model", "831C");
            property_set("ro.build.product", "htc_m8whl");
        } else if (strstr(bootmid, "0P6B61000")) {
            /* China Unicom (m8dug) */
            property_set("ro.build.product", "htc_m8dug");
            property_set("ro.product.model", "HTC M8e");
        } else if (strstr(bootmid, "0P6B64000") || strstr(bootmid, "0P6B68000")) {
            /* International (m8dug) */
            property_set("ro.build.product", "htc_m8dug");
            property_set("ro.product.model", "HTC One_M8 dual sim");
        } else if (strstr(bootmid, "0P6B41000")) {
            /* China Telecom (m8dwg) */
            property_set("ro.build.product", "htc_m8dwg");
            property_set("ro.product.model", "HTC M8d");
        } else {
            /* m8 */
            property_set("ro.build.product", "htc_m8");
            property_set("ro.product.model", "HTC One_M8");
        }
    } else if (strstr(bootmid, "0PAJ")) {
        if (strstr(bootmid, "0PAJ50000")) {
            /* Sprint (mecwhl) */
            property_set("ro.build.product", "htc_mecwhl");
            property_set("ro.product.model", "0PAJ5");
        } else if (strstr(bootmid, "0PAJ10000")) {
            /* China Mobile (mectl) */
            property_set("ro.build.product", "htc_mectl");
            property_set("ro.product.model", "HTC One_E8");
        } else if (strstr(bootmid, "0PAJ20000") || strstr(bootmid, "0PAJ21000") || strstr(bootmid, "0PAJ22000")) {
            /* China Unicom/Bangladesh (mecdugl) */
            property_set("ro.build.product", "htc_mecdugl");
            property_set("ro.product.model", "HTC One_E8 Dual Sim");
        } else if (strstr(bootmid, "0PAJ30000")) {
            /* Europe (mecul_emea) */
            property_set("ro.build.product", "htc_mecul_emea");
            property_set("ro.product.model", "HTC One_E8");
        } else if (strstr(bootmid, "0PAJ31000")) {
            /* Singapore/Vietnam/Europe MMR (mecul) */
            property_set("ro.build.product", "htc_mecul");
            property_set("ro.product.model", "HTC One_E8");
        } else if (strstr(bootmid, "0PAJ40000")) {
            /* China Telecom (mecdwgl) */
            property_set("ro.build.product", "htc_mecdwgl");
            property_set("ro.product.model", "HTC One_E8 Dual Sim");
        } else {
            /* e8 */
            property_set("ro.build.product", "htc_e8");
            property_set("ro.product.model", "HTC One_E8");
        }
    }

    set_props_from_build();

    property_get_sdk23("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
