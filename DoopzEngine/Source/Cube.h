#ifndef _CUBE_H
#define _CUBE_H

#include "Model.h"

class Cube : public Model
{
public:
	Cube();
	~Cube();
	void Update(float _deltaTime);

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texcoords;

};

#endif