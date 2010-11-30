# ---------------------------------------------------------------------------
# Makefile
#
# SYNOPSIS:
#
# make [all] - makes everything
# make clean - removes all files generated by make
#
# Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
# ---------------------------------------------------------------------------

# Programms
RM        = /bin/rm
CP        = /bin/cp
STRIP     = /usr/bin/strip

# Flags passed to the preprocessor
CXXFLAGS = -g -Wall -Wextra -Winit-self -march=k8 -ansi -pedantic -std=c++98

# Additional flags for debugging
DEBUG_FLAGS = -pg

# Additional libs
LIBS = -lpcap

# Path to the source and object files
MODULES   := Flow Ip Measurement .
SRC_DIR   := $(addprefix src/,$(MODULES))
SRC   := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,src/%.o,$(SRC))

## Name of the programm
NAME = spid

# Where to find user code.
USER_DIR = src

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGES) $(LIBS) -o $(NAME) $(OBJ)
	$(STRIP) $(NAME)

debug : $(OBJ)
	$(CXX) $(CXXFLAGES) $(DEBUG_FLAGS) $(LIBS) -o $(NAME) $(OBJ)

check-syntax:
	$(CXX) $(CXXFLAGS) -fsyntax-only -o nul -S ${CHK_SOURCES}
clean:
	$(RM) -rf $(NAME) $(OBJ) *.o *.a
