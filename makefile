CPP.COMPILER ?= g++
BUILD ?= debug

DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SRC_DIR := $(DIR)/src
INCLUDE_DIR := $(SRC_DIR)
BUILD_DIR := $(DIR)/build/$(BUILD)

EXECUTABLE := $(BUILD_DIR)/exec

CPP.FLAGS := -o $(EXECUTABLE) -pedantic -Wall -Wextra -I$(INCLUDE_DIR) -std=c++20 -lgtest
ifeq ($(BUILD),release)
	CPP.FLAGS += -Ofast
else
	CPP.FLAGS += -g -O0
endif

CPP.SRC := $(shell find $(SRC_DIR) -name '*.cpp')
CPP.HEADERS := $(shell find $(INCLUDE_DIR) -name '*.h')

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) $(ARGS)

run-vg: $(EXECUTABLE)
	valgrind $(EXECUTABLE) $(ARGS)


test: $(EXECUTABLE)
	valgrind $(EXECUTABLE) test

$(EXECUTABLE): $(CPP.SRC) $(CPP.HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CPP.COMPILER) $(CPP.FLAGS) $(CPP.SRC)

clean:
	rm -r build/
