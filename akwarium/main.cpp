#include"GL/glew.h"
#include"GL/glut.h"
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include"aquarium.h"

using namespace glm;
using namespace std;


void displayFrame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void initializeGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK!= err){
		fprintf(stderr,"Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout,"Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0.41, 0.57, 0.83, 1); // Clear background with black color
	glfwSetKeyCallback(window, key_callback); //Register key event processing procedure
	glEnable(GL_LIGHTING); // Turn on lighting mode
	glEnable(GL_LIGHT0); //Turn on default light 0
	glEnable(GL_DEPTH_TEST); //Turn on hidden surface removal via depth buffer
	glEnable(GL_COLOR_MATERIAL); //Make glColor procedures work on object material settings


}

int main(int argc, char** argv) {
	GLFWwindow* window; //creating new window
	if (!glfwInit()) { //Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(1000, 500, "Aquarium", NULL, NULL);
	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	//glfwSwapInterval(1); //nie wiem co robi ale w projekcie by³o :D 
	initializeGLEW();
	initOpenGLProgram(window);
	glfwSetTime(0); 
	 
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		drawAquarium(window);
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now
	}

	glfwDestroyWindow(window); 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}