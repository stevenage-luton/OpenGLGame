# Maze Game By Huw

A short, simple Maze Game in C++ and OpenGL.

# How to open the .exe

Unzip the folder and then double click the .exe. Ensure that libraries are in C:\Users\Public\OpenGL or it probably won't open

# How does the program work?

"main.cpp" is what runs the program. This contains the Render loop and all the models required for it. It's also responsible for detecting and handling collisions between objects. The "Player" class is fairly simple, containing information nessecary for calculating collisions (position + radius, for sphere collisions) as well as a constant "MOVESPEED" and a Move method, which take directions calculated in "main" from key inputs, and use them to update the position of the player.

The "MazeGameLevel" class ("maze_game.h" is the filename; more clarity was needed) contains a vector of GameObjects, as well as two methods: A public method that loads a level from a given .txt file, and a private InitializeLevel method called by the loader. The InitializeLevel method is responsible for parsing the input jagged array. A position vector3 starts at the top left corner of the maze, and updates its position after each square of the grid is placed (Empty, Solid, or Victory Chest). If required, a GameObject is created at it's coordinates each time and pushed back to a Vector containing all the GameObjects for the level.

The "GameObject" class, similar to the player class, contains information required for collisions. Essentially, it's position, and size on each axis (it's collider is a box). It also contains a method for setting the Model of the MVP for each instance of the object to be placed.

# What makes the program special?

It is a fully playable game with 3 levels selected from randomly. The player has to know how to navigate mazes (and avoid common tricks used to keep the player looping around in circles) to be able to complete it. There is also a victory condition if the player reaches the treasure at the end of the maze.

## Where was the idea from?

Lab 8- Procedural generation gave me the idea to try a game that featured procedural generation, and I knew that maze generation algorithms existed, so I wanted to combine the two. Unfortunately I didn't know how to program a maze generation algorithm, so I decided to simply use pre-made maps that were loaded from files.

## What I started with

I started with the material used for Lab 9- Model Loading(https://github.com/AmethystBird/COMP3016-Lab-Tasks/tree/main/Lab9). The libraries and materials used were the ones provided: GLAD, GLM, GLEW, ASSimp, and the LearnOpenGL "shader" and "model" files. I also attempted to incorporate similar object-oriented design patterns to the "LearnOpenGL" "breakout" tutorial (https://learnopengl.com/In-Practice/2D-Game/Breakout), though there were issues with this as will be detailed soon.

## How did I make mine unique?

The object-oriented design proved harder than it seemed. I had to write it from the ground up, porting over functionality piecemeal to my new classes and stopping when something broke. I was able to use object instancing to draw many copies of the same object by only storing information about the model in a GameObject class, but not attaching ownership of any actual model, mesh, or shader to any GameObjects. Instead, we draw an instance of that object at the right location according to the GameObject's size and location variables.

Additionally, the LearnOpenGL "breakout" tutorial gives an example of using fileloading to get information required to load a 2d screen full of blocks. I used that as a jumping off point for being able to load different mazes at random when the program loads, to give variety to the player. The only similarities are that they split functionality between two methods- one that reads the file, and one that parses it. Unfortunately everything else had to be done by hand, as my GameObject class, Player class and Level Class all had very different intended functionality by virtue of the fact the player needed to be able to navigate a 3d space instead of just shooting 2d sprites at other 2d sprites.

## Did I start with a given project?

I started with the material used for Lab 9- Model Loading. https://github.com/AmethystBird/COMP3016-Lab-Tasks/tree/main/Lab9 

MouseLook code is mostly the same, as are the vertex and fragment shaders. Playermovement needed to be changed to keep the player fixed to the same Y plane (it would be too easy to solve the maze if the player could just fly around freely as in the lab), as did the process of rendering objects. Other features such as AABB collisions (sphere and box), loading levels, and victory conditions were added by me.

# Video Link

https://youtu.be/C6eGYFOuosk