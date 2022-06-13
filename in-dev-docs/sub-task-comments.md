
Task 0.01 - Setup Version Control
- a: Initialised Git
- b: Added all files to git 
- c: Had to rename branch from master to dev, to make the branch names match on git and github 
    - git branch -m dev
- d: Push to remote git branch
- e: Pulled from remote git branch
- f: completed the Task
Task 0.02 - Basic Makefile
- a: Try make hello world
- b: This worked as planned
- c: Create Src Directory
- d: Create include directory
- e: create main file in src
- f: create hello world in c++
- g: create make file to build hello_world.exe
- h: look for g++ build exe command from g++ docs
- i: run hello_exe
- j: this worked as intended
- k: create a variable for the include directories (consulting the makefile [docs](https://www.gnu.org/software/make/manual/html_node/Introduction.html))
- l: create a variable for the source directories
- m: create a rule make that will make object files from all cpp files in a src directory
- n: before completing task m, created a variable (CC) and assigned g++ (the compiler to it)
- o: Task m was complete, however, what I needed to do was create a rule.
- p: From all object files, I need to build it into an exe file
- q: Find out how to get a list of all object files that are in a directory, so that it can be used to build hello_exe
- r: Make hello_exe failed
- s: removed hello temporary build command
- t: echo the found objects, to find out what the program is able to currently recognise
- u: Task Complete
Task 0.03 - Ignore Object Files 
- a: created gitignore file
- b: ignore executables and object files
- c: commit changes to github
- d: push changed
- e: forgot to add files, then added then and retried previous steps
- f: task completed

Task - Initialise SDL and GLEW 0.0.4
a: copy and comment previous initialisations of SDL
b: added SDL dependancy make file and capitalised variables
c: define a default screen width and height
d: Done and commited

Task - Initialise ImGui 0.0.5
a: copied imgui init from previous initialisation
b: subtask: add vendor folder and copy the ImGui source files Inside, done
c: subtask: Add the include and the source folders for ImGui into the MAKEFILE, done
d: Create the demo window ImGui command
e: rename the output exe
f: create a make install-run command
g: a new makefile that will include imgui files
h: non conflicting names for object files : contraints
i: var for individual src files
h:  remove srcfiles 