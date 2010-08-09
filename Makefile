# ---------------------------------------------------------------------------
# Makefile
#
# Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
# ---------------------------------------------------------------------------

# Where to find the rm command
RM        = /bin/rm

# Where to find the cp command
CP        = /bin/cp

# Flags passed to the preprocessor
CXXFLAGES = -Wall -Wextra -Winit-self -march=i386 -ansi -pedantic -std=c++98 -O3

# Addtional flags for debugging
DEBUG_FLAGES = -pg

LIBS    = -lpcap
STRIP   = /usr/bin/strip

## files
SRC_DIR = src
SOURCES = \
	  $(SRC_DIR)/*.cpp \
	  $(SRC_DIR)/Flow/*.cpp \
	  $(SRC_DIR)/Flow/*.h \
	  $(SRC_DIR)/Ip/*.cpp \
	  $(SRC_DIR)/Ip/*.h \
	  $(SRC_DIR)/Measurement/*.cpp \
	  $(SRC_DIR)/Measurement/*.h

## names
NAME   = spid

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unittests

.PHONY: check-syntax

$(NAME):
	$(CXX) $(CXXFLAGES) $(LIBS) $(SOURCES) -o $(NAME)
	$(STRIP) $(NAME)

debug:
	$(CXX) $(CXXFLAGES) $(DEBUG_FLAGES) $(LIBS) $(SOURCES) -o $(NAME)

clean:
	$(RM) -rf $(NAME)

check-syntax:
	$(CXX) $(CXXFLAGES) -fsyntax-only $(SOURCES)

