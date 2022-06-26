# Code Generator #

I have never written a code generator, however I am confident that I know what needs to be done to do this

- I would need to convert a c++ file to another c++ file.
- Idealy I would want to preserve the original file
- I would probably have to create another directory to build the program, therefore rather than building from src, I should build from src_gen
- To generate the files I am likely to use a scripting language like Python

Advantages
- I would have unlocked a powerful way to solve problems
- I would be able to solve the problem of wanting to create a function or another class based on the properties of an existing class, since C++ is not able to provide this for me.

Disadvantages
- I may be unintentionally reimplementing a feature that already exists in C++ therefore re inventing the wheel
- I might not have many uses for this

- I will call this code generator cpp_gen

What I did
- I created an src_gen folder
- I created a python file called ImGuiLogger Generator
- In the python script I will create a file reader
- In I will copy the contents of the file to a string
- I will Find Lines that contain [Code Generate]
- I will get the parametres of the code generator
- Based on the instructions in the parametres I will tokenise the C++ constucts.
- Based on the tokens I will generate the strings for the new code
- I will then append this new code after the code generation

- I tried using macros and the c++ Preprocessor to generate code, however this failed.
1. I will create a file type called entity
2. I will add comments with the symbol //cpp+ml for where I want certain pieces of code to generate
3. The line will have the file path of the code that I want to inject


Day 2
- Read section 3 of the GCC docs for macros

Notes Macros in section 3
- Named code fragment for text replacement
- 2 macro types (Object Like, Function Lick)
Object Like
    -Usually for constsant

    
    #define TABLESIZE BUFFERSIZE
    #define BUFFERSIZE 10

    int square(int num) {
        int z = TABLESIZE;
        return 1;
    }

    Becomes

    int square(int num) {
        int z = 10;
        return 1;
    }

Therefore TABLESIZE is replace with BUFFERSIZE and BUFFERSIZE is replaced with 10
- This is macro expansion

- having read page 1 of the macros doc, I might have figured out a way, to create new entites with the proprocessor


Task
- Use macros to create a metastructure called an Entity
    - An entity will have a dependancy on ImGui
    - it will costruct a class for an object
    - it will construct a free function that is able to take the entity as an input and log it's gettable properties to an imgui tree view
    - maybe macro expansion might not be good enough