#include "SphereCollider.h"

bool SphereCollider::IsColliding(std::vector<float> _pos1, std::vector<float> _pos2, float _raidus1, float _radius2)
{
	/*
	Due to my own engine limitations, along with time constraints,
	I was unable to implement the SphereCollider component properly into the engine.
	While this function is never called currently, given the correct values from
	two GameObjects, this function *should* correctly return whether or not they are colliding.
	*/


	int dx = _pos1[0] - _pos2[0];
	int dy = _pos1[1] - _pos1[1];
	int dz = _pos1[2] - _pos1[2];

	int radii = _raidus1 + _radius2;

	if ((dx * dx) + (dy * dy) + (dz * dz) < radii * radii)
	{
		return true;
	}
	else
	{
		return false;
	}
}