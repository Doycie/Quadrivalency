#include "Charactar.h"



Charactar::Charactar()
{
}


Charactar::~Charactar()
{
}

void Charactar::init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache)
{
	DynamicEntity::init(position, size, world, texCache);
	_tex = texCache.getTexture("Npc.png");
}

void Charactar::input(InputManager& inputManager) {

	std::cout << "CHARACTAR INPUT";
	if (inputManager.isKeyDown(SDLK_RIGHT)) {
		_dynamicBody->ApplyForceToCenter(b2Vec2(50.0f, 0.0f), true);
	}

	if (inputManager.isKeyDown(SDLK_LEFT)) {
		_dynamicBody->ApplyForceToCenter(b2Vec2(-50.0f, 0.0f), true);
	}

}