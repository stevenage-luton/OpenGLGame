#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"

using std::string;

class MazeGameLevel {
public:

	std::vector<GameObject> Blocks;

	MazeGameLevel() {};

	void LoadDataFromFile(std::string fileName);

private:
	void InitializeLevel(std::vector<std::vector<int>> levelData);
};