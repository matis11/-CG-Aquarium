#ifndef AQUARIUM_H
#define AQUARIUM_H

#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include "fish.h"
using namespace std;
using namespace glm;

void drawAquarium(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif