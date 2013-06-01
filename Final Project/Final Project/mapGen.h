// Grid library interface
	#include <vector>
	
	extern const int MAXROWS = 20;
	extern const int MAXCOLS = 20;
	extern char mapInput[MAXROWS][MAXCOLS];
	extern int map[MAXROWS][MAXCOLS-10];

	bool readFile();
	void storeBlocks(vector<float> xPos, vector<float>yPos, vector<float>zPos);

	
