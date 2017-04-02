#ifndef _SCENE_H
#define _SCENE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "GameObject.h"
#include "Object.h"
#include "Cube.h"
#include "Plane.h"
#include "Bullet.h"
#include "Enemy.h"

class Scene
{
public:

	Scene();
	~Scene();

	bool Update(float deltaTs);

	void Draw();

	std::vector<Object*> m_objects;

	void Fire();

protected:	

	enum objectType {
		cube,
		plane,
		bullet,
		enemy
	};

	bool gameEnd = false;

	void UpdateConsole();
	Object* Instantiate(objectType _type, std::string _name, glm::vec3 _pos);

	float m_timer = 0.0;

	glm::mat4 _viewMatrix;

	glm::mat4 _modelMatrix;

	glm::mat4 _projMatrix;

	float _cube1Angle;

	unsigned int _texture;

	GLuint _shaderProgram;


	int _shaderModelMatLocation;
	int _shaderViewMatLocation;
	int _shaderProjMatLocation;

	int _shaderDiffuseColLocation, _shaderEmissiveColLocation;
	int _shaderWSLightPosLocation;

	int _shaderTexSamplerLocation;

	bool CheckShaderCompiled(GLint shader);
	void BuildShaders();

	unsigned int LoadTexture(std::string filename);

};

#endif