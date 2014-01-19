INCLUDE =
LIBDIR  =

COMPILERFLAGS = -Wall
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -ggdb
LIBRARIES = -lX11 -lXi -lglut -lGL -lGLU -lm
OBJS = src/CameraSync.o src/Engine.o src/Image.o src/Object.o src/World.o \
       src/main.o
TARGET = main

ifdef WIN32
CXX = i686-w64-mingw32-g++
LIBRARIES = -lglut -lglu32 -lopengl32
TARGET = main.exe
endif

all: $(TARGET) mouse

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBDIR) $(LIBRARIES)

glfw-legacy/lib/x11/libglfw.a:
	git clone https://github.com/glfw/glfw-legacy.git
	cd glfw-legacy ; sh compile.sh
	make -C glfw-legacy x11 $(MAKEFLAGS)

mouse: mouse.cpp glfw-legacy/lib/x11/libglfw.a
	clang -Wall -Wextra -Wunused -o mouse mouse.cpp -lpthread -I  glfw-legacy/include glfw-legacy/lib/x11/libglfw.a -lX11 -lXrandr -lGL -lm -lstdc++

clean:
	rm -f $(OBJS) main mouse
