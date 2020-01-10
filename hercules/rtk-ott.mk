# Bruce some bad workaround here, define overlay at the same place.
DEVICE_PACKAGE_OVERLAYS := device/realtek/hercules/overlay_common \
                        device/realtek/hercules/overlay_ott

$(call inherit-product, device/realtek/hercules/device.mk)

PRODUCT_AAPT_CONFIG := normal large tvdpi mdpi hdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base.mk)

# Low memory device applies Android Go settings
ifeq ($(ENABLE_LOW_RAM), true)
$(warning Enable low ram settings)
$(call inherit-product, build/make/target/product/go_defaults_512.mk)
endif

#rtkbt
$(call inherit-product, hardware/realtek/bt/rtkbt/rtkbt.mk)

PRODUCT_CHARACTERISTICS := tablet

PRODUCT_COPY_FILES += frameworks/native/data/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml
#PRODUCT_COPY_FILES += device/realtek/hercules/overlay/system/etc/permissions/tablet_extend_hardware.xml:system/etc/permissions/tablet_extend_hardware.xml
#PRODUCT_COPY_FILES += device/realtek/hercules/audio_policy_tablet.conf:system/etc/audio_policy.conf

PRODUCT_PACKAGES += Calendar
#PRODUCT_PACKAGES += RtkLauncher2
#PRODUCT_PACKAGES += RealtekSettings
PRODUCT_PACKAGES += RealtekSoftwareUpdater
PRODUCT_PACKAGES += RealtekMiniLauncher
PRODUCT_PACKAGES += NetworkLocation

PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=240

