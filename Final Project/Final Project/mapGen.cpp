
#include "iostream"
#include "fstream"
#include <vector>
//#include "main.h"
using namespace std;


const int MAXROWS = 20;
const int MAXCOLS = 20;
char mapInput[MAXROWS][MAXCOLS];
int map[MAXROWS][MAXCOLS-10];

bool readFile()
{
	ifstream mapfile;
	mapfile.open ("map.txt");
	if (mapfile.is_open()) 
	{
		for (int i = 0; i < MAXROWS; i++)
		{
			for (int j = 0; j<MAXCOLS; j++)
			{
				if (!mapfile || mapfile.eof()) 
				{
					break;
				}
				else
				{
					mapfile >> mapInput[i][j];
					//Testing Output
					//cout<<mapInput[i][j];
				}
			}
			//cout << endl;
		}
	}
	else 
	{
		cout << "Error in opening the file.";
		return false;
	}
	mapfile.close();

	//convert to 20x10 map coordinate
	int rowCounter = 0;
	int colCounter = 0;
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			if (mapInput[i][j] == 'o')
			{
				map[rowCounter][colCounter] = 2;
				colCounter++;
			}
			else if (mapInput[i][j] == 'b')
			{
				map[rowCounter][colCounter] = 0;
				colCounter++;
			}
			else if (mapInput[i][j] == 'x')
			{
				map[rowCounter][colCounter] = 1;
				colCounter++;
			}
			/*
			else if (mapInput[i][j] == '\t' || mapInput[i][j] == '\n')
			{
				//map[i][j] = 0;
			} */
			if (colCounter == (MAXCOLS-10))
			{
				colCounter = 0;
				rowCounter++;
			}
		}
	}

	//Test to see if map accurately generated
	/*
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j< 10; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	*/
	return true;
}

void storeBlocks(vector<float> xPos, vector<float>yPos, vector<float>zPos)
{
	//cubePos tempBlock;
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j< MAXCOLS-10; j++)
		{
			if (map[i][j] == 1)
			{
				xPos.push_back = (float)(i*5); //left and right
				zPos.push_back = (float)(j*5); //into the screen
				int randomNum = (rand() % 3);
				if (randomNum == 0)
					yPos.push_back = -15; // vertical position
				else if (randomNum == 1)
					yPos.push_back = 0;
				else
					yPos.push_back = 15;

			}
		}
	}
}