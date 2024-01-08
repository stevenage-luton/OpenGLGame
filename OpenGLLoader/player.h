#pragma once

#include "glm/ext/vector_float3.hpp"
#include <string>

using std::string;

class Player {
public:
	float radius;
	glm::vec3 position;

	const float PLAYER_MOVESPEED = 1.0f;

	Player();
	Player(glm::vec3 position, float radius);

	void Move(float deltaTime, float xSpeed, float zSpeed, string keyPress);

};