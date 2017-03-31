#ifndef _SCENE_H
#define _SCENE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "GameObject.h"
#include "Cube.h"

class Scene
{
public:

	Scene();
	~Scene();

	void ChangeCameraAngleX(float value) { _cameraAngleX += value; };
	void ChangeCameraAngleY(float value) { _cameraAngleY += value; };

	void Update(float deltaTs);

	void Draw();

	void SetScreen(SDL_Surface* _screen);
	std::vector<Cube*> m_cubes;

protected:	

	void UpdateConsole();
	void Instantiate(std::string _name, glm::vec3 _pos);

	float m_timer = 0.0;

	glm::mat4 _viewMatrix;

	glm::mat4 _modelMatrix;

	glm::mat4 _projMatrix;

	float _cube1Angle;
	float _cameraAngleX, _cameraAngleY, _cameraMoveX, _cameraMoveY;

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

	SDL_Surface* m_screen = NULL;

};

#endif