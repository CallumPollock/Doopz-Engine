#include "Plane.h"

Plane::Plane()
{
	//Model::LoadModel("cube");
	SetName("Plane");

	m_vertices = {

		{-1.0f, 1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		//Front Tri 2
		//{-1.0f,-1.0f, 1.0f},
		//{1.0f,-1.0f, 1.0f},
		//{1.0f, 1.0f, 1.0f},

	};

	m_normals = {
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},

		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
	};

	m_texcoords = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},

		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f},
	};

	SetVertices(m_vertices);
	SetNormals(m_normals);
	SetTexCoords(m_texcoords);
	ApplyModel();
}

Plane::~Plane()
{

}