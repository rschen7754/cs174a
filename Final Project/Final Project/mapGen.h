// Grid library interface

	extern const int MAXROWS = 20;
	extern const int MAXCOLS = 20;
	extern char mapInput[MAXROWS][MAXCOLS];
	extern int map[MAXROWS][MAXCOLS-10];

	bool readFile();
	void storeBlocks();
	
