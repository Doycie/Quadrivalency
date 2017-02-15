#include "DynamicEntity.h"



DynamicEntity::DynamicEntity()
{
}


DynamicEntity::~DynamicEntity()
{
}


void DynamicEntity::init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache) {
	

	_size = size;
	
	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body

		
	
	_bodyDef.position.Set(position.x, position.y); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	_dynamicBody = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x, _size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	_dynamicBody->CreateFixture(&boxFixtureDef);
	_tex = texCache.getTexture("Npc.png");
}

