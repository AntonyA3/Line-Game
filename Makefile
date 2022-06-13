INCLUDES = -I./include
SOURCES = ./src
FLAGS = -Wall
# SDL and opengl deps
DEPS = -lSDL2 -lglu32 -lopengl32 -lglew32
CC = g++
OBJECTS = $(patsubst $(SOURCES)/%.cpp,%.o,$(wildcard $(SOURCES)/*.cpp))

%.o : $(SOURCES)/%.cpp
	$(CC) -c $< -o $@

hello_exe : $(OBJECTS) 
	$(CC) -o hello_exe $(OBJECTS) $(INCLUDES) $(FLAGS) $(DEPS)