#include <private/android_filesystem_config.h>

#define NO_ANDROID_FILESYSTEM_CONFIG_DEVICE_DIRS
/* static const struct fs_path_config android_device_dirs[] = { }; */

/* Rules for files.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root. Prefixes ending in * denotes wildcard
** and will allow partial matches.
*/
static const struct fs_path_config android_device_files[] = {
    // Support FIFO scheduling mode in hwcomposer.
    { 00755, AID_SYSTEM,    AID_GRAPHICS,  (1ULL << CAP_SYS_NICE),
        "vendor/bin/hw/android.hardware.graphics.composer@2.2-service" },

    // Support FIFO scheduling mode in sideband.
    { 00755, AID_MEDIA,    AID_GRAPHICS,  (1ULL << CAP_SYS_NICE),
        "vendor/bin/sideband" },

#ifdef NO_ANDROID_FILESYSTEM_CONFIG_DEVICE_DIRS
    { 00000, AID_ROOT,      AID_ROOT,      0, "system/etc/fs_config_dirs" },
#endif
};
