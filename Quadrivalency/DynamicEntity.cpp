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
	_bodyDef.angle =0.0f; //set the starting angle
	_body = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x, _size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 3;
	boxFixtureDef.friction = 1;
	_body->CreateFixture(&boxFixtureDef);

}

void DynamicEntity::draw(SpriteBatch & spriteBatch) {
	spriteBatch.draw(glm::vec4((_body->GetPosition().x - _size.x/2 )* 64,( _body->GetPosition().y  - _size.y / 2)* 64, _size.x *64, _size.y * 64), glm::vec4(0, 0, 1.0f, -1.0f), _tex, .5f, ColorRGBA8(255, 255, 255, 255), _body->GetAngle());
}
