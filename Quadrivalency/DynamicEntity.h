#pragma once
#include "EntityBody.h"
class DynamicEntity : public EntityBody
{
public:
	DynamicEntity();
	~DynamicEntity();

	void init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache);
	void draw(SpriteBatch& spriteBatch);

private:


};

