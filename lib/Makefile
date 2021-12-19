.PHONY: build clean

CC := gcc
PKGCONFIG := pkg-config
DEPENDENCIES := gtk4
INCLUDES := $(shell $(PKGCONFIG) --cflags $(DEPENDENCIES))
LIBS := $(shell $(PKGCONFIG) --libs $(DEPENDENCIES))
GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)
RESOURCES = $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies popup.gresource.xml)
BUILD_DIR := $(shell pwd)/build
FLAGS := -shared -fPIC
OUT_FILE := popup.so

ifdef debug
	FLAGS += -DDEBUG
	BUILD_DIR := $(BUILD_DIR)/debug
else
	BUILD_DIR := $(BUILD_DIR)/release
endif

build: resources.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDES) $(FLAGS) -o $(BUILD_DIR)/$(OUT_FILE) popup.c resources.c $(LIBS)

resources.c: popup.gresource.xml $(RESOURCES)
	$(GLIB_COMPILE_RESOURCES) popup.gresource.xml --target=resources.c --generate-source

clean:
	rm -rf build
	rm resources.c