#include "CsComponents.h"

CsComponent::CsComponent() {}
CsComponent::~CsComponent() {}

void CsComponent::update() {}
void CsComponent::init() {}


CsVec2PositionComponent::CsVec2PositionComponent(glm::vec2 positon, glm::vec2 size, float angle) { 
	_pos = positon; ID = "CsVec2PositionComponent";
_size = size;
_angle = angle;
}
CsVec2PositionComponent::~CsVec2PositionComponent() {}
glm::vec2& CsVec2PositionComponent::getPosition() {
	return _pos;
}

glm::vec2 & CsVec2PositionComponent::getSize()
{
	return _size;
}

float CsVec2PositionComponent::getAngle()
{
	return _angle;
}

CsBodyComponent::CsBodyComponent(glm::vec2 position, b2World * world, glm::vec2 size) {
	ID = "CsBodyComponent";
	_size = size;

	_bodyDef.type = b2_dynamicBody; //this will be a dynamic body

	_bodyDef.position.Set(position.x - _size.x / 2, position.y - _size.y / 2); //set the starting position
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
CsBodyComponent::~CsBodyComponent() { _body->GetWorld()->DestroyBody(_body); }
glm::vec2& CsBodyComponent::getPosition() {
	return glm::vec2(_body->GetPosition().x, _body->GetPosition().y);
}
glm::vec2& CsBodyComponent::getSize() {
	return _size;
}
float CsBodyComponent::getAngle() {
	return _body->GetAngle();
}
void CsBodyComponent::update() {
	
}

CsDrawingBodyComponent::CsDrawingBodyComponent(SpriteBatch* s, CsBodyComponent* c, GLuint tex) {
	
	ID = "CsDrawingBodyComponent";
	spriteBatch = s;
	_bodyComp = c;
	_tex = tex;
}
CsDrawingBodyComponent::~CsDrawingBodyComponent()
{
}
;
void CsDrawingBodyComponent::update() {
	spriteBatch->draw(glm::vec4((_bodyComp->getPosition().x * 64 -_bodyComp->getSize().x * 32), (_bodyComp->getPosition().y * 64 - _bodyComp->getSize().y * 32), _bodyComp->getSize().x * 64, _bodyComp->getSize().y * 64), glm::vec4(0, 0, 1.0f, -1.0f), _tex, .5f, ColorRGBA8(255, 255, 255, 255), _bodyComp->getAngle());
}



CsDrawingPositionComponent::CsDrawingPositionComponent(SpriteBatch* s, CsVec2PositionComponent* c, GLuint tex) {
	_posComp = c;
	spriteBatch = s;
	_tex = tex;
}
CsDrawingPositionComponent::~CsDrawingPositionComponent()
{
}
;
void CsDrawingPositionComponent::update() {
	spriteBatch->draw(glm::vec4((_posComp->getPosition().x * 64 - _posComp->getSize().x *32), (_posComp->getPosition().y * 64 - _posComp->getSize().y * 32), _posComp->getSize().x * 64, _posComp->getSize().y * 64), glm::vec4(0, 0, 1.0f, -1.0f), _tex, .5f, ColorRGBA8(255, 255, 255, 255), _posComp->getAngle());
}
