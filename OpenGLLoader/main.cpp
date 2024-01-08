#pragma once

//STD
#include <iostream>

//GLAD
#include <glad/glad.h>

//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp> //Access to the value_ptr

//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "maze_game.h"

#include "game_object.h"

//LEARNOPENGL
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>

//GENERAL
#include "main.h"

#include "player.h"

#include <random>


using namespace std;
using namespace glm;

vector<GameObject> gameObjects;

MazeGameLevel* level1;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];

//Transformations
mat4 mvp;

mat4 model;

mat4 view;

mat4 projection;

int windowWidth = 1280;
int windowHeight = 720;

Player* player;



GLfloat bgR = 0.25f;
GLfloat bgG = 0.0f;
GLfloat bgB = 1.0f;
GLfloat bgA = 1.0f;


//Transformations
//Relative position within world space
vec3 cameraPosition = vec3(0.0f, 0.0f, 3.0f);
//The direction of travel
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
//Up position within world space
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

//Camera sidways rotation
float cameraYaw = -90.0f;
//Camera vertical rotation
float cameraPitch = 0.0f;
//Determines if first entry of mouse into window
bool mouseFirstEntry = true;
//Positions of camera from given last frame
float cameraLastXPos = 800.0f / 2.0f;
float cameraLastYPos = 600.0f / 2.0f;

//Variables for DeltaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

vec3 playerStartPosition = vec3(-7.0f, 0.5f, -7.0f);

const string FILE_NAMES[] = { "level1.txt", "level2.txt", "level3.txt" };

const string FILE_FOLDER = "levelData/";

bool gameRunning = true;


