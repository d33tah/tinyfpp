INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib

COMPILERFLAGS = -Wall
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -ggdb
LIBRARIES = -lX11 -lXi -lglut -lGL -lGLU -lm
OBJS = CameraSync.o Engine.o Image.o Object.o World.o Rotate.o main.o

all: main mouse

main : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBDIR) $(LIBRARIES)

glfw-legacy/lib/x11/libglfw.a:
	git clone https://github.com/glfw/glfw-legacy.git
	cd glfw-legacy ; sh compile.sh
	make -C glfw-legacy x11 $(MAKEFLAGS)

mouse: mouse.cpp glfw-legacy/lib/x11/libglfw.a
	clang -Wall -Wextra -Wunused -o mouse mouse.cpp -lpthread -I  glfw-legacy/include glfw-legacy/lib/x11/libglfw.a -lX11 -lXrandr -lGL -lm -lstdc++

clean:
	rm -f *.o main mouse
