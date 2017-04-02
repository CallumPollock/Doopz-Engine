#ifndef _PLANE_H
#define _PLANE_H

#include "Object.h"

class Plane : public Object
{
public:
	Plane();
	~Plane();

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texcoords;

};

#endif