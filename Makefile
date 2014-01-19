INCLUDE =
LIBDIR  =
COMPILERFLAGS = -Wall
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE) -ggdb
OBJS = src/CameraSync.o src/Engine.o src/Image.o src/Object.o src/World.o \
       src/main.o

UNIX_TARGET = main
WIN32_TARGET = main.exe

ifdef WIN32
CXX = i686-w64-mingw32-g++
LIBRARIES = -static -lstdc++ -Wl,-Bdynamic -lglut -lglu32 -lopengl32
TARGET = $(WIN32_TARGET)
else
CXX = g++
LIBRARIES = -lX11 -lXi -lglut -lGL -lGLU -lm
TARGET = $(UNIX_TARGET)
endif

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBDIR) $(LIBRARIES)

clean:
	rm -f $(OBJS) $(UNIX_TARGET) $(WIN32_TARGET)
