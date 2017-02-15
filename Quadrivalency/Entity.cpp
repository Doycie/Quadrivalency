#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{
}

 void Entity::init(glm::vec2 position,glm::vec2 size, b2World * world, TextureCache &texCache, bool staticBody) {


	_size =size;
	if(!staticBody)
	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body
	else {
		_bodyDef.type = b2_staticBody; //this will be a dynamic body
	}
	_bodyDef.position.Set(position.x, position.y); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	_dynamicBody = world->CreateBody(&_bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_size.x, _size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	_dynamicBody->CreateFixture(&boxFixtureDef);

}

void Entity::draw(SpriteBatch& spriteBatch) {
	spriteBatch.draw(glm::vec4(_dynamicBody->GetPosition().x, _dynamicBody->GetPosition().y, _size.x, _size.y), glm::vec4(0, 0, 1.0f, 1.0f), _tex, 1.0f, ColorRGBA8(255, 255, 255, 255));

}
void Entity::update() {

}
void Entity::input(InputManager& inputManager) {
	 std::cout << "asd";
}