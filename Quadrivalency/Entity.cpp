#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{
}

 void Entity::init(glm::vec2 position,glm::vec2 size, b2World * world, TextureCache &texCache) {


	
	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body
	
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

void Entity::draw(SpriteBatch& spriteBatch) {
	spriteBatch.draw(glm::vec4((_body->GetPosition().x-_size.x/2) * 64 , (_body->GetPosition().y-_size.y/2 )* 64, _size.x*2 * 64, _size.y*2 * 64), glm::vec4(0, 0, 1.0f, 1.0f), _tex, 1.0f, ColorRGBA8(255, 255, 255, 255));

}
void Entity::update() {

}

void Entity::input(InputManager & inputManager)
{
}
