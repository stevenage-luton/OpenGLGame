
// Cube.h
#ifndef CUBE_H
#define CUBE_H
#pragma once
//#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Cube {
public:
    Cube(const char* vertexPath, const char* fragmentPath, const char* texturePath);
    ~Cube();

    void render(glm::mat4 projection,glm::mat4 view);

    // Setters for transformation properties
    void setPosition(glm::vec3 setposition) {
        position = setposition;
    }
    void setRotation(glm::vec3 setrotation) {
        position = setrotation;
    };
    void setScale(glm::vec3 setscale) {
        scale = setscale;
    };

    void setupBuffers();
    void loadTexture(const char* texturePath);

private:
    GLuint VAO, VBO, texture;
    Shader shader;

    glm::mat4 model;

    // Transformation properties
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(2.0f, 2.0f, 2.0f);

    
};

#endif // CUBE_H