.PHONY: all clean

DIRECTORY := $(shell pwd)
COMPILER := g++
INCLUDE := -I$(DIRECTORY)/src/code -I$(DIRECTORY)/src -I$(DIRECTORY)/src/base
OPTIONS := -g -fpermissive -Wno-unused-function -Wno-unused-variable -fsanitize=address -Wall -Werror -D_GNU_SOURCE 

CFLAGS += $(shell pkg-config --cflags x11)
LDFLAGS += $(shell pkg-config --libs x11)

OPTIONS += $(CFLAGS)
OPTIONS += $(LDFLAGS)

BUILD_DIR  := ./build
SOURCE_DIR := ./src
TARGET := $(BUILD_DIR)/program

all: $(TARGET)

debug: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(SOURCE_DIR)/code/program.cpp
	$(COMPILER) $(INCLUDE) $(OPTIONS) $(SOURCE_DIR)/code/program.cpp -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
