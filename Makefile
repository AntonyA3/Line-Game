CC = g++ #compiler
INCLUDES = -I./include -I./vendors/imgui -I./vendors/imgui/backends
SRCDIR = ./sourcegen 
CFLAGS = -Wall -g
# SDL and opengl deps
DEPS = -lSDL2 -lglu32 -lopengl32 -lglew32
# Get all the future object files
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp)) ./vendors/imgui/backends/imgui_impl_opengl3.o ./vendors/imgui/backends/imgui_impl_sdl.o $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
#build object files
%.o : %.cpp
	$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)

line_runner : $(OBJECTS) 
	$(CC) -o line_runner $(OBJECTS) $(INCLUDES) $(CFLAGS) $(DEPS)

install :
	make line_runner

#clean all object files
clean : $(OBJECTS)
	rm -f $(OBJECTS) line_runner.exe
# 

install_run :
	make line_runner
	./line_runner