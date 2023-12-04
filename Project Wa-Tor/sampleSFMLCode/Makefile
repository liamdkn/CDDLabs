#Author: Liam Durkan 
#Licence: GPL3 
#Github: https://github.com/liamdkn/ConcurrentDevelopment-/blob/main/labThree

CXX = g++
CPPFILES = main.cpp
CPPFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system #-libomp -fopenmp
EXE = wator

# SFML configuration
SFML_INCLUDE = -I/usr/local/Cellar/sfml/2.6.1/include
SFML_LIB = -L/usr/local/Cellar/sfml/2.6.1/lib

SRCS = main.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

# This rule says that each .o file depends on a .cpp file of the same name
# This is actually built into Make but anyways...
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(SFML_INCLUDE) $(DEBUGFLAGS)

ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS) $(SFML_LIB)

# Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

# Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: ALL

# Remove temporary .o files
CLEAN:
	rm -f *.o
