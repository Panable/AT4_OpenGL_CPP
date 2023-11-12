NUM_CORES := $(shell nproc)

.PHONY: clean build

# Default build mode is 'debug' if not set
BUILD_MODE ?= debug

clean:
	@echo "Cleaning..."
	@rm -rf build

build: clean
	@echo "Building in $(BUILD_MODE) mode with $(NUM_CORES) cores..."
	@mkdir -p build
	@cd build && cmake -DCMAKE_BUILD_TYPE=$(BUILD_MODE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	@cmake --build build -- -j$(NUM_CORES)

all: build

.DEFAULT_GOAL := all
