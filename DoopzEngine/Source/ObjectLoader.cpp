
#include "ObjectLoader.h"

ObjectLoader::ObjectLoader()
{

}

Object ObjectLoader::LoadModel(std::string _file)
{
	std::ifstream obj;

	std::cout<<"Opening " << _file << ".obj \n";

	obj.open(_file + ".obj");


	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texcoords;


	std::vector<glm::vec3> m_Fvertices;
	std::vector<glm::vec3> m_Fnormals;
	std::vector<glm::vec2> m_Ftexcoords;

	std::vector<unsigned int> m_vertexIndices;
	std::vector<unsigned int> m_normalIndices;
	std::vector<unsigned int> m_uvIndices;

	if (obj.is_open())
	{
		objLoaded = true;
		std::cout<<"Opened " << _file << ".obj successfully!\n";

		while (!obj.eof())
		{
			std::getline(obj, line);
			std::istringstream iss(line);

			if (line[0] == 'v')
			{
				if (line[1] == 'n')
				{
					glm::vec3 normals;

					iss >> line >> normals.x >> normals.y >> normals.z;

					m_normals.push_back(normals);


				}
				else if (line[1] == 't')
				{
					glm::vec2 texcoords;

					iss >> line >> texcoords.x >> texcoords.y;

					m_texcoords.push_back(texcoords);
				}
				else
				{
					glm::vec3 vertices;
					iss >> line >> vertices.x >> vertices.y >> vertices.z;

					m_vertices.push_back(vertices);
				}
			}
			else if (line[0] == 'f')
			{
				for (std::string::iterator it = line.begin(); it != line.end(); ++it)
				{
					if (*it == '/')
					{
						line.erase(it);
						line.insert(it, ' ');
					}
				}
				unsigned int VertexIndex[3], UVIndex[3], NormalIndex[3];

				std::istringstream iss2(line);

				iss2 >> line >> VertexIndex[0] >> UVIndex[0] >> NormalIndex[0] >> VertexIndex[1] >> UVIndex[1] >> NormalIndex[1] >> VertexIndex[2] >> UVIndex[2] >> NormalIndex[2];

				m_vertexIndices.push_back(VertexIndex[0]);
				m_vertexIndices.push_back(VertexIndex[1]);
				m_vertexIndices.push_back(VertexIndex[2]);
				m_uvIndices.push_back(UVIndex[0]);
				m_uvIndices.push_back(UVIndex[1]);
				m_uvIndices.push_back(UVIndex[2]);
				m_normalIndices.push_back(NormalIndex[0]);
				m_normalIndices.push_back(NormalIndex[1]);
				m_normalIndices.push_back(NormalIndex[2]);
			}
		}

		for (unsigned int i = 0; i < m_vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = m_vertexIndices[i];
			unsigned int uvIndex = m_uvIndices[i];
			unsigned int normalIndex = m_normalIndices[i];

			glm::vec3 vertex = m_vertices[vertexIndex - 1];
			glm::vec2 uv = m_texcoords[uvIndex - 1];
			glm::vec3 normal = m_normals[normalIndex - 1];	

			m_Fvertices.push_back(vertex);
			m_Ftexcoords.push_back(uv);
			m_Fnormals.push_back(normal);

			m_object.SetVertices(m_Fvertices);
			m_object.SetTexCoords(m_Ftexcoords);
			m_object.SetNormals(m_Fnormals);
		}
	}
	else
	{
		std::cout<<"Unable to load " << _file << ".obj. Please ensure the file is valid and that it is in the correct directory." <<std::endl;
	}
	
	
	return m_object;


}

ObjectLoader::~ObjectLoader()
{
	
	// TODO: delete the VBOs as well!
}