CXX := /usr/local/bin/g++
CPP := /usr/local/bin/cpp
# Eliminate intrinsic rules
.SUFFIXES:

SRC := $(shell /usr/bin/find -L . -path ./.git -prune -o -name '*.cpp' -print)
HDR := $(shell /usr/bin/find -L . -path ./.git -prune -o -name '*.hpp' -print)

# Initialize common variables
SDL_GAME_DIR := /home/shkumar/code/cpp/sdl_game

CPPFLAGS:=
CPPFLAGS += -I $(SDL_GAME_DIR)/
CPPFLAGS += -I $(SDL_GAME_DIR)/lib


CXXFLAGS:= -std=c++23
CXXFLAGS += -Wall -Werror -Wno-attributes -O2 -fPIC

SDL2_DIR := /usr/local/include/SDL2
CPPFLAGS += -isystem $(SDL2_DIR)
LDLIBS += -lSDL2 -lSDL2_image

# Shared files for WMS that are architecture specific

# Use gcc 4.8.5
# export it so that so_wrapper can use it too.
LDLIBS += -latomic

# 32 bit build
# CXXFLAGS += -m32
# LDFLAGS += -m32

LDFLAGS += -Wl,-rpath=


MY_COMPILE.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) 
MY_PREPROCESS.cpp = $(CPP) $(CPPFLAGS)
MY_OUTPUT_OPTION = -o $@
 
%.o: %.cpp
	$(MY_COMPILE.cpp) -c $(MY_OUTPUT_OPTION) $<
 

SRC_SRC := $(shell /usr/bin/find -L src -maxdepth 2 -name '*.cpp')
EXE :=
EXE += $(patsubst %/main, %, $(patsubst %.cpp, %, $(patsubst src/%, bin/%, $(SRC_SRC))))

 
OBJ := $(patsubst %.cpp, %.o, $(SRC))
	
#Also include any files with a .mk extension
SUB_MAKES += $(shell /usr/bin/find -L . -name '*.mk' -print)
ifneq ($(SUB_MAKES),)
    include $(SUB_MAKES)
endif

.PHONY:  \
	$(PHONY)

all : exe lib

exe: $(EXE)

lib: $(LIB)

clean:
	@echo "Removing current object files and dependency files..."
	@rm -f --verbose -- $(OBJ) $(SHOBJ)
	@echo "Removing current executables..."
	@rm -f --verbose -- $(EXE)
	@find -L . -name "*.[oda]" -o -name "*.os" | xargs --verbose --no-run-if-empty rm -f --



ctags:
	ctags -R $(SDL_GAME_DIR)

