#ifndef _OBJECT_H
#define _OBJECT_H

#include "GameObject.h"

class Object : public GameObject {

public:
	~Object();

	void ApplyModel();

	void Draw();
	void Translate(glm::vec3 _pos);
	void Scale(glm::vec3 _sca);
	glm::vec3 GetPosition();

	glm::mat4 m_modelMatrix;
	//bool SetSurfaceTexture(const char *_file);

	std::vector<glm::vec3> GetVertices();
	void SetVertices(std::vector<glm::vec3> _vertices);

	std::vector<glm::vec3> GetNormals();
	void SetNormals(std::vector<glm::vec3> _normals);

	std::vector<glm::vec2> GetTexCoords();
	void SetTexCoords(std::vector<glm::vec2> _texcoords);

private:
	GLuint _VAO;
	unsigned int _numVertices;

	SDL_Surface surface;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texcoords;

	glm::vec3 m_pos;
	glm::vec3 m_sca;
};

#endif