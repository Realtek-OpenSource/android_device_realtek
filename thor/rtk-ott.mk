# Bruce some bad workaround here, define overlay at the same place.
DEVICE_PACKAGE_OVERLAYS := device/realtek/thor/overlay_common \
                        device/realtek/thor/overlay_ott

$(call inherit-product, device/realtek/thor/device.mk)

PRODUCT_AAPT_CONFIG := normal large tvdpi mdpi hdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base.mk)

#rtkbt
$(call inherit-product, hardware/realtek/bt/rtkbt/rtkbt.mk)

PRODUCT_CHARACTERISTICS := tablet

PRODUCT_COPY_FILES += frameworks/native/data/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml
#PRODUCT_COPY_FILES += device/realtek/thor/overlay/system/etc/permissions/tablet_extend_hardware.xml:system/etc/permissions/tablet_extend_hardware.xml
#PRODUCT_COPY_FILES += device/realtek/thor/audio_policy_tablet.conf:system/etc/audio_policy.conf

PRODUCT_PACKAGES += Calendar
#PRODUCT_PACKAGES += RtkLauncher2
#PRODUCT_PACKAGES += RealtekSettings
PRODUCT_PACKAGES += RealtekSoftwareUpdater
PRODUCT_PACKAGES += RealtekMiniLauncher
PRODUCT_PACKAGES += NetworkLocation

PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=240

