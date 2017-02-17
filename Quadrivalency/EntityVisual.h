#pragma once
#include "Entity.h"
class EntityVisual : public Entity
{
public:
	EntityVisual();
	~EntityVisual();

	virtual void init(glm::vec2 position, glm::vec2 size, GLuint tex);
	virtual void draw(SpriteBatch & spriteBatch);
private:
	glm::vec2 _position;

};