int main()
{
    //Initialisation of GLFW
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Maze", NULL, NULL);

    //Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }

    srand(time(NULL));
    string fileToLoad = FILE_NAMES[rand() % 3];

    //Binds OpenGL to window
    glfwMakeContextCurrent(window);

    //Initialisation of GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "couldn't load GLAD" << std::endl;
        return -1;
    }

    //Loading of shaders
    Shader Shaders("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    Model Rock("media/rock/Rock07-Base.obj");
    Model Tree("media/tree/yamaboushi_tan_6000_a_spr1.obj");

    Model Chest("media/chest/chest.obj");

    Model Brick("media/cube/centreCube.obj");

    Model Floor("media/cube/plane.obj");

    Model SkyBox("media/skybox/skybox.obj");

    Model victoryScreen("media/victory/victoryScreen.obj");

    Shaders.use();


    GameObject Ground(vec3(0.0f, 0.8f, 0.0f), vec3(1.0f, 1.0f, 1.0f), false, "floor");

    GameObject VictoryScreen(vec3(0.0f, 0.0f, -15.0f), vec3(1.0f, 1.0f, 1.0f), false, "victory");

    GameObject SkyBoxObject(vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), false, "skybox");


    level1 = new MazeGameLevel();

    level1->LoadDataFromFile(FILE_FOLDER + fileToLoad);

    //Sets the viewport size within the window to match the window size of 1280x720
    glViewport(0, 0, 1280, 720);

    //Sets the framebuffer_size_callback() function as the callback for the window resizing event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Sets the mouse_callback() function as the callback for the mouse movement event
    glfwSetCursorPosCallback(window, mouse_callback);

    //Model matrix
    model = mat4(1.0f);
    //Scaling to zoom in
    model = scale(model, vec3(0.025f, 0.025f, 0.025f));
    //Looking straight forward
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    //Elevation to look upon terrain
    model = translate(model, vec3(0.0f, -2.f, -1.5f));

    //Projection matrix
    projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.05f, 100.0f);

    player = new Player(playerStartPosition,2.0f);

    player->radius = 0.7f;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ////Model matrix
    //model = mat4(1.0f);
    ////model = mat4(1.0f);
    ////Scaling to zoom in
    //model = scale(model, vec3(4.0f, 4.0f, 4.0f));
    ////Rotation to look down
    //model = rotate(model, radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));
    ////Movement to position further back
    //model = translate(model, vec3(0.0f, 1.f, -1.5f));

    ////View matrix
    //mat4 view = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 1.0f, 0.0f));

    ////Projection matrix
    //mat4 projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    //// Model-view-projection matrix uniform for vertex shader
    //mat4 mvp = projection * view * model;
    /*int mvpLoc = glGetUniformLocation(program, "mvpIn");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));*/



    //Render loop
    while (glfwWindowShouldClose(window) == false)
    {

        //get Delta Time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        

        //Input
        ProcessUserInput(window); //Takes user input

        //Rendering
        glClearColor(bgR, bgG, bgB, bgA); //Colour to display on cleared window
        glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer
        glClear(GL_DEPTH_BUFFER_BIT); //Might need

        glEnable(GL_CULL_FACE); //Discards all back-facing triangles
        glEnable(GL_DEPTH_TEST);

        cameraPosition = player->position;

        //Transformations & Drawing
        //Viewer orientation
        view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp); //Sets the position of the viewer, the movement direction in relation to it & the world up direction

        //draw normal objects
        if (gameRunning)
        {
            //Rock
            model = mat4(1.0f);
            model = translate(model, vec3(0.0f, 0.0f, -1.0f));
            model = scale(model, vec3(0.05f, 0.05f, 0.05f));
            SetMatrices(Shaders);


            Rock.Draw(Shaders);

            //Brick
            //model = scale(model, vec3(10.0f, 10.0f, 10.0));
            /*model = mat4(1.0f);
            model = translate(model, vec3(0.0f, 0.0f, -1.0f));
            model = scale(model, vec3(0.5f, 0.5f, 0.5f));
            SetMatrices(Shaders);
            Brick.Draw(Shaders);*/

            for (GameObject obj : level1->Blocks) {
                model = obj.SetModel();

                SetMatrices(Shaders);
                if (obj.type == "block")
                {
                    Brick.Draw(Shaders);
                }
                else if (obj.type == "chest")
                {
                    Chest.Draw(Shaders);
                }

            }

            //draw floor

            model = Ground.SetModel();
            SetMatrices(Shaders);
            Floor.Draw(Shaders);

            model = SkyBoxObject.SetModel();
            SetMatrices(Shaders);
            SkyBox.Draw(Shaders);

            //Rock (reorient MVP back to starting values)
            //model = scale(model, vec3(0.1f, 0.1f, 0.1f));

            //SetMatrices(Shaders);

            //Tree (changes MVP in relation to past values)
            model = mat4(1.0f);
            model = translate(model, vec3(-3.0f, 0.0f, 0.0f));
            model = scale(model, vec3(0.0005f, 0.0005f, 0.0005f));
            SetMatrices(Shaders);
            Tree.Draw(Shaders);

            //Rock (reorient MVP back to starting values)

            model = scale(model, vec3(20.0f, 20.0f, 20.0f));
            SetMatrices(Shaders);
        }
        else
        {
            model = VictoryScreen.SetModel();
            SetMatrices(Shaders);
            victoryScreen.Draw(Shaders);
        }


        




        //Refreshing
        glfwSwapBuffers(window); //Swaps the colour buffer
        glfwPollEvents(); //Queries all GLFW events
    }
    //Safely terminates GLFW
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Resizes window based on contemporary width & height values
    glViewport(0, 0, width, height);
}

