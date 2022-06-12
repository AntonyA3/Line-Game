includes = ./include
sources = ./src
CC = g++
OBJECTS = $(patsubst $(sources)/%.cpp,%.o,$(wildcard $(sources)/*.cpp))

%.o : $(sources)/%.cpp
	$(CC) -c $< -o $@

hello_exe : $(OBJECTS) 
	$(CC) -o hello_exe $(OBJECTS)