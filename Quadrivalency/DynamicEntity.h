#pragma once
#include "Entity.h"
class DynamicEntity : public Entity
{
public:
	DynamicEntity();
	~DynamicEntity();

	void init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache);
	
};

