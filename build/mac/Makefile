CPP=g++
CFLAGS=-std=c++14 -Wall

PROJ_DIR:=../..

INCLUDE_DIR=$(PROJ_DIR)/include
LIB_DIR=$(PROJ_DIR)/lib/mac/
SRC_DIR=$(PROJ_DIR)/src
INT_DIR=$(PROJ_DIR)/bin-int
OUTPUT_DIR=$(PROJ_DIR)/bin
OUTPUT=main
LIBS=glfw3
FRAMEWORKS=Cocoa OpenGL IOKit
DEFINES=GL_SILENCE_DEPRECATION

SRC_FILES_NAMES:=$(shell find $(SRC_DIR) *.cpp)
SRC_FILES:=$(foreach dir,$(SRC_FILES_NAMES),$(wildcard $(dir)/*.cpp))
SRC_FILES_OBJ=$(addprefix $(INT_DIR)/, $(patsubst %.cpp, %.o, $(subst $(PROJ_DIR)/,,$(SRC_FILES))))
INCLUDE_FILES_NAMES:=$(shell find $(INCLUDE_DIR) *.cpp)
INCLUDE_FILES:=$(foreach dir, $(INCLUDE_FILES_NAMES),$(wildcard $(dir)/*.cpp))
INCLUDE_FILES_OBJ=$(addprefix $(INT_DIR)/, $(patsubst %.cpp, %.o, $(subst $(PROJ_DIR)/,,$(INCLUDE_FILES))))

all: build

$(SRC_FILES_OBJ): $(SRC_FILES)
	mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $(patsubst %.o,%.cpp,$(subst $(INT_DIR)/,$(PROJ_DIR)/,$@)) -o $@ $(foreach define,$(DEFINES),$(addprefix -D,$(define)))

$(INCLUDE_FILES_OBJ): $(INCLUDE_FILES)
	mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $(patsubst %.o,%.cpp,$(subst $(INT_DIR)/,$(PROJ_DIR)/,$@)) -o $@ $(foreach define,$(DEFINES),$(addprefix -D,$(define)))

bin-int-dir:
	@mkdir -p $(INT_DIR)

bin-dir:
	@mkdir -p $(OUTPUT_DIR)

build: | bin-dir bin-int-dir $(SRC_FILES_OBJ) $(INCLUDE_FILES_OBJ)
	$(CPP) $(SRC_FILES_OBJ) $(INCLUDE_FILES_OBJ) -o $(OUTPUT_DIR)/$(OUTPUT) -L$(LIB_DIR) $(foreach lib,$(LIBS),$(addprefix -l,$(lib))) $(foreach fw,$(FRAMEWORKS),$(addprefix -framework ,$(fw)))

$(OUTPUT): build

run: $(OUTPUT)
	./$(OUTPUT_DIR)/$(OUTPUT) $(ARGS)

clean:
	rm -r $(INT_DIR)
	rm -r $(OUTPUT_DIR)
