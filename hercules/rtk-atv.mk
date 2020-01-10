## currently, hercules_tv only uses overlay settings under overlay_common, the order of inherit is important,
## we inherit device.mk first, so overlay_common is applied first, then we inherit atv_generic

$(call inherit-product, device/realtek/hercules/device.mk)
$(call inherit-product, device/google/atv/products/atv_base.mk)

# Low memory device applies Android Go settings
ifeq ($(ENABLE_LOW_RAM), true)
$(warning Enable low ram settings)
$(call inherit-product, build/make/target/product/go_defaults_512.mk)
endif

#rtkbt
$(call inherit-product, hardware/realtek/bt/rtkbt/rtkbt.mk)

# device/google/atv/overlay already included in atv_base.mk
PRODUCT_PACKAGE_OVERLAYS := \
    device/realtek/hercules/overlay_common \
    device/realtek/hercules/overlay_atv

PRODUCT_CHARACTERISTICS := tv

#PRODUCT_PACKAGES += RealtekTvSettings
#PRODUCT_PACKAGES += RealtekTvQuickSettings
PRODUCT_PACKAGES += RealtekAppDrawer

#PRODUCT_PACKAGES += UseHDMITvInputService
PRODUCT_PACKAGES += SampleTvInput
PRODUCT_PACKAGES += RtkPartnerConfig
#PRODUCT_PACKAGES += RtkPartnerInterface

### Work-around to make home key works, refer to ATM-327 for detailed information
#PRODUCT_PACKAGES += Provision

# DHCKYLIN-38, Need DocumentsUI to handle android.provider.action.BROWSE_DOCUMENT_ROOT
#PRODUCT_PACKAGES += DocumentsUI

PRODUCT_COPY_FILES += device/realtek/hercules/bootanimation-atv.zip:$(TARGET_COPY_OUT_SYSTEM)/media/bootanimation.zip

# Netflix
PRODUCT_PACKAGES += ninja
PRODUCT_COPY_FILES += device/realtek/hercules/nrdp.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/nrdp.xml
PRODUCT_COPY_FILES += device/realtek/hercules/whitelist.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/sysconfig/whitelist.xml
# NEXUSPLAYERFUGU / RTD2841AVTENGINEERING / RTD2851AVTENGINEERING
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.vendor.nrdp.modelgroup=NEXUSPLAYERFUGU
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.vendor.nrdp.validation=ninja_6
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += sys.display-size=3840x2160
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += vendor.display-size=3840x2160

ifeq ($(ENABLE_LOW_RAM), true)
# 213 for 720p, 318 for 1080p. TODO:flags to separate 720p & 1080p
PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=213
else
PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=320
endif
PRODUCT_PROPERTY_OVERRIDES += persist.vendor.rtk.net.wol=1
