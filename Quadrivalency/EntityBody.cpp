#include "EntityBody.h"



EntityBody::EntityBody()
{
}


EntityBody::~EntityBody()
{
}


void EntityBody::init(glm::vec2 position, glm::vec2 size, b2World * world,GLuint tex) {
	_size = size;
	_tex = tex;
	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body

	_bodyDef.position.Set(position.x - _size.x / 2, position.y - _size.x / 2); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	_bodyDef.gravityScale = 0.0f;
	_body = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x / 2.0f, _size.y / 2.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.filter.maskBits = 0x0000;
	_body->CreateFixture(&boxFixtureDef);
}

void EntityBody::draw(SpriteBatch& spriteBatch) {
	spriteBatch.draw(glm::vec4((_body->GetPosition().x - _size.x / 2) * 64, (_body->GetPosition().y - _size.y / 2) * 64, _size.x * 64, _size.y * 64), glm::vec4(0, 0, 1.0f, -1.0f), _tex, .1f, ColorRGBA8(255, 255, 255, 255));

}