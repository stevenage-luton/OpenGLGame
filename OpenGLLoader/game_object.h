#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/ext/matrix_transform.hpp>
#include <string>


using std::string;


class GameObject {
public:

	GameObject( glm::vec3 position, glm::vec3 size, bool solid, string type);

	glm::vec3 position;
	
	glm::vec3 size;

	glm::mat4 SetModel();

	string type;

	bool solid;
};


#endif