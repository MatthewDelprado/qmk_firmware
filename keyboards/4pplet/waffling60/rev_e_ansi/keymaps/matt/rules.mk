ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes

# Regenerate underglow_presets.h from underglow.json on every build
UNDERGLOW_GEN_ERROR := $(shell python3 $(KEYMAP_PATH)/gen_underglow.py)
ifneq ($(UNDERGLOW_GEN_ERROR),)
    $(error $(UNDERGLOW_GEN_ERROR))
endif
