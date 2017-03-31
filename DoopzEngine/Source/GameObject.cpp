#include "GameObject.h"

GameObject::GameObject()
{
	m_name = " ";
}

void GameObject::Destroy()
{
	
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