#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <glm.hpp>

class Object {

public:
	std::vector<glm::vec3> GetVertices();
	void SetVertices(std::vector<glm::vec3> _vertices);

	std::vector<glm::vec3> GetNormals();
	void SetNormals(std::vector<glm::vec3> _normals);

	std::vector<glm::vec2> GetTexCoords();
	void SetTexCoords(std::vector<glm::vec2> _texcoords);

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texcoords;

};

#endif