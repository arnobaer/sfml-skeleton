# CMake wrapper

PROJECT = sfml-skeleton
BUILD = build
CMAKELISTS = CMakeLists.txt

RM = rm -rf
MAKE_DIR = mkdir -p
MAKE = make
CMAKE = cmake

.PHONY: all run clean

all: $(BUILD)/Makefile
	@ ( cd $(BUILD) ; $(MAKE) )

$(BUILD):
	@ ( $(MAKE_DIR) $(BUILD) )

$(BUILD)/Makefile: $(BUILD) $(CMAKE_LISTS)
	@ ( cd $(BUILD) ; $(CMAKE) .. )

run: all
	@ ( cd $(BUILD) ; ./$(PROJECT) )

clean:
	$(RM) $(BUILD)
