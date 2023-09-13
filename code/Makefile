# Author: Dylan Turner
# Description: Build file for the GameCube controller code

# Settings

## Build system settings

ARD_FLD :=			arduino-cli
ARD_CONF :=			arduino-cli.yaml
ARDC :=				arduino-cli
ARD_BOARDS :=		arduino:avr
PKG_INDEX :=		$(ARD_FLD)/data/package_index.json
BOARD_PKG_INDEX :=	$(ARD_FLD)/data/packages/arduino/hardware/avr/1.8.6/boards.txt

## Project specific settings

PROJNAME :=			ArduBox
BOARD_FQBN :=		arduino:avr:uno
BUILD_PATH :=		build
LIBS :=				
SRC :=				$(PROJNAME)/$(PROJNAME).ino \
					$(wildcard $(PROJNAME)/*.cpp) \
					$(wildcard $(PROJNAME)/*.hpp)
BOARD_PROPERTIES :=	
OBJNAME :=			$(PROJNAME).ino.hex

# Targets

## Helper targets

.PHONY: all
all: upload

.PHONY: clean
clean:
	rm -rf $(ARD_FLD)
	rm -rf $(BUILD_PATH)
	rm -rf *.hex

### Set up arduino-cli to be able to find things
$(PKG_INDEX):
	$(ARDC) --config-file $(ARD_CONF) core update-index

### Add boards to arduino-cli
$(BOARD_PKG_INDEX):
	$(ARDC) --config-file $(ARD_CONF) core install $(ARD_BOARDS)

### Download and install libraries
define download-lib
$(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip: $(PKG_INDEX)
	$(ARDC) --config-file $(ARD_CONF) lib download "$(subst \_, ,$(1))"
	cp $(ARD_FLD)/staging/libraries/$(subst \,,$(1))*.zip $(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip
endef
define install-lib
libraries/$(subst \,,$(1))/: $(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip
	$(ARDC) --config-file $(ARD_CONF) lib install "$(subst \_, ,$(1))"
endef
$(foreach lib,$(LIBS), \
	$(eval $(call download-lib,$(lib))); \
	$(eval $(call install-lib,$(lib))) \
)

## Main targets

### Build

# Note: ESP32 shown here. Arduino just needs the first! It will be $(PROJNAME).ino.hex

$(PROJNAME).hex: $(SRC) $(PKG_INDEX) $(BOARD_PKG_INDEX) $(foreach lib,$(LIBS),libraries/$(subst \,,$(lib))/)
	mkdir -p $(BUILD_PATH)
	$(ARDC) compile \
		--config-file $(ARD_CONF) \
		--fqbn $(BOARD_FQBN) \
		--build-path $(BUILD_PATH) \
		--libraries "libraries/" \
		$(BOARD_PROPERTIES) \
		$(PROJNAME)
	cp $(BUILD_PATH)/$(PROJNAME).ino.hex ./$@

### Upload
.PHONY: upload
upload: $(PROJNAME).hex
	$(ARDC) upload \
		--config-file $(ARD_CONF) \
		--fqbn $(BOARD_FQBN) \
		-p $(PORT) -i $(PROJNAME)

