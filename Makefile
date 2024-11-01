GCC_DIR := /usr/bin
CXX := $(GCC_DIR)/bin/g++-11.1.0
CPP := $(GCC_DIR)/bin/cpp-11.1.0
# Eliminate intrinsic rules
.SUFFIXES:

SRC := $(shell /usr/bin/find -L . -path ./.git -prune -o -name '*.cpp' -print)
HDR := $(shell /usr/bin/find -L . -path ./.git -prune -o -name '*.hpp' -print)

# Initialize common variables
CPPFLAGS:=
CXXFLAGS:= -std=c++20

LDLIBS := -lgtest

# Shared files for WMS that are architecture specific

# Use gcc 4.8.5
# export it so that so_wrapper can use it too.
LDLIBS += -latomic

# 32 bit build
CXXFLAGS += -m32
LDFLAGS += -m32

APP_DIR := .
CPPFLAGS += -I ../include
CPPFLAGS += -I ../../include
CPPFLAGS += -I $(APP_DIR)
CPPFLAGS += -I /usr0/include



LDFLAGS += -Wl,-rpath,$(GTEST_DIR)/lib

TEST_LDLIBS := -lgtest


OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEP := $(patsubst %.cpp, %.d, $(SRC))

EXE :=
SCRIPTS :=
SHOBJ :=

# Objects that are built as part of all, but not as part of any other subgoal.
LIB :=


TARBALL_DIR := tarball

SRC_MENU := $(wildcard src/*.m)

# Make targets that do not require the dependency files to be generated
NONDEPEND_GOALS :=




PHONY += all

# Add the NONDEPEND_GOALS to the PHONY list, but submakes will need to add to
# both if that is what is wanted.
PHONY += $(NONDEPEND_GOALS)

CXXFLAGS += -Wall -Werror -Wno-attributes -O2 -fPIC

MY_COMPILE.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)
MY_PREPROCESS.cpp = $(CPP) $(CPPFLAGS)
MY_OUTPUT_OPTION = -o $@

CLANG_TIDY_OPTIONS =
# Check all header files included by the changed file
CLANG_TIDY_OPTIONS += --header-filter=".*"
# Lower the verbosity to just the extraneous messages that can be filtered by
# filter_build_output
CLANG_TIDY_OPTIONS += --quiet
# Tell clang compiler where to find the g++ libraries
CLANG_TIDY_OPTIONS += --extra-arg="--gcc-toolchain=$(GCC_DIR)"
# Allow users to add in new options or override the above options by arranging
# for CLANG_TIDY_USER_OPTION to be set.
CLANG_TIDY_OPTIONS += $(CLANG_TIDY_USER_OPTION)

# Place other CLANG_TIDY_OPTIONS before this line. These should be the final
# options.  Everything after -- is information for clang-tidy about the gcc
# command.
CLANG_TIDY_OPTIONS += $< -- $(MY_COMPILE.cpp) -c $(MY_OUTPUT_OPTION) $<


# Sometimes it is useful to see the preprocessed source. 
# Make the .i version of your cpp file if you want this.
%.i: %.cpp
	$(MY_PREPROCESS.cpp) $(MY_OUTPUT_OPTION) $<

%.d: %.cpp
	@test -f $@ && unlink $@ ; \
	sh depend.sh `dirname $*.cpp` $(CPPFLAGS) $*.cpp > $@


%.a: %.mk
	./ar_wrapper $@ $(filter-out %.mk, $^)

# Sub makes will add other goals to all
all: exe lib



ifeq (,$(filter $(MAKECMDGOALS),$(NONDEPEND_GOALS)))
include $(DEP)
include lib/libdal.mk

endif

# Also include any files with a .mk extension
SUB_MAKES += $(shell /usr/bin/find -L . -name '*.mk' -print)

# build_type was already included
SUB_MAKES := $(filter-out %build_type.mk , $(SUB_MAKES))


ifneq ($(SUB_MAKES),)
    include $(SUB_MAKES)
endif

.PHONY:  \
	$(PHONY)

# Shared libraries should be built before exes try to link to them
$(EXE) : | $(LIB)

exe: $(EXE)

lib: $(LIB)


# Make all of the dependency files
depends: $(DEP)



# remove only the .d files for when you had a bad include that needs to be
# fixed, but you do not need to recompile everything.
depend_clean:
	@echo "Removing dependency files..."
	@find -L . -name "*.d" | xargs --no-run-if-empty rm --

clean:
	@echo "Removing current object files and dependency files..."
	@rm -f --verbose -- $(OBJ) $(DEP) $(SHOBJ)
	@echo "Removing current executables..."
	@rm -f --verbose -- $(EXE)
	@echo "Removing libraries..."
	@rm -f --verbose -- $(LIB)



ctags:
	ctags -R $(WMS_DIR)

