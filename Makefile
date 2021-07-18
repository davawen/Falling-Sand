CXX = g++
CXXFLAGS = -Wall -Wno-unknown-pragmas -Wno-switch
CXXLINKFLAGS = #-pthread

EXEC_NAME = main

SRC_FILES = main.cpp matrix.cpp element.cpp

LIBS = sfml-window sfml-system sfml-network sfml-graphics sfml-audio

LIB_PATH = /usr/local/lib64
INCLUDE_PATH = ./include /usr/local/include/

# The rest is madness

SRC_FILES := $(addprefix src/,$(SRC_FILES))
OBJ_FILES = $(basename $(SRC_FILES))
OBJ_FILES := $(OBJ_FILES:src/%=build/obj/%.o)

LIBS := $(addprefix -l,$(LIBS))
LIB_PATH := $(addprefix -L,$(LIB_PATH))
INCLUDE_PATH := $(addprefix -I,$(INCLUDE_PATH))

all: prog
	./build/bin/$(EXEC_NAME)

prog: $(OBJ_FILES)
	$(CXX) $(CXXLINKFLAGS) $^ $(LIB_PATH) $(LIBS) -o build/bin/$(EXEC_NAME)

build/obj/%.o: src/%.c
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(INCLUDE_PATH)

build/obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(INCLUDE_PATH)

clean:
	rm -rf build/bin/$(EXEC_NAME) build/obj/*.o

init:
	mkdir build build/bin build/obj

test:
	@echo Source Files: $(SRC_FILES) 
	@echo Object Files: $(OBJ_FILES)
	@echo Libs: $(LIBS)
	@echo Lib Path: $(LIB_PATH)
	@echo Include Path: $(INCLUDE_PATH)
	@echo Executable Name: $(EXEC_NAME)
	@echo Compiler: $(CXX) $(CXXFLAGS)
	@echo Linker: $(CXX) $(CXXLINKFLAGS)