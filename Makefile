.PHONY: all clean

CC := gcc
CFLAGS := -I. -Wall -Wextra -Wno-unused-function -Wno-unused-variable -Dtb_UNITY
LDLIBS := -lX11 -lm

BUILD_DIR := build
TARGET := $(BUILD_DIR)/app
SOURCE := source/tb/tb.c

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LDLIBS) -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
