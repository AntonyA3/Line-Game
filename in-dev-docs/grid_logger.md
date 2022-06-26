
- Option 1: Rejected
    I grid is able to log itself to an Imgui window with grid_object.log(); However the grid will have a dependancy on ImGui

    Disadvantages:
        - The Grid and ImGui are coupled, therefore it will fail if I use any other UI Framework

- Option 2: Acceptable
    Advantages
        - No coupling between the Grid or other objects and its logger.
        - If I forget to make a function to log a particular object, it will be easily caught by the compiler
    Disadvantages
        - For each new class that I want to log, I will have to create a new function to interprete it.
    I have a function that recieves a grid and is able to log it: However function will be a free function, rather than an object

- Option 3: Acceptable
    I have a method in the grid that returns a loggable subset of the Grid then that loggable grid subset is able to log the grid. The grid without the changed Property; However that will still lead to the Grid being dependant on ImGui; a reference grid logger will use the function for logging a grid; 
    Advantages
    - Classes and the loggers are decoupled
    -
    Disadvantages
    - However a logger class will be dependant on all the classes in my program that can be logged to an ImGui window

- Option 4: Acceptable
    Grid Logger Class a class that is able to log the grid, at the initialisation stage I add the grid to the grid logger, in the while loop, I Update the GridLogger to log the grid in the frame; A reference grid logger will delegate it's logging to a grid logger;
    Advantage
        - Logger decoupled from the object

    Disadvantage
        - A new logger class will need to be created for each object that I want to consider logging


- Option 5: Acceptable
    - I have a logger class, however it recieves logging commands that are then converted into ImGui Commands; This will lead to the loggable classes needing some sort of builder object
    - And some interpreter for the builder object
    - However each class will still have to implement it's own interpreter

    Advantages
        - Objects decoupled from logger
    Disadvantages
        - Any object that I want to log will be dependant on the command rules 

- Option 6: All classes are able to return a universal format, such as a hashmap, or JSON
    - This hashmap can be used in the logger to log information
    - Therefore every class should be able to return JSON which can be parsed to the logger. Instead of every class being parsed by the logger if that method is available
    - However every class will need to be able to return a json object

    Advantages
    - Objects are decoupled from the logger
    - I would be able to log anything with only a single function
    - The universal data format of a class is nly dependant on itself

    Disadvantages
    - All classes would need to have the universal format, If the schema changes, then I would have to change every class
    - I would need to convert the class to a sting, otherwise I would have to use a large union based data structurre to represent any value type in the hash map

- Option 7: I have an object called ImGuiLog info: Each loggable object will have an Imgui Log function; However it will lead to the same problems as in Option 1 
Rather than creating many classes to extend the logger it would be better to Option 2 would be the best: I might use ifdefn to remove functions when certain classes are made not to exist.

- Option 8: I have a tag above a class, if this tag exists then there will be a function that can that will be able to log this class

Pick Option 2: If this was a bad choice. create a new task


