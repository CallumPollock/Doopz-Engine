#include "Object.h"

void Object::ApplyModel()
{
	if (Object::GetVertices().size() >= 1)
	{
		_VAO = 0;

		glGenVertexArrays(1, &_VAO);

		glBindVertexArray(_VAO);

		_numVertices = GetVertices().size();


		GLuint buffer = 0;

		glGenBuffers(1, &buffer);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		glBufferData(GL_ARRAY_BUFFER, GetVertices().size() * sizeof(glm::vec3), &GetVertices()[0], GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		if (GetNormals().size() > 0)
		{
			GLuint normalBuffer = 0;

			glGenBuffers(1, &normalBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

			glBufferData(GL_ARRAY_BUFFER, GetNormals().size() * sizeof(glm::vec3), &GetNormals()[0], GL_STATIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}
		

		if (GetTexCoords().size() > 0)
		{

			GLuint texcoordBuffer = 0;

			glGenBuffers(1, &texcoordBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);

			glBufferData(GL_ARRAY_BUFFER, GetTexCoords().size() * sizeof(glm::vec2), &GetTexCoords()[0], GL_STATIC_DRAW);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glDisableVertexAttribArray(0);
		}
	}
	else
	{
		std::cout << "Error: Object has vertices less than 1." << std::endl;
	}
}

glm::vec3 Object::GetPosition()
{
	return m_pos;
}

void Object::Translate(glm::vec3 _pos)
{
	m_pos.x += _pos.x;
	m_pos.y += _pos.y;
	m_pos.z += _pos.z;
	m_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), m_pos), glm::vec3(m_sca.x, m_sca.y, m_sca.z));
}

void Object::Scale(glm::vec3 _sca)
{
	m_sca.x += _sca.x;
	m_sca.y += _sca.y;
	m_sca.z += _sca.z;
	m_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), m_pos), glm::vec3(m_sca.x, m_sca.y, m_sca.z));
}

void Object::Draw()
{

	glBindVertexArray(_VAO);

	glDrawArrays(GL_TRIANGLES, 0, _numVertices);
	glBindVertexArray(0);

}

bool Object::SetSurfaceTexture(const char *_file)
{
	m_surface = SDL_LoadBMP(_file);
	if (m_surface == NULL)
	{
		printf("Unable to load file %s! SDL Error: %s\n", _file, SDL_GetError());
		return false;
	}
	return true;
}

std::vector<glm::vec3> Object::GetVertices()
{
	return m_vertices;
}

void Object::SetVertices(std::vector<glm::vec3> _vertices)
{
	m_vertices = _vertices;
	_numVertices = m_vertices.size();
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

Object::~Object()
{
	glDeleteVertexArrays(1, &_VAO);
}