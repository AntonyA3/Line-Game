PREPROCESSOR =py ./src/mach_to_cpp.py
CC = g++ #compiler
INCLUDES = -I./include -I./vendors/imgui -I./vendors/imgui/backends
SRCDIR = ./$(SRCFOLDER)
CFLAGS = -Wall -g
# SDL and opengl deps
DEPS = -lSDL2 -lglu32 -lopengl32 -lglew32
# Get all the future object files
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard sourcegen/*.cpp)) ./vendors/imgui/backends/imgui_impl_opengl3.o ./vendors/imgui/backends/imgui_impl_sdl.o $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
SOURCEGEN = sourcegen/main.cpp

# #build object files

./sourcegen/%.cpp : src/mach/%.mach
	$(PREPROCESSOR) $< $@

./sourcegen/%.o : ./sourcegen/%.cpp
	$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)

%.o : %.cpp
	$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)


line_runner : $(SOURCEGEN) $(OBJECTS)
	$(CC) -o line_runner $(OBJECTS) $(INCLUDES) $(CFLAGS) $(DEPS)

install : 
	make line_runner

remove_code_gen :
	rm -f $(SOURCEGEN)

code_gen: $(SOURCEGEN) 

code_re_gen:
	make remove_code_gen
	make code_gen

#clean all generated files
clean :
	rm -f $(OBJECTS) line_runner.exe $(SOURCEGEN)


install_run :
	make line_runner
	./line_runner