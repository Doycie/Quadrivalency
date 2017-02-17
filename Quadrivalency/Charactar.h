#pragma once
#include "DynamicEntity.h"
#include "Entity.h"
#include "Ball.h";
#include <math.h>

class Charactar :
	public DynamicEntity
{
public:
	Charactar();
	~Charactar();

	void init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex);

	virtual void input(InputManager& inputManager,std::vector<Entity*> entities);
	virtual void draw(SpriteBatch& SpriteBatch);

private:

	b2Fixture* _fixtures[3];
	int _direction = 1;
	bool _isPunching = false;
	int _punchCooldown = 0;

	bool _onGround = false;

};

