#pragma once
#include "DynamicEntity.h"
class Ball :
	public DynamicEntity
{
public:
	Ball();
	~Ball();
	void init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex);


};

