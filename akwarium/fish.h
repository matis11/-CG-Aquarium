#ifndef FISH_H
#define FISH_H

const float PI = 3.141592653589793f;

#include <vector>
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

namespace Models {

	class Model {
	public:
		virtual void drawSolid();
		virtual void drawWire();
	protected:
		int vertexCount;
		float *vertices;
		float *vertexNormals;
		float *texCoords;
		void loadOBJ(char filename[]);
	};
}

namespace Models {

	class Fish : public Model {
	public:
		Fish();
		virtual ~Fish();
	};
	extern Fish fish;
}

#endif