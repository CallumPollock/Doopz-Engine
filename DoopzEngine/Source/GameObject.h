#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

class GameObject {

public:
	GameObject();
	void Destroy();

	std::string GetName();
	void SetName(std::string _name);

	//glm::mat4 m_modelMatrix;

private:


	std::string m_name;

	//GLuint _VAO;
	unsigned int _numVertices;

};

#endif