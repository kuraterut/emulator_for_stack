#-----------------------
# Compiler/linker flags
#-----------------------

CC = g++

# Compiler flags:
CFLAGS = \
	-std=c++17 \
	-O2
# 	-g3
	
	

# Linker flags:
# NOTE: it is sometimes required to link to math library.
#LDFLAGS =

# Select build mode:
# NOTE: invoke with "DEBUG=1 make" or "make DEBUG=1".
ifeq ($(DEBUG),1)
	# Add default symbols:
	CFLAGS += -g
else
	# Enable link-time optimization:
	CFLAGS  += -flto
	LDFLAGS += -flto
endif

# CFLAGS = -fsanitize=undefined,address -g3 -O0
# LDFLAGS = -fsanitize=undefined,address -g3 -O0

#--------
# Colors
#--------

# Use ANSI color codes:
BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

#-------
# Files
#-------

INCLUDES = $(wildcard include/*.hpp)

# Add "include" folder to header search path:
CFLAGS += -I $(abspath include)

# List of sources:
SOURCES = $(wildcard src/*.cpp)


OBJECTS_all = $(SOURCES:src/%.cpp=build/%.o) build/alltest.o
# OBJECTS_all +=  $(build/alltest.o)
OBJECTS_fibo = $(SOURCES:src/%.cpp=build/%.o) build/fibo.o
OBJECTS_fact = $(SOURCES:src/%.cpp=build/%.o) build/fact.o
OBJECTS_factrec = $(SOURCES:src/%.cpp=build/%.o) build/factrec.o
OBJECTS_rbin = $(SOURCES:src/%.cpp=build/%.o) build/read_bin.o

EXECUTABLE_all = build/alltest
EXECUTABLE_fibo = build/fibo
EXECUTABLE_fact = build/fact
EXECUTABLE_factrec = build/factrec
EXECUTABLE_rbin = build/read_bin

#---------------
# Build process
#---------------

# default: $(EXECUTABLE)

# # Link all object files together to obtain a binary:
# # NOTE: all object files will be built first.
# $(EXECUTABLE): $(OBJECTS) Makefile
# 	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# # Compile an object file:
# # NOTE: all include files are passed as dependencies (this may be redundant)
# build/%.o: src/%.cpp $(INCLUDES) Makefile
# 	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
# 	@mkdir -p build
# 	$(CC) -c $< $(CFLAGS) -o $@

# By default, build executable:
# NOTE: first target in the file is the default.

default: $(EXECUTABLE_all)

# Link all object files together to obtain a binary:
# NOTE: all object files will be built first.
$(EXECUTABLE_rbin): $(OBJECTS_rbin) build/read_bin.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS_rbin) -o $@

$(EXECUTABLE_all): $(OBJECTS_all) build/alltest.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS_all) -o $@

$(EXECUTABLE_fibo): $(OBJECTS_fibo) build/fibo.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS_fibo) -o $@

$(EXECUTABLE_fact): $(OBJECTS_fact) build/fact.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS_fact) -o $@

$(EXECUTABLE_factrec): $(OBJECTS_factrec) build/factrec.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS_factrec) -o $@




# Compile an object file:
# NOTE: all include files are passed as dependencies (this may be redundant)
build/read_bin.o: src/tests/read_bin.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

build/alltest.o: src/tests/alltest.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@


# Compile an object file:
# NOTE: all include files are passed as dependencies (this may be redundant)
build/fibo.o: src/tests/fibo.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

build/fact.o: src/tests/fact.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

build/factrec.o: src/tests/factrec.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

build/%.o: src/%.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@



#--------------
# Test scripts
#--------------

# Run program:
alltest: $(EXECUTABLE_all)
	./$(EXECUTABLE_all)

fibo: $(EXECUTABLE_fibo)
	./$(EXECUTABLE_fibo)

fact: $(EXECUTABLE_fact)
	./$(EXECUTABLE_fact)

factrec: $(EXECUTABLE_factrec)
	./$(EXECUTABLE_factrec)

rbin: $(EXECUTABLE_rbin)
	./$(EXECUTABLE_rbin)
#---------------
# Miscellaneous
#---------------

clean:
	@printf "$(BYELLOW)Cleaning build directory $(RESET)\n"
	rm -rf build

# List of non-file targets:
.PHONY: run clean default