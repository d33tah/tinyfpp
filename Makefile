INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -O3
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 
OBJS = CameraSync.o Engine.o Image.o Object.o World.o

all: main

main : main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm -f *.o main
