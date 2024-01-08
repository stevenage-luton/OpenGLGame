
#include "game_object.h"

GameObject::GameObject(glm::vec3 position, glm::vec3 size, bool solid, string type):
	position(position), size(size), solid(solid), type(type) {};

glm:: mat4 GameObject::SetModel() {

	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, position);

	//center the model
	model = glm::translate(model, glm::vec3(0.0f, -1.0f * size.y, 0.0f));

	model = scale(model, size);


	return model;
}

