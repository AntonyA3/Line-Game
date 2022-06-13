CC = g++ #compiler
INCLUDES = -I./include -I./vendors/imgui -I./vendors/imgui/backends
SRCDIR = ./src 
FLAGS = -Wall
# SDL and opengl deps
DEPS = -lSDL2 -lglu32 -lopengl32 -lglew32
# Get all the future object files
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp)) ./vendors/imgui/backends/imgui_impl_opengl3.o ./vendors/imgui/backends/imgui_impl_sdl.o $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
#build object files
%.o : %.cpp
	$(CC) -c $< -o $@ $(INCLUDES)

line_runner : $(OBJECTS) 
	$(CC) -o line_runner $(OBJECTS) $(INCLUDES) $(FLAGS) $(DEPS)

install_run :
	make line_runner
	./line_runner