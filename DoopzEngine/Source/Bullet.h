#ifndef _BULLET_H
#define _BULLET_H

#include "Cube.h"
#include "Object.h"

class Bullet : public Cube
{
public:
	Bullet();
	~Bullet();
	void Update(float _deltaTime);

};

#endif