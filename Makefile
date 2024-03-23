CC := g++
CFL := 

TOOLCHAIN := 
OUT_EXECUTABLE_NAME := zcame1-repacker
OUT_EXECUTABLE_PATH := ./build
ARCH := 
LIBS := -lz

SOURCE_FILES := src/*.cpp

all:
	$(TOOLCHAIN)$(CC) $(CFL) $(ARCH) $(SOURCE_FILES) $(LIBS) -o $(OUT_EXECUTABLE_PATH)/$(OUT_EXECUTABLE_NAME)

clear:
	rm -f *.o
	rm -f $(OUT_EXECUTABLE_PATH)/$(OUT_EXECUTABLE_NAME)