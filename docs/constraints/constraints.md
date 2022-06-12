
## Constraints ##

### Physical ###
As a game the methods of inputs that the player can provide are likely to be A **Keyboard**, **Mouse** and its buttons, on a desktop computer, A **touch screen** on a phone or tablet and a  **game controller** on a game console, these are interchangable, 

All of these devices have a way to respond to the user through audio means through the speaker and visual means through the **monitor(screen)**. The screen is physically red,green, blue LED's uniformly laid out as to create the illusion of an continous image. With game controllers, haptic feedback is also a possible way to respond to the user, along with the game controllers LED.

Computers have a limited amount of **persistent storage**, either this is **Hard Drive** an **SSD**. There will be decisions to determine whether, external devices such as a flash drive or a CD is a suitable means of storage.

Things that are currently being used by an application such as a game is stored in **Main Memory(RAM)** or in **CPU Cache**, these can be accesssed faster than persistant storage, but it is also limited, currently ranging from (4 - 16 GB).

### Logical ###
This game will be running on someone(organisations) operating system. Operating Systems such as Windows, Mac and Gnu/Linux. For Mobile Android, iOS; for game consoles, Microsoft Game Console, Sony Game Console and Nintendo Game Console or Streaming based Game Console like Stadia. On Windows, Mac and Linux, applications that output graphics are usually enclosed inside windows, that can be closed, minimised, resized, hiden and overlayed; unless the game is put in full screen mode. Apple and Android both have apps, have access to device features such as notifications. These containers, imposed by the operating system usually have API's for programming langauges, that provide a logical interface between the physical components of the computational device.


A web browser is almost like it's own operating system, it has even more constrainst in that, the lowest level that everything in the browser comes down to **HTML**, **CSS** and **Javascript** (sometimes **Web Assembly**). Javascript has API's that provide a logical interface to the physical devices.

### GPU Constrainst ###
Modern GPU's Specialise in the ability to render complex 3D forms out of triangles. For different operating systems, there are diffrent API's for sending instructions for the GPU, render these triangles directly to the screen and also to loading models onto the **GPU's memory**. Although most GPU's are not optimised for this, it is possible to do raycasting on the GPU by either enclosing the world inside a 3D model or a fullscreen quad. Raycasting should be used sparingly, since for every pixel(fragment) that is visible, the color in the scene must be searched for.

### Programatic ###

C++ requires a build script to be ran to compile the program, the compilation step needs to know which files are headers, source files and object files, the last stage requires the object files to be combined, to create an executable.

The game logic is likely to be the same across all potential platforms, however, The Operating systems input API and Rendering API and constraints are likely to be where these diverge.

I have good reasons to use C++ For this project, since it fulfills the requirement for a programming language, it doesn't do garbage collection, a task that could slow down the game, if I don't decide when memory should be free. I syntactically understand the programming language.

To prevent the program from becoming difficult to maintain, the code will have lots of comments in the hezader files, explaining what problem the declared programming construct (function, class, etc) is able to solve, The naming of constructs will follow those of a reliable c++ formatting guide, this may be set to be enforced by the IDE, to avoid miscommitment.

If The game is to be ported to web, I would need to either transpile C++ code to javascript

### Reducing Decoupling ###

The rendering will be entirely seperate from the game logic. Any rendering system for the game will need to be able to interprete commands, for drawing 3D and 2D game objects.

The game logic will be entirely seperate from the API that provides input from the device peripherals. Although the game is decoupled from the peripherals, there is a mediator that is needed between the operating systems input api, and the game's input system.