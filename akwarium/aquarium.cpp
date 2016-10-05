#include"aquarium.h"


float fbspeed = 0; // front-back speed
int ymove = 0;
int xmove = 0;
GLfloat angle_y = -90.0f;
GLfloat angle_x = 0.0f;
GLfloat cameraSpeed = 0.05f;
vec3 cameraPos = vec3(0.0f, 0.0f, 10.0f);
vec3 cameraLooksAt = vec3(0.0f, 0.0f, 0.0f);
mat4 P = perspective(10.0f*PI / 90.0f, 2.0f, 1.0f, 50.0f); // Compute projection matrix	

//Key event processing procedure
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
	if (key == GLFW_KEY_D) ymove += 1;
	if (key == GLFW_KEY_A) ymove -= 1;
	if (key == GLFW_KEY_W) xmove += 1;
	if (key == GLFW_KEY_S) xmove -= 1;
	if (key == GLFW_KEY_SPACE) fbspeed = 1;
	if (key == GLFW_KEY_LEFT_ALT) fbspeed = -1;
	}

	if (action == GLFW_RELEASE) {
	if (key == GLFW_KEY_D) ymove -= 1;
	if (key == GLFW_KEY_A) ymove += 1;
	if (key == GLFW_KEY_W) xmove -= 1;
	if (key == GLFW_KEY_S) xmove += 1;
	if (key == GLFW_KEY_SPACE) fbspeed = 0;
	if (key == GLFW_KEY_LEFT_ALT) fbspeed = 0;
	}

}

void drawAquarium(GLFWwindow* window){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/**********************CREATING MATRICES***************************/
	
	mat4 M = mat4(1.0f);

	/*****moving camera left-right up-down********/
	vec3 front;
	if (ymove == 1) angle_y +=1;
	if (ymove == -1) angle_y -=1;
	angle_y = mod(angle_y, 360.0f);
	if (xmove == 1) angle_x += 1;
	if (xmove == -1) angle_x -= 1;
	if ((angle_x > 89.0f) || (angle_x < -89.0f)) angle_x = (fabs(angle_x) / angle_x)*89.0f;
	front.x = cos(radians(angle_y)) * cos(radians(angle_x));
	front.y = sin(radians(angle_x));
	front.z = sin(radians(angle_y)) * cos(radians(angle_x));
	cameraLooksAt = normalize(front);
	/********************************************/
	cameraPos += fbspeed * cameraSpeed * cameraLooksAt; // moving front-back

	mat4 V = lookAt( //Compute view matrix (begining position)
		cameraPos, //where is camera
		cameraPos + cameraLooksAt, // where looks c4amera = where is camera + movement
		vec3(0.0f, 1.0f, 0.0f) //which way: head up
		);
	/****************************************************************/
	

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));

	//glColor3d(0, 1, 0);
	//drawFloor();

	/* Generating objects*/
	int x, z, y, j, i;
	j = 0; i = 0;
	x = 1;
	z = 1;
	y = 1;
	glColor3d(1, 1, 0);
	for (int k = 0; k < 4; k++) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 3; j++) {
				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(value_ptr(V*M));
				Models::fish.drawSolid();
				M = translate(M, vec3(0, 0, z));
			}
			M = translate(M, vec3(x, 0, j*-z));
		}
		M = translate(M, vec3(i*-x, y, 0));
	}
	/*************************/
	
	glfwSwapBuffers(window);
}
