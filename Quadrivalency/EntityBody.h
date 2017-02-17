#pragma once
#include "Entity.h"
class EntityBody :
	public Entity
{
public:
	EntityBody();
	~EntityBody();

	virtual void init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex);
	virtual void draw(SpriteBatch& spriteBatch);
	b2Body* getBody() {
		return _body;
	}

protected:



	b2Body* _body = nullptr;

	b2BodyDef _bodyDef;
};

