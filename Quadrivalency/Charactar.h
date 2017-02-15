#pragma once
#include "DynamicEntity.h"
class Charactar :
	public DynamicEntity
{
public:
	Charactar();
	~Charactar();

	void init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache);

	void input(InputManager& inputManager) override ;



};

