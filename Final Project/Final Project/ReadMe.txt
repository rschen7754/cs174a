CS 174 Project README

Roy Chen, Kenny Chow, Collin Yen

-----Implementation-----
1) Instead of bump mapping, we implemented collision detection as our advanced
topic.
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
	to ensure that the game would not be too easy (blocks would not be spaced out
	too far apart)  
4) Score and menu are implemented 
5) Health was not implemented due to the relatively slow pace of the game.  
	-It was determined that it would make the game too easy, so it was decided
	that any collision would result in the user having to restart
6) Power ups and other obstacles were not implemented.
	
-----To generate a custom map -----
*NOTE* map must be named "map.txt" and placed in the project folder

The following are the letters accepted to create a map:
An 'o' represents where the user starts.
A 'b' represents empty space (no block present).
An 'x' is where a user wants to place the block.  

-Each new row must be started with a letter ('b', 'o', or 'x')
-each letter is delineated by a tab ('\t')
-To generate the next row of blocks, press "enter" to insert a new row
-The cube's vertical position is randomly generated in the map 

-----Keyboard movement-----
Press 'Enter' key: start/restart a game
Press left arrow key: move ship left
Press right arrow key: move ship right
Press up arrow key: move ship up
Press down arrow key: move ship down
