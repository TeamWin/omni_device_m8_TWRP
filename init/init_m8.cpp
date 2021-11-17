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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mount.h>

#define DEV_BLOCK_SYSTEM "/dev/block/bootdevice/by-name/system"

void set_props_from_file(const char *filename)
{
    int IsSet_ro_product_device = 0;
    FILE *fp = fopen(filename, "r");

    if (fp) {
        char line[1024];

        char propname[PROP_NAME_MAX];
        char propvalue[PROP_VALUE_MAX];
        char *pch;

        while ((fgets(line, sizeof(line), fp))) {
            if (line[0] == '\n' || line[0] == '#') continue;

            pch = strtok(line, "=\n");
            if (!pch || strlen(pch) >= PROP_NAME_MAX) continue;
            strcpy(propname, pch);

            pch = strtok(NULL, "=\n");
            if (!pch || strlen(pch) >= PROP_VALUE_MAX) continue;
            strcpy(propvalue, pch);

            if (strcmp(propname, "ro.build.fingerprint") == 0) {
                property_set(propname, propvalue);
            }
            else if (strcmp(propname, "ro.product.device") == 0) {
                property_set(propname, propvalue);
                IsSet_ro_product_device = 1;
            }
        }
        fclose(fp);
    }

    if (!IsSet_ro_product_device) {
#ifdef GETPROP_RETURNS_STRING
        std::string propvalue;
        propvalue = property_get("ro.build.product");
        property_set("ro.product.device", propvalue.c_str());
#else
        char propvalue[PROP_VALUE_MAX];
        property_get("ro.build.product", propvalue);
        property_set("ro.product.device", propvalue);
#endif
    }
}

void set_props_from_build(void)
{
    if (access("/system/build.prop", R_OK) == 0) {
        set_props_from_file("/system/build.prop");
        return;
    }

    if (mkdir("/tmpsys", 777) != 0)
        return;

    int is_mounted = mount(DEV_BLOCK_SYSTEM, "/tmpsys", "ext4", MS_RDONLY | MS_NOATIME , "") == 0;

    if (!is_mounted)
        is_mounted = mount(DEV_BLOCK_SYSTEM, "/tmpsys", "f2fs", MS_RDONLY | MS_NOATIME , "") == 0;

    if (is_mounted) {
        set_props_from_file("/tmpsys/build.prop");
        umount("/tmpsys");
    }
    rmdir("/tmpsys");
}

void vendor_load_properties()
{
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];

    property_get("ro.boot.mid", bootmid);

    if (strstr(bootmid, "0P6B")) {
        if (strstr(bootmid, "0P6B20000")) {
            /* m8vzw (m8wl) */
            property_set("ro.build.product", "htc_m8wl");
            property_set("ro.product.device", "htc_m8wl");
            property_set("ro.product.model", "HTC6525LVW");
        } else if (strstr(bootmid, "0P6B41000")) {
            /* China Telecom (m8dwg) */
            property_set("ro.build.product", "htc_m8dwg");
            property_set("ro.product.device", "htc_m8dwg");
            property_set("ro.product.model", "HTC M8d");
        } else if (strstr(bootmid, "0P6B61000")) {
            /* China Unicom (m8dug) */
            property_set("ro.build.product", "htc_m8dug");
            property_set("ro.product.device", "htc_m8dug");
            property_set("ro.product.model", "HTC M8e");
        } else if (strstr(bootmid, "0P6B64000") || strstr(bootmid, "0P6B68000")) {
            /* International (m8dug) */
            property_set("ro.build.product", "htc_m8dug");
            property_set("ro.product.device", "htc_m8dug");
            property_set("ro.product.model", "HTC One_M8 dual sim");
        } else if (strstr(bootmid, "0P6B70000")) {
            /* m8spr (m8whl) */
            property_set("ro.build.product", "htc_m8whl");
            property_set("ro.product.device", "htc_m8whl");
            property_set("ro.product.model", "831C");
        } else {
            /* US/Int'l/GPE GSM m8 (m8) */
            property_set("ro.product.device", "htc_m8");
            property_set("ro.build.product", "htc_m8");
            property_set("ro.product.model", "HTC One_M8");
        }
    } else {
        if (strstr(bootmid, "0PAJ")) {
            if (strstr(bootmid, "0PAJ10000")) {
                /* China Mobile (mectl) */
                property_set("ro.build.product", "htc_mectl");
                property_set("ro.product.device", "htc_mectl");
                property_set("ro.product.model", "HTC One_E8");
            } else if (strstr(bootmid, "0PAJ20000") || strstr(bootmid, "0PAJ21000") || strstr(bootmid, "0PAJ22000")) {
                /* China Unicom/Bangladesh (mecdugl) */
                property_set("ro.build.product", "htc_mecdugl");
                property_set("ro.product.device", "htc_mecdugl");
                property_set("ro.product.model", "HTC One_E8 Dual Sim");
            } else if (strstr(bootmid, "0PAJ30000")) {
                /* Europe (mecul_emea) */
                property_set("ro.build.product", "htc_mecul_emea");
                property_set("ro.product.device", "htc_mecul_emea");
                property_set("ro.product.model", "HTC One_E8");
            } else if (strstr(bootmid, "0PAJ31000")) {
                /* Singapore/Vietnam/Europe MMR (mecul) */
                property_set("ro.build.product", "htc_mecul");
                property_set("ro.product.device", "htc_mecul");
                property_set("ro.product.model", "HTC One_E8");
            } else if (strstr(bootmid, "0PAJ40000")) {
                /* China Telecom (mecdwgl) */
                property_set("ro.build.product", "htc_mecdwgl");
                property_set("ro.product.device", "htc_mecdwgl");
                property_set("ro.product.model", "HTC One_E8 Dual Sim");
            } else if (strstr(bootmid, "0PAJ50000")) {
                /* Sprint (mecwhl) */
                property_set("ro.build.product", "htc_mecwhl");
                property_set("ro.product.device", "htc_mecwhl");
                property_set("ro.product.model", "0PAJ5");
            } else {
                /* E8 */
                property_set("ro.build.product", "htc_mec");
                property_set("ro.product.device", "htc_mec");
                property_set("ro.product.model", "HTC One_E8");
            }
        }
    }

    set_props_from_build();

    property_get("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
