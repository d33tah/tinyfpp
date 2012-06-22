INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -ggdb -O0
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

all: clean Engine.o CameraSync.o Image.o World.o main

main : main.cpp
	$(CXX) $(CXXFLAGS) -o $@ Image.o World.o Engine.o CameraSync.o $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm -f *.o main
