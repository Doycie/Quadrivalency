#include "StaticEntity.h"



StaticEntity::StaticEntity()
{
}


StaticEntity::~StaticEntity()
{
}


void StaticEntity::init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex) {


	_size = size;
	_bodyDef.type = b2_staticBody; //this will be a static body
	_bodyDef.position.Set(position.x, position.y); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	_body = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x/2, _size.y/2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	_body->CreateFixture(&boxFixtureDef);

	_tex = tex;

}

void StaticEntity::draw(SpriteBatch & spriteBatch) {
	spriteBatch.draw(glm::vec4((_body->GetPosition().x - _size.x / 2) * 64, (_body->GetPosition().y - _size.y / 2) * 64, _size.x * 64, _size.y * 64), glm::vec4(0, 0, 1.0f, -1.0f), _tex, .5f, ColorRGBA8(255, 255, 255, 255));

}