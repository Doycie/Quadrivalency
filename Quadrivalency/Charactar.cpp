#include "Charactar.h"



Charactar::Charactar()
{
}


Charactar::~Charactar()
{
}

void Charactar::init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex, bool internet)
{
	_internet = internet;
	
	_size = size;



	// Make the body
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(position.x, position.y);
	_bodyDef.fixedRotation = 1.0f;
	_body = world->CreateBody(&_bodyDef);

	// Create the box
	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x / 2.0f, ((size.y - size.x)) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = 0xFFF0;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 3;
	fixtureDef.friction = 1.0f;
	_fixtures[0] = _body->CreateFixture(&fixtureDef);

	// Create the circles
	b2CircleShape circleShape;
	circleShape.m_radius = _size.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = 3;
	circleDef.friction = 1.0f;
	circleDef.filter.categoryBits = 0xFFF0;

	// Bottom circle
	circleShape.m_p.Set(0.0f, (-size.y + size.x) / 2.0f);
	_fixtures[1] = _body->CreateFixture(&circleDef);

	// Top Circle
	circleShape.m_p.Set(0.0f, (_size.y - _size.x) / 2.0f);
	_fixtures[2] = _body->CreateFixture(&circleDef);

	//DynamicEntity::init(position, size, world, texCache);
	_tex = tex;
}

 void Charactar::input(InputManager& inputManager,std::vector<Entity*> entities) {


	 if (_internet) {
		
	 }
	 else {

	
	 if (inputManager.isKeyDown(SDLK_LEFT)) {
		 _body->ApplyForceToCenter(b2Vec2(-80.0, 0.0), true);
		 _direction = -1;
	 }
	 else if (inputManager.isKeyDown(SDLK_RIGHT)) {
		 _body->ApplyForceToCenter(b2Vec2(80.0, 0.0), true);
		 _direction = 1;
	 }
	 else {
		 _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x * 0.95, _body->GetLinearVelocity().y));
	 }

	 _isPunching = false;
	 _punchCooldown--;
	 // Check for punch
	 if (inputManager.isKeyPressed(SDLK_x) && _punchCooldown <0) {
		 _isPunching = true;
		 _punchCooldown = 30;

		 Ball* b = dynamic_cast<Ball*>(entities[7]);

		 float x = (_body->GetPosition().x) - b->getBody()->GetPosition().x;
		 float y = (_body->GetPosition().y) - b->getBody()->GetPosition().y;

		 if (sqrt(x*x + y*y) < 2) {
			 b->getBody()->ApplyLinearImpulseToCenter(b2Vec2(x < 0 ? 5:-5,y <0 ? 5:-5),true);
		 }
	 }


	 float MAX_SPEED = 7.0f;
	 if (_body->GetLinearVelocity().x < -MAX_SPEED) {
		 _body->SetLinearVelocity(b2Vec2(-MAX_SPEED, _body->GetLinearVelocity().y));
	 }
	 else if (_body->GetLinearVelocity().x > MAX_SPEED) {
		 _body->SetLinearVelocity(b2Vec2(MAX_SPEED, _body->GetLinearVelocity().y));
	 }

	 // Loop through all the contact points
	 _onGround = false;
	 for (b2ContactEdge* ce = _body->GetContactList(); ce != nullptr; ce = ce->next) {
		 b2Contact* c = ce->contact;
		 if (c->IsTouching()) {
			 b2WorldManifold manifold;
			 c->GetWorldManifold(&manifold);
			 // Check if the points are below
			 bool below = false;
			 for (int i = 0; i < b2_maxManifoldPoints; i++) {
				 if (manifold.points[i].y < _body->GetPosition().y - _size.y / 2.0f +_size.x / 2.0f + 0.01f) {
					 below = true;
					 break;
				 }
			 }
			 if (below) {
				 _onGround = true;
				 // We can jump
				 if (inputManager.isKeyPressed(SDLK_z)) {
					 _body->ApplyLinearImpulse(b2Vec2(0.0f, 70.0), b2Vec2(0.0f, 0.0f), true);
					 break;
				 }
			 }
		 }
	 }

	 }

	

}
 void Charactar::draw(SpriteBatch& spriteBatch) {


	 glm::vec4 uvrect = glm::vec4(0.5f,0,0.5f,-1);
	 if (_punchCooldown >0) {
		 uvrect.x = 0;
	 }
	 spriteBatch.draw(glm::vec4((_body->GetPosition().x - _size.x / 2) * 64, (_body->GetPosition().y - _size.y / 2) * 64, _size.x * 64, _size.y * 64), uvrect, _tex, .5f, ColorRGBA8(255, 255, 255, 255), _body->GetAngle());


 }