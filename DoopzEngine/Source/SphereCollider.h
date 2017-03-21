#ifndef _SPHERECOLLIDER_H
#define _SPHERECOLLIDER_H

#include <vector>
#include <glm.hpp>

class SphereCollider {

public:
	bool IsColliding(std::vector<float> _pos1, std::vector<float> _pos2, float _raidus1, float _radius2);
};

#endif