void ProcessUserInput(GLFWwindow* window)
{
    //Closes window on 'exit' key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    Player* playerPlusMove = new Player(player->position, player->radius);

    if (!gameRunning)
    {
        return;
    }

    //WASD controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        //cameraPosition += movementSpeed * cameraFront;

        playerPlusMove->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "W");

        if (TestCollisions(*playerPlusMove) == false)
        {
            if (TestCollisions(*player) == false)
            {
                player->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "W");
            }
            
        }

    
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        //cameraPosition -= movementSpeed * cameraFront;
        playerPlusMove->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "S");
        if (TestCollisions(*playerPlusMove) == false)
        {
            if (TestCollisions(*player) == false)
            {
                player->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "S");
            }
            
        }

    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        //cameraPosition -= normalize(cross(cameraFront, cameraUp)) * movementSpeed;
        playerPlusMove->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "A");

        if (TestCollisions(*playerPlusMove) == false)
        {
            if (TestCollisions(*player) == false)
            {
                player->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "A");
            }
            
        }


    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {

        playerPlusMove->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "D");

        if (TestCollisions(*playerPlusMove) == false)
        {
            if (TestCollisions(*player) == false)
            {
                player->Move(deltaTime, sin(radians(cameraYaw)), cos(radians(cameraYaw)), "D");
            }
            
        }
        //cameraPosition += normalize(cross(cameraFront, cameraUp)) * movementSpeed;
        
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Initially no last positions, so sets last positions to current positions
    if (mouseFirstEntry)
    {
        cameraLastXPos = (float)xpos;
        cameraLastYPos = (float)ypos;
        mouseFirstEntry = false;
    }

    if (!gameRunning)
    {
        return;
    }

    //Sets values for change in position since last frame to current frame
    float xOffset = (float)xpos - cameraLastXPos;
    float yOffset = cameraLastYPos - (float)ypos;

    //Sets last positions to current positions for next frame
    cameraLastXPos = (float)xpos;
    cameraLastYPos = (float)ypos;

    //Moderates the change in position based on sensitivity value
    const float sensitivity = 0.025f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    //Adjusts yaw & pitch values against changes in positions
    cameraYaw += xOffset;
    cameraPitch += yOffset;

    //Prevents turning up & down beyond 90 degrees to look backwards
    if (cameraPitch > 89.0f)
    {
        cameraPitch = 89.0f;
    }
    else if (cameraPitch < -89.0f)
    {
        cameraPitch = -89.0f;
    }

    //Modification of direction vector based on mouse turning
    vec3 direction;
    direction.x = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    direction.y = sin(radians(cameraPitch));
    direction.z = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    cameraFront = normalize(direction);

}

void SetMatrices(Shader& ShaderProgramIn)
{
    mvp = projection * view * model; //Setting of MVP
    ShaderProgramIn.setMat4("mvpIn", mvp); //Setting of uniform with Shader class
}

bool PlayerCollision(Player& player, GameObject& object)
{
    float playerXDist = abs(player.position.x - object.position.x);
    float playerYDist = abs(player.position.y - object.position.y);
    float playerZDist = abs(player.position.z - object.position.z);

    //there's definitely no collision if the absolute value of our position - the object's position is greater than our radius + half the object size.

    if (playerXDist >= (object.size.x/2.0f + player.radius)) 
    { 
        return false; 
    }
    if (playerYDist >= (object.size.y/ 2.0f + player.radius)) 
    { 
        return false; 
    }
    if (playerZDist >= (object.size.z/2.0f + player.radius)) 
    { 
        return false; 
    }

    //there's definitely a collision if the absolute value of our position - the object's position is less than half the object size.
    if (playerXDist < (object.size.x/2.0f)) 
    { 
        return true; 
    }
    if (playerYDist < (object.size.y/2.0f)) 
    { 
        return true; 
    }
    if (playerZDist < (object.size.z/2.0f)) 
    { 
        return true; 
    }

    //if it's inconclusive, get the distance from us to the object squared
    float distanceToCornerSquared = ((playerXDist - object.size.x) * (playerXDist - object.size.x)) + ((playerYDist - object.size.y) * (playerYDist - object.size.y) + ((playerZDist - object.size.z) * (playerZDist - object.size.z)));
    
    //then check against our radius
    bool collision = distanceToCornerSquared < (player.radius* player.radius);

    //return if there was a collision
    return collision;
}

bool TestCollisions(Player &player) {
    for (GameObject& object : level1->Blocks) {
        if (object.solid)
        {
            if (PlayerCollision(player, object))
            {
                cout << "COLLISION" << endl;
                return true;
            }
        }
        else
        {
            if (PlayerCollision(player, object))
            {
                cout << "NON SOLID COLLISION" << endl;
                VictoryCollision();
                return false;
            }
        }
    }

    return false;
}

void VictoryCollision() {
    gameRunning = false;

    player->position = vec3(0.0f, 0.0f, 0.0f);

    cameraFront = vec3(0.0f, 0.0f, -1.0f);

    bgR = 0.0f;
    bgG = 0.0f;
    bgB = 0.0f;
    bgA = 0.0f;
}