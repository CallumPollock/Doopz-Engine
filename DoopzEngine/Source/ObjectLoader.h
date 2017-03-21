
#ifndef _OBJECTLOADER_H__
#define _OBJECTLOADER_H__

// This is the main SDL include file
#include <SDL.h>
#include <iostream>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm.hpp>

#include "Object.h"

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	Object LoadModel(std::string _file);

protected:
	
	unsigned int _numVertices;
	std::string line, iss2;
	float value, a, b, c;
	int n, t, v, f;
	bool objLoaded;
	glm::vec3 objData;

	Object m_object;

};

#endif
