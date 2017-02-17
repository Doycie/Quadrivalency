#include "Ball.h"



Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex) {

	_size = size;
	_tex = tex;
	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body

	_bodyDef.position.Set(position.x - _size.x / 2, position.y - _size.x / 2); //set the starting position
	_bodyDef.angle = 0; //set the starting angle
	
	_body = world->CreateBody(&_bodyDef);
	// Create the circles

	b2CircleShape circleShape;
	circleShape.m_radius = _size.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = 0.8f;
	circleDef.restitution = .9f;
	circleDef.friction = 0.5f;
	circleDef.filter.maskBits = 0x000F;

	// Bottom circle
	circleShape.m_p.Set(0.0f, 0.0f);
	_body->CreateFixture(&circleDef);
}

