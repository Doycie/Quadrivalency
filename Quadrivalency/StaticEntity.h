#pragma once
#include "EntityBody.h"
class StaticEntity : public EntityBody
{
public:
	StaticEntity();
	~StaticEntity();

	 void init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex);
	 virtual void draw(SpriteBatch& spriteBatch);
private:


};

