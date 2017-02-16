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

	
	if (inputManager.isKeyDown(SDLK_RIGHT)) {
		
		_body->ApplyLinearImpulse(b2Vec2(5, 0), _body->GetWorldCenter(),true);
	}

	if (inputManager.isKeyDown(SDLK_LEFT)) {
		_body->ApplyLinearImpulseToCenter(b2Vec2(-5, 0), true);
	}

	if (inputManager.isKeyDown(SDLK_UP)) {
		_body->ApplyLinearImpulseToCenter(b2Vec2(0, 10), true);
	}

}