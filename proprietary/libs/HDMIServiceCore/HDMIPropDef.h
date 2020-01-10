#ifndef _HDMI_PROP_DEF_H_
#define _HDMI_PROP_DEF_H_

#ifndef _ANDROID_LEGACY

/* Android P and later version */
#define PROPERTY_EDID_MODE                  "persist.vendor.rtk.edid.auto"
#define PROPERTY_DEEP_COLOR_FIRST           "persist.vendor.rtk.deep.first"
#define PROPERTY_COLOR_MODE_ENUM            "persist.vendor.rtk.color.mode"
#define PROPERTY_HDR_AUTO                   "persist.vendor.rtk.hdr.auto"

#define PROPERTY_IGNORE_EDID                "persist.vendor.rtk.ignore.edid"
#define PROPERTY_VIDEO_STANDARD             "persist.vendor.rtk.display.standard"
#define PROPERTY_SUPPORT_DOVI               "ro.vendor.rtk.dovi.support"

#else

/* Android O is a legacy version */
#define PROPERTY_EDID_MODE                  "persist.vendor.edid.auto"
#define PROPERTY_DEEP_COLOR_FIRST           "persist.vendor.deep.first"
#define PROPERTY_COLOR_MODE_ENUM            "persist.vendor.color.mode"
#define PROPERTY_HDR_AUTO                   "persist.vendor.hdr.auto"

#define PROPERTY_VIDEO_STANDARD             "persist.vendor.display.standard"
#define PROPERTY_IGNORE_EDID                "persist.vendor.ignore.edid"
#define PROPERTY_SUPPORT_DOVI               "ro.vendor.dovi.support"

#endif

#endif
