#include "Object.h"

std::vector<glm::vec3> Object::GetVertices()
{
	return m_vertices;
}

void Object::SetVertices(std::vector<glm::vec3> _vertices)
{
	m_vertices = _vertices;
}

std::vector<glm::vec3> Object::GetNormals()
{
	return m_normals;
}

void Object::SetNormals(std::vector<glm::vec3> _normals)
{
	m_normals = _normals;
}

std::vector<glm::vec2> Object::GetTexCoords()
{
	return m_texcoords;
}

void Object::SetTexCoords(std::vector<glm::vec2> _texcoords)
{
	m_texcoords = _texcoords;
}