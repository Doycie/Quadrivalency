#include "StaticEntity.h"



StaticEntity::StaticEntity()
{
}


StaticEntity::~StaticEntity()
{
}


void StaticEntity::init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache) {


	_size = size;
	_bodyDef.type = b2_staticBody; //this will be a static body
	_bodyDef.position.Set(position.x, position.y); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	_body = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x, _size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	_body->CreateFixture(&boxFixtureDef);

}