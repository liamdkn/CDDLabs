# Joseph Kehoe
# This is very basic. It is just here to show you a simple sfml graphics display that you can use.
# I expect better from you!

CXX = g++
CPPFILES = main.cpp
CPPFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system #-libomp -fopenmp
EXE = testApp

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
