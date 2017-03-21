#include "GameObject.h"

GameObject::GameObject()
{
	m_name = " ";
}

void GameObject::Destroy()
{
	SDL_FreeSurface(surface);
	surface = NULL;
	glDeleteVertexArrays(1, &_VAO);
	delete this;
}


std::string GameObject::GetName()
{
	return m_name;
}

void GameObject::SetName(std::string _name)
{
	m_name = _name;
}

SDL_Surface* GameObject::GetSurface()
{
	return surface;
}

void GameObject::Translate(float x, float y, float z)
{
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;
	m_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), m_pos), glm::vec3(1.0f, 1.0f, 0.5f));
}

void GameObject::ApplyModel(std::string _file)
{
	ObjectLoader* objLoader = new ObjectLoader();

	Object m_object = objLoader->LoadModel(_file);

	if (m_object.GetVertices().size() >= 1)
	{
		_VAO = 0;

		glGenVertexArrays(1, &_VAO);

		glBindVertexArray(_VAO);

		_numVertices = m_object.GetVertices().size();
		printf("Vertices loaded: %u | Triangles loaded: %u\n\n", _numVertices, _numVertices / 3);


		GLuint buffer = 0;

		glGenBuffers(1, &buffer);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		glBufferData(GL_ARRAY_BUFFER, m_object.GetVertices().size() * sizeof(glm::vec3), &m_object.GetVertices()[0], GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);


		GLuint normalBuffer = 0;

		glGenBuffers(1, &normalBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

		glBufferData(GL_ARRAY_BUFFER, m_object.GetNormals().size() * sizeof(glm::vec3), &m_object.GetNormals()[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);



		GLuint texcoordBuffer = 0;

		glGenBuffers(1, &texcoordBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);

		glBufferData(GL_ARRAY_BUFFER, m_object.GetTexCoords().size() * sizeof(glm::vec2), &m_object.GetTexCoords()[0], GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glDisableVertexAttribArray(0);
	}
	else
	{
		std::cout << "Error: Object has vertices less than 1." << std::endl;
	}

	

	delete objLoader;
}

void GameObject::Draw()
{
	glBindVertexArray(_VAO);

	glDrawArrays(GL_TRIANGLES, 0, _numVertices);
	glBindVertexArray(0);
	
	glBindVertexArray(0);

}

bool GameObject::SetSurfaceTexture(const char *_file)
{
	surface = SDL_LoadBMP(_file);
	if (surface == NULL)
	{
		printf("Unable to load file %s! SDL Error: %s\n", _file, SDL_GetError());
		return false;
	}
	return true;
}