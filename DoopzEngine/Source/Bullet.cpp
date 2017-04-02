#include "Bullet.h"

Bullet::Bullet()
{
	
}

void Bullet::Update(float _deltaTime)
{
	Translate(glm::vec3(1.0f * _deltaTime, 0.0f, 0.0f));
	Rotate(glm::vec3(_deltaTime*3.21f, 0.0f, _deltaTime*3.21f));
}

Bullet::~Bullet()
{

}