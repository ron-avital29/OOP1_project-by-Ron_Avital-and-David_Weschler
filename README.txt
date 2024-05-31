Project - Amazing Escape: Mouse Maze (using SFML)

Written by Ron Avital, and David Weschler.

In this OOP project, we built the game "Amazing Escape". 
The game involves a mouse collecting cheese while avoiding cats. 
In this exercise, we practiced interface design, the usage of complex classes, 
data transformation between objects, references, and consts. The game is built in a 
CMake environment, and the code is written in C++, utilizing the SFML library.
The project is object-oriented.

Files:

- main.cpp: Activates the game
- SingleTon.h: a singleton class that holds the textures, soundbuffers and const variables used in the game
- Menu.h: Defines the Menu class
- Menu.cpp: Implements the Menu class, incharge of the buttons - 'sound', 'exit', 'help' and 'start'
- Controller.h: Defines the class that is responsible for running the game
- Controller.c: Implements the functions defined in the header
- GameInfo.h: Defines the the gameInfo class
- GameInfo.cpp: Implements the gameInfo class,, incharge of holding the player stats and showing them on the window
- Base.h: Definition of an Abstract class that holds basic members of sfml
- Base.cpp: Implementation of the base class functions
- Animal.h: (Inherets from Base) Definition of an Abstract that represents a animal (cat/mouse) 
- Animal.cpp: Implementation of the Animal class
- Mouse.h: (Inherets from Animal) Defines the class of the Mouse, the main character of the game
- Mouse.cpp: Implements the functions - get/set function and more
- Cat.h: (Inherets from Animal) Defines the class of the Cats, the side charactesr of the game
- Cat.cpp: Implements the functions - get/set function and more
- StaticObj.h: (Inherets from Base) Definition of an Abstract that represents a non-movable game object (wall, key, cheese, door, present...)
- StaticObj.cpp: Implementation of the StaticObj class
- Wall.h:(Inherets from StaticObj) Defines a Wall class 
- Wall.cpp: Implements the wall class
- Cheese.h: (Inherets from StaticObj) Defines a Cheese class 
- Cheese.cpp: Implements the Cheese class
- Door.h: (Inherets from StaticObj) Defines a Door class 
- Door.cpp: Implements the Door class
- Key.h: (Inherets from StaticObj) Defines a Key class 
- Key.cpp: Implements the Key class
- Present.h: (Inherets from StaticObj) Defines an abstract present class 
- Present.cpp: Implements the present class
- Bomb.h: (Inherets from Present) Defines a bomb class 
- Bomb.cpp: Implements the Bomb class
- Heart.h: (Inherets from Present) Defines a Heart class 
- Heart.cpp: Implements the Heatr class
- Frozen.h: (Inherets from Present) Defines a Frozen class 
- Frozen.cpp: Implements the Frozen class
- Faster.h: (Inherets from Present) Defines a Faster class 
- Faster.cpp: Implements the Faster class
- KillCat.h: (Inherets from Present) Defines a KillCat class 
- KillCat.cpp: Implements the KillCat class
- playlist.txt: Holds the names of the level files.
- level(+number).txt: Level files containing the actual levels.
- CMakeLists.txt: Add any level you want to include, duplicating a line and changing the relevant name.
- UML.txt: The class diagram of the game.
- In Resources: PNG, JPG, OGG, and TTF files for graphics and sound.

Dominant Data Structures:
- The program uses vectors from the std library to hold static and movable objects.
- A singleton class is used to hold textures and sounds in the game.

Notable Algorithms:

The cat movement mechanism in Cat.cpp employs a chasing algorithm. 
Prior to each cat's movement, it evaluates the four available directions 
to determine the new location with the shortest distance from the cat. 
Subsequently, the cat moves to that location, provided it is feasible. 
If the cat collides with a wall or the window border, it sets its destination 
to a random location on the board until the next collision, after which its 
destination returns to the mouse's original location.

Design Overview:
The game incorporates mouse and cat objects, where the mouse symbolizes the user, 
and the cats function as automated enemies. The cats movements are directly influenced 
by the behavior of the mouse, establishing an interactive dynamic between the user and the automatic adversaries.

Notes:
To introduce a new level to the game, follow these steps:
1) Create a new text file for the level, named level0n.txt (replace 'n' with the level number), and save it in the 'resources' folder.
2) Add a line of code in the CMakeLists.txt file, as previously instructed.
3) Update the 'playlist.txt' file by adding the new level filename on a new line.


