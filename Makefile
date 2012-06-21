INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -O3
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

all: clean Image.o World.o main

main : main.cpp
	$(CXX) $(CXXFLAGS) -o $@ Image.o World.o $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm -f *.o main
