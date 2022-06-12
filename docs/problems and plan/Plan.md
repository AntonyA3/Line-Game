# Plan and Problems#
The main problem is to Develop Line Runner, then distribute this game to people on a desktop or mobile operating system along with the Web.
Other Problems include

## Development Related Problems to Solve ##
- Creating different levels for the game, through a level editor and other editable entities in the game
- Designate where the game files will be stored
- Find ways to test the game, when new things are added
- Find Ways to debug the Game
    - Logging
    - C++ GDB
    - A unit testing Framework
    - An in game debugger that can be removed in final builds
- Audio For the Game
- Graphics For the Game
- Finding out how to make changes to the game without having to completely redesign the game.
- Develop the game, with well thought out designs, that may be flawed, but can be improved, through player feedback and design guides
- How to explore new features that the game could have
## Potential Player Desires ##
- The game progresses from easy to difficult
- The game does not stutter
- The response from the input is fast.

# Strategy
As a strategy, the best one is likely to be exploratory development as I am not completely certain of what the game will have, or what sort of abstractions that the game will require, but it is important that I track progress of this project, whether these progress points represent milestones or problems that need to be fixed. The source code will have lots of comments, to make things easy to find by using the IDE search feature

Additionally creating software that will be used to help with developing the game will be used.

# Tasks
Tasks represent atomic changes to the code that will be made, these may have subtasks that need to be completed if the task is a long task. These tasks will have. For know, a manual task list will be used, it will be in the folder called, in-dev-docs.

- Number
- Name
- Why Develop
- Pre Requirements and Major Task.
- Post Requirements
- Success Criteria
- Difficulty Estimations

# Evaluation
At the end each task, it will be decided whether completing this task, increased the projects, **Minor Version**, **Major Version** or was responsible for creating a **New Version**. How well the difficulty was estimated. The next task to do, or new tasks to create.

# Design
Some difficult tasks, may need to be tried out, before they are incorporated into the main project, this could be done by creating a new branch, where I could make a draft of the feature. Some tasks would either require, drawing things inside a image editor like Gimp or inkscape, Drawing on a paper diagram (or with a grid drawing application).

# Diagnostics 
It will be important to track how much memory and processing time is being used by the game and it's editor, to prevent bugs that have been caused by forgetting to free memory, or to allow or restrict the use of good programming techniques, that might have a flaw of requiring indirect memory access.

It will also be useful to diagnose whether these are errors when an error is caused by issues related to incorrect timing.

# Dev Logging
All changes to the code base will be logged in a linear way, along with bug fixes.
All bug found will be logged as well, whenever a bug is found, all efforts will be made to find the cause of the bug, then fix it.

# Version Control 
For the game, git will be integrated into the development early, however, there will be attempts to prevent loss of work due to the lack of understanding of git, by reading the documentation of the commands before using it

# New Strategic changes
How will I deal with new strategy changes. I would need to consider, whether it will change the tasks, The versioning rules, what benifit this new strategy will have, 