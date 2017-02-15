#pragma once
#include "StaticEntity.h"
class Wall :
	public StaticEntity
{
public:
	Wall();
	~Wall();

	void init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache);

};

