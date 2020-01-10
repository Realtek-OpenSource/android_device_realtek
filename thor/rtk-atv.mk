## currently, thor_tv only uses overlay settings under overlay_common, the order of inherit is important,
## we inherit device.mk first, so overlay_common is applied first, then we inherit atv_generic

$(call inherit-product, device/realtek/thor/device.mk)
$(call inherit-product, device/google/atv/products/atv_base.mk)

#rtkbt
$(call inherit-product, hardware/realtek/bt/rtkbt/rtkbt.mk)

# device/google/atv/overlay already included in atv_base.mk
PRODUCT_PACKAGE_OVERLAYS := \
    device/realtek/thor/overlay_common \
    device/realtek/thor/overlay_atv

PRODUCT_CHARACTERISTICS := tv

#PRODUCT_PACKAGES += RealtekTvSettings
#PRODUCT_PACKAGES += RealtekTvQuickSettings
PRODUCT_PACKAGES += RealtekAppDrawer

#PRODUCT_PACKAGES += UseHDMITvInputService
PRODUCT_PACKAGES += SampleTvInput
PRODUCT_PACKAGES += RtkPartnerConfig
PRODUCT_PACKAGES += RtkPartnerInterface

### Work-around to make home key works, refer to ATM-327 for detailed information
#PRODUCT_PACKAGES += Provision

# DHCKYLIN-38, Need DocumentsUI to handle android.provider.action.BROWSE_DOCUMENT_ROOT
#PRODUCT_PACKAGES += DocumentsUI

PRODUCT_COPY_FILES += device/realtek/thor/bootanimation-atv.zip:$(TARGET_COPY_OUT_SYSTEM)/media/bootanimation.zip

# Netflix
PRODUCT_PACKAGES += ninja
PRODUCT_COPY_FILES += device/realtek/thor/nrdp.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/nrdp.xml
PRODUCT_COPY_FILES += device/realtek/thor/netflix.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/sysconfig/netflix.xml
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.vendor.nrdp.modelgroup=NEXUSPLAYERFUGU
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += ro.vendor.nrdp.validation=ninja_6
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += vendor.display-size=3840x2160

