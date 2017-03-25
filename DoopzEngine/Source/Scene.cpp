
#include "Scene.h"

#include <iostream>
#include <SDL.h>

using namespace std;

Scene::Scene()
{
	for (int i = 0; i < m_objectsInScene; i++)
	{
		GameObject *newGameObject;
		m_gameObjects.push_back(newGameObject);
		m_gameObjects[i] = new GameObject();
	}

	printf("%i GameObjects in scene\n", m_gameObjects.size());

	m_gameObjects[0]->ApplyModel("models/cube");
	m_gameObjects[0]->SetName("Cube 1");
	m_gameObjects[1]->ApplyModel("models/cube");
	m_gameObjects[1]->SetName("Cube 2");

	_cube1Angle = 0.0f;
	_cameraAngleX = 0.0f, _cameraAngleY = 0.0f;


	_shaderModelMatLocation = 0;
	_shaderViewMatLocation = 0;
	_shaderProjMatLocation = 0;

	_shaderDiffuseColLocation = 0;
	_shaderEmissiveColLocation = 0;
	_shaderWSLightPosLocation = 0;

	_shaderTexSamplerLocation = 0;

	BuildShaders();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0, 1, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 1, 1, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	m_gameObjects[0]->Translate(0.0f, 0.0f, 0.0f);
	m_gameObjects[1]->Translate(0.0f, 0.0f, 0.0f);

	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.5f));

	_projMatrix = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);

}

void Scene::SetScreen(SDL_Surface* _screen)
{
	m_screen = _screen;
}

void Scene::Update(float deltaTs)
{
	_viewMatrix = glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.5f)), _cameraAngleX, glm::vec3(1, 0, 0)), _cameraAngleY, glm::vec3(0, 1, 0));

	Draw();

}

void Scene::Draw()
{
	glUseProgram(_shaderProgram);

	glUniform4fv(_shaderWSLightPosLocation, 1, glm::value_ptr(m_gameObjects[0]->m_modelMatrix * glm::vec4(0, 0, 0, 1)));

	glUniform1i(_shaderTexSamplerLocation, 0);


	glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
	glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(_projMatrix));

	glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);

	//glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 0.0f, 0.0f))));
	glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(m_gameObjects[0]->m_modelMatrix));

	glUniform3f(_shaderDiffuseColLocation, 1.0f, 0.3f, 0.3f);
	m_gameObjects[0]->Draw();
	m_gameObjects[1]->Draw();



	glUseProgram(0);
}




bool Scene::CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}

void Scene::BuildShaders()
{
	const GLchar *vShaderText = "#version 430 core\n\
						 layout(location = 0) in vec4 vPosition;\n\
						 layout(location = 1) in vec3 vNormalIn;\n\
						 layout(location = 2) in vec2 vTexCoordIn;\n\
						 \n\
						 uniform mat4 modelMat;\n\
						 uniform mat4 invModelMat;\n\
						 uniform mat4 viewMat;\n\
						 uniform mat4 projMat;\n\
						 \n\
						 uniform vec4 worldSpaceLightPos = {1,0.0,1,1};\n\
						 \n\
						 out vec3 vNormalV;\n\
						 out vec3 eyeSpaceLightPosV;\n\
						 out vec3 eyeSpaceVertPosV;\n\
						 \n\
						 void main()\n\
						 {\n\
								gl_Position = projMat * viewMat * modelMat * vPosition;\n\
								\n\
								eyeSpaceVertPosV = vec3(viewMat * modelMat * vPosition);\n\
								eyeSpaceLightPosV = vec3(viewMat * worldSpaceLightPos);\n\
								\n\
								vNormalV = mat3(viewMat * modelMat) * vNormalIn;\n\
						 }";

	//fragment shader
	const GLchar *fShaderText = "#version 430 core\n\
								in vec3 vNormalV;\n\
								in vec3 eyeSpaceLightPosV;\n\
								in vec3 eyeSpaceVertPosV;\n\
								\n\
								uniform vec3 lightColour = {1,1,1};\n\
								uniform vec3 emissiveColour = {0,0,0};\n\
								uniform vec3 ambientColour  = {0.1f,0.1f,0.2f};\n\
								uniform vec3 diffuseColour  = {0.8f,0.1f,0.1f};\n\
								uniform vec3 specularColour = {0.0f,1.0f,0.0f};\n\
								uniform float shininess     = 50.0f;\n\
								uniform float alpha         = 1.0f;\n\
								vec3 worldSpaceLightPos = {1,0.0,1};\n\
								float intensity;\n\
								\n\
								out vec4 fragColour;\n\
								\n\
								uniform sampler2D tex1;\n\
								\n\
								void main()\n\
								{\n\
									vec3 lightDir = normalize( eyeSpaceLightPosV - eyeSpaceVertPosV );\n\
									vec3 normal = normalize( vNormalV );\n\
									\n\
										vec3 texColour = diffuseColour;//vec3(texture(tex1,texCoord));\n\
										vec3 diffuse = vec3(0,0,0);\n\
										\n\
										vec3 specular = vec3(0,0,0);\n\
										\n\
										fragColour = vec4( emissiveColour + ambientColour*texColour + diffuse + specular, alpha);\n\
										normalize(worldSpaceLightPos);\n\
										normalize(vNormalV);\n\
										intensity = dot(worldSpaceLightPos, vNormalV);\n\
										\n\
										fragColour = vec4(0.0f, intensity, intensity, 1.0f);\n\
								}";


	_shaderProgram = glCreateProgram();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vShader, 1, &vShaderText, NULL);

	glCompileShader(vShader);

	if (!CheckShaderCompiled(vShader))
	{
		std::cerr << "ERROR: failed to compile vertex shader" << std::endl;
		return;
	}

	glAttachShader(_shaderProgram, vShader);


	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	if (!CheckShaderCompiled(fShader))
	{
		std::cerr << "ERROR: failed to compile fragment shader" << std::endl;
		return;
	}
	glAttachShader(_shaderProgram, fShader);


	glLinkProgram(_shaderProgram);

	GLint linked;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(_shaderProgram, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return;
	}



	glUseProgram(_shaderProgram);
	_shaderModelMatLocation = glGetUniformLocation(_shaderProgram, "modelMat");
	_shaderViewMatLocation = glGetUniformLocation(_shaderProgram, "viewMat");
	_shaderProjMatLocation = glGetUniformLocation(_shaderProgram, "projMat");

	_shaderDiffuseColLocation = glGetUniformLocation(_shaderProgram, "diffuseColour");
	_shaderEmissiveColLocation = glGetUniformLocation(_shaderProgram, "emissiveColour");
	_shaderWSLightPosLocation = glGetUniformLocation(_shaderProgram, "worldSpaceLightPos");

	_shaderTexSamplerLocation = glGetUniformLocation(_shaderProgram, "tex1");
}

unsigned int Scene::LoadTexture(std::string filename)
{
	SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	if (!image)
	{
		std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
		return 0;
	}

	SDL_FreeSurface(image);


	return 0;
}

Scene::~Scene()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		std::cout<<"Destroying " << m_gameObjects[i]->GetName() << "...\n";
		m_gameObjects[i]->Destroy();
	}
	m_gameObjects.clear();

}