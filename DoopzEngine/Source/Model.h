#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "Object.h"

class Model : public Object
{
public:
	Model();
	~Model();

	void LoadModel(std::string _file);
	

private:
	
	
	std::string line, iss2;
	float value, a, b, c;
	int n, t, v, f;
	bool objLoaded;
	glm::vec3 objData;
};

#endif