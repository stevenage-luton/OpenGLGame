#include "player.h"

Player::Player() :
	radius(2.0f), position(0.0f, 0.0f, 0.0f) {}

Player::Player(glm::vec3 position, float radius) :
	position(position), radius(radius) {}

void Player::Move(float deltaTime, float xSpeed, float zSpeed, string keyPress) {

	xSpeed = xSpeed * PLAYER_MOVESPEED * deltaTime;

	zSpeed = zSpeed * PLAYER_MOVESPEED * deltaTime;

	if (keyPress == "W")
	{
		position.x += zSpeed;
		position.z += xSpeed;
	}
	else if (keyPress == "S")
	{
		position.x -= zSpeed;
		position.z -= xSpeed;
	}
	else if (keyPress == "A")
	{
		position.x += xSpeed;
		position.z -= zSpeed;
	}
	else if (keyPress == "D")
	{
		position.x -= xSpeed;
		position.z += zSpeed;
	}


}