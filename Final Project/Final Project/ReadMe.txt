CS 174 Project README

Roy Chen, Kenny Chow, Collin Yen

-----Project Introduction-----

Our project is called Space Runner.  The point of the game is to pilot a 
spaceship via keyboard arrow keys to avoid blocks and get the highest score 
possible by reaching the end of the game.  The user has a limited amount
of lives, and a life is deducted each time the user hits a block. Users can 
utilize the provided map, or create custom maps by modifying the map file.  The 
coordinates are specified by placing an 'x' with a random generation of the block's 
vertical position, or a column of blocks with a 'w'. A 'b' indicates
the lack of a block at the specified coordinate.  

Coordinates for block placement are read in from the specified map file.  Map data
is read in and converted to block coordinates, which is stored in a vector called 
"blocks," which stores the structure cubePos that contains x, y, and z coordinates
of a generated block.  The arrow keys determine the movement of the ship and triggers
the movement animation.  Score is a continuously running counter, and lives are 
decremented as each collision between a block and the spaceship is detected.  

-----Project Result/Implementation-----
1) Instead of bump mapping, we implemented collision detection as our advanced
topic.
	-Collision detection is implemented in the didCollide() function.
	-The test is made to see if there is an intersection between the spaceship 
	and the volume of the cube.  
	-There is an iteration through all of the generated blocks to test if 
	any intersection with the spaceship occurs
2) Custom user generated maps are implemented
3) All movement (horizontal, as well as vertical) is implemented
	-We made a decision to limit it to keyboard movement, due to the 
	spacing of the blocks required to make the game playeable.  
	Mouse movement would have made the game too easy, allowing users to 
	easily circumvent the blocks of a user-generated map. Keyboard movment
	allowed us to specify how much the ship moved with each keystroke,
	ensuring that the ship would shift in alignment with the block placement.
	-vertical movement is limited to one unit up and one unit down from 
	the center.  Users are only able to specify location of blocks on a 2D plane,
	so we limited random generation of the vertical coordinates of the blocks
	to ensure that the game would not be too easy (so blocks would not be spaced 
	out too far apart)  
4) Score and menu are implemented 
5) Lives and display of lives are implemented
6) Power ups and other obstacles were not implemented.
	
-----To generate a custom map -----
*NOTE* map must be named "map.txt" and placed in the project folder

The following are the letters accepted to create a map:
An 'o' represents where the user starts.
A 'b' represents empty space (no block present).
An 'x' is where a user wants to place the block.  
A 'w' creates a column of blocks at the designated coordinates

-Each new row must be started with a letter ('b', 'o', or 'x')
-each letter is delineated by a tab ('\t')
-To generate the next row of blocks, press "enter" to insert a new row
-The cube's vertical position is randomly generated in the map,
unless user chooses to use the column functionality. 

-----Keyboard movement-----
Press 'Enter' key: start/restart a game
Press left arrow key: move ship left
Press right arrow key: move ship right
Press up arrow key: move ship up
Press down arrow key: move ship down
