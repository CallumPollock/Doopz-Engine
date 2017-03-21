#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SDL.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "ObjectLoader.h"
#include "SphereCollider.h"

class GameObject {

public:
	GameObject();
	void Destroy();

	void ApplyModel(std::string _file);
	void Draw();

	bool SetSurfaceTexture(const char *_file);
	SDL_Surface* GetSurface();
	std::string GetName();
	void SetName(std::string _name);

	glm::mat4 m_modelMatrix;

	SphereCollider m_collider;

	void Translate(float x, float y, float z);

private:
	
	glm::vec3 m_pos;

	std::string m_name;
	SDL_Surface* surface = NULL;

	GLuint _VAO;
	unsigned int _numVertices;

};

#endif