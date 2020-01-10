# Android TV common goes to rtk-atv.mk
$(call inherit-product, device/realtek/hercules/rtk-atv.mk)

# Low memory device applies Android Go settings
$(call inherit-product, build/make/target/product/go_defaults_512.mk)

PRODUCT_MODEL  := Rtk Android TV 1GB
PRODUCT_DEVICE := atv1gb
PRODUCT_NAME   := atv1gb
PRODUCT_BRAND  := rtk
PRODUCT_MANUFACTURER := Realtek

PRODUCT_PROPERTY_OVERRIDES += ro.sf.lcd_density=318

