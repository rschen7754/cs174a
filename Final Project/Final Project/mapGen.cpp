
#include "iostream"
#include "fstream"
#include <string>
#include <vector>
using namespace std;


std::vector<char> mapInputVec2;
std::vector<std::vector <int>> mapVec;

bool readFile()
{
	ifstream mapfile;
	mapfile.open ("map.txt");
	char inputLetter = 'z';
	int mapWidth = 0;
	while (inputLetter != '\n')
	{
		inputLetter = mapfile.get();
		mapWidth++;
	}
	mapfile.close();

	mapfile.open ("map.txt");
	if (mapfile.is_open())
	{
		//bool eofReached = false;
		while (mapfile.eof() == false)
		{
			std::string str;
			std::getline(mapfile,str);
			//char tChar;
			//mapfile >> tChar;
			string::iterator it;
			int index = 0;
			for ( it = str.begin() ; it < str.end(); it++ ,index++)
			{
				mapInputVec2.push_back(*it);
			}
			mapInputVec2.push_back('\n');
		}
	}
	else 
	{
		cout << "Error in opening the file.";
		return false;
	}
	mapfile.close();

	//filter out tabs and new lines
	char tempChar;
	std::vector<int> tempVec;
	//for (int i = 0; i< mapWidth; i++)
	std::vector<char>::iterator it = mapInputVec2.begin();
	int sizeInput = mapInputVec2.size();
	int counter = 0;
	while(counter < sizeInput)
	{
		tempChar = *it; 
		if (tempChar == 'o')
		{
			tempVec.push_back(2);
		}
		else if (tempChar == 'b')
		{
			tempVec.push_back(0);
		}
		else if (tempChar == 'x')
		{
			tempVec.push_back(1);
		}
		else if (tempChar == '\n' && counter+1 < sizeInput)
		{
			mapVec.push_back(tempVec);
			tempVec.clear();
		}
		++it;
		counter++;
	}
	return true;
}

void storeBlocks(vector<float> &xPos, vector<float> &yPos, vector<float> &zPos)
{

	vector< vector<int> >::iterator row;
	vector<int>::iterator col;
	int itr1=0;
	int itr2=0;
	int xshift = 0;
	for (col = mapVec.begin()->begin(); col != mapVec.begin()->end(); col++)
	{
		xshift++;
	}
	xshift = (xshift*25)/2; //to center player
	for (row = mapVec.begin(); row != mapVec.end(); row++)
	{
		//create wall on right side
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(-15); // vertical position
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(0);
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(15);
		for (col = row->begin(); col != row->end(); col++)
		{
			//if (map[i][j] == 1)
			if (*col == 1)
			{
				xPos.push_back((float)(itr1*25-xshift)); //left and right
				zPos.push_back((float)(itr2*50+300)); //into the screen
				int randomNum = (rand() % 3);
				if (randomNum == 0)
					yPos.push_back(-15); // vertical position
				else if (randomNum == 1)
					yPos.push_back(0);
				else
					yPos.push_back(15);
			}
			itr1++;
		}
		//create wall on left side
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(-15); // vertical position
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(0);
		xPos.push_back((float)(itr1*25-xshift)); //left and right
		zPos.push_back((float)(itr2*50+300)); //into the screen
		yPos.push_back(15);

		itr1 = 0;
		itr2++;
	}
	////Test code
	//vector<float>::iterator counter = xPos.begin();
	//vector<float>::iterator counter2 = yPos.begin();
	//vector<float>::iterator counter3 = zPos.begin();
	//for (counter = xPos.begin(); counter != xPos.end(); counter++)
	//{
	//	cout<< *counter << ' '<< *counter2 << ' ' << *counter3 << endl;
	//	counter2++;
	//	counter3++;
	//}
	return;
}