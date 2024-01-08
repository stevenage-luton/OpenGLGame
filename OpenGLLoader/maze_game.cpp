#include "maze_game.h"

#include <fstream>
#include <sstream>

void MazeGameLevel::LoadDataFromFile(string fileName) {
	this->Blocks.clear();

	int blockID;

	string currentLine;

	std::ifstream levelFile(fileName);

	std::vector<std::vector<int>> levelData;

	if (levelFile.is_open())
	{
		while (std::getline(levelFile, currentLine))
		{
			std::istringstream lineToInt(currentLine);
			std::vector<int> row;

			while (lineToInt >> blockID) // read each word separated by spaces
				row.push_back(blockID);
			levelData.push_back(row);
		}
		levelFile.close();
	}
	//error handling so that the init method doesn't try to access an empty vector
	if (levelData.size() > 0)
	{ 
		this->InitializeLevel(levelData);
	}
		
}


void MazeGameLevel::InitializeLevel(std::vector<std::vector<int>> levelData) {
	float blockWidth = 2.0f;
	float blockSizeModifier = 1.0f;

	float chestSizeModifier = 1.0f;

	/*vec3(9.0f, 0.6f, 9.0f), vec3(1.0f, 1.0f, 1.0f), true*/

	glm::vec3 blockPosition = glm::vec3(-9.0f, 0.6f, -9.0f);
	//columns
	int levelHeight = levelData.size();
	//rows
	int levelWidth = levelData[0].size();

	for (int y = 0; y < levelHeight; y++)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			if (levelData[y][x] == 1)
			{
				GameObject block(blockPosition, glm::vec3(blockSizeModifier, blockSizeModifier, blockSizeModifier), true, "block");
				Blocks.push_back(block);
			}else if (levelData[y][x] == 2)
			{
				glm::vec3 chestPosition = blockPosition;
				chestPosition.y += 0.2f;
				GameObject chest(chestPosition, glm::vec3(chestSizeModifier, chestSizeModifier, chestSizeModifier), false, "chest");
				Blocks.push_back(chest);
			}
			blockPosition.x += blockWidth;
		}
		blockPosition.x = -9.0f;
		blockPosition.z += blockWidth;
	}
}