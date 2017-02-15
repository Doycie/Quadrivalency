#pragma once
#include "Entity.h"
class StaticEntity : public Entity
{
public:
	StaticEntity();
	~StaticEntity();

	 void init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache);

};

