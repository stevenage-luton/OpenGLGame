#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/ext/matrix_transform.hpp>


class GameObject {
public:

	GameObject( glm::vec3 position, glm::vec3 size, bool solid);

	glm::vec3 position;
	
	glm::vec3 size;

	glm::mat4 SetModel();

	bool solid;
};


#endif