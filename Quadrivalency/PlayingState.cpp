#include "PlayingState.h"


PlayingState::PlayingState()
{
}

PlayingState::~PlayingState()
{

	socket.Close();

	for (unsigned int i = 0; i < _entities.size(); i++) {
		if(!( dynamic_cast<EntityBody*>(_entities[i]) == nullptr))
		_world->DestroyBody(dynamic_cast<EntityBody*>(_entities[i])->getBody());
	}
	for (unsigned int i = 0; i < _entities.size(); i++) {
		delete _entities[i];
	}

	delete _world;
}



void PlayingState::init(Drawer * drawer, bool* running,SpriteBatch* s) {
	_drawer = drawer;
	_running = running;
	_listening = false;
	_world = new b2World(b2Vec2(0.0f, -9.81f));

	spriteBatch = s;

	
	
	
	for (int i = 0; i < 5; i++) {
		bodyComponents.insert(std::pair<int,CsBodyComponent*>(i,(new CsBodyComponent(glm::vec2(5, 5), _world, glm::vec2(1, 1)))));
		drawingBodyComponents.insert(std::pair<int,CsDrawingBodyComponent*>(i, new CsDrawingBodyComponent(spriteBatch, bodyComponents.at(i), texCache.getTexture("Assets/ball.png"))));
		
		entitiesIDs.push_back(i);
	}




	//CHARACTAR
	Charactar *e = new Charactar();
	e->init(glm::vec2(5, 10), glm::vec2(1,2), _world, texCache.getTexture("Assets/birbSheet.png"),false);
	_entities.push_back(e);

	Charactar *k = new Charactar();
	k->init(glm::vec2(5, 10), glm::vec2(1, 2), _world, texCache.getTexture("Assets/birbSheet.png"),true);
	_entities.push_back(k);
	//GROUND
	Wall* w = new Wall();
	w->init(glm::vec2(0, -4), glm::vec2(96, 8), _world, texCache.getTexture("Assets/grass.png"));
	_entities.push_back(w);
	//BOX
	Wall* w2 = new Wall();
	w2->init(glm::vec2(0, 1), glm::vec2(1, 2),_world, texCache.getTexture("Assets/box.png"));
	_entities.push_back(w2);
	//CASTLE
	//EntityVisual* h = new EntityVisual();
	//h->init(glm::vec2(0, 16), glm::vec2(32, 32),  texCache.getTexture("Assets/castle.png"));
	//_entities.push_back(h);

	EntityVisual* i = new EntityVisual();
	i->init(glm::vec2(0, -0.05f), glm::vec2(96, 2), texCache.getTexture("Assets/grassfield.png"));
	_entities.push_back(i);

	//LEFT GOAL
	Wall* f = new Wall();
	f->init(glm::vec2(-20,8), glm::vec2(5, 16), _world, texCache.getTexture("Assets/image2.png"));
	_entities.push_back(f);

	//RIGHT GOAL
	Wall* g = new Wall();
	g->init(glm::vec2(20, 8), glm::vec2(5, 16), _world, texCache.getTexture("Assets/image2.png"));
	_entities.push_back(g);


	//BALL
	Ball* b = new Ball();
	b->init(glm::vec2(5, 12), glm::vec2(0.75f, 0.75f), _world, texCache.getTexture("Assets/ball.png"));
	_entities.push_back(b);

	
	

}

void PlayingState::drawHud(SpriteBatch& hudSpriteBatch, SpriteFont * spriteFont) {
	char buffer[256];

	std::string a = ("x: " + std::to_string(_drawer->getScreenBounds().x) +
		" y: " + std::to_string(_drawer->getScreenBounds().y) +
		" width: " + std::to_string(_drawer->getScreenBounds().z) +
		" height: " + std::to_string(_drawer->getScreenBounds().w));
	/*sprintf_s(buffer, ( "x: " + std::to_string(drawer.getScreenBounds().x )+
	" y: " + std::to_string(drawer.getScreenBounds().y )+
	" width: " + std::to_string(drawer.getScreenBounds().z) +
	" height: " + std::to_string(drawer.getScreenBounds().w)));*/
	sprintf_s(buffer, "X: %d Y: %d Width: %d Height: %d", (int)_drawer->getScreenBounds().x, (int)_drawer->getScreenBounds().y, (int)_drawer->getScreenBounds().z, (int)_drawer->getScreenBounds().w);
	//std::cout << drawer.getScreenBounds().x;

	hudSpriteBatch.begin();

	//std::cout << buffer << std::endl;
	spriteFont->draw(hudSpriteBatch, buffer, glm::vec2(_drawer->getScreenBounds().x, _drawer->getScreenBounds().y), glm::vec2(1.0f / _drawer->cameraPos.z, 1.0f / _drawer->cameraPos.z), 1.0f, ColorRGBA8(255, 255, 255, 255), Justification::LEFT);

	hudSpriteBatch.end();
	hudSpriteBatch.renderBatch();
}
void PlayingState::draw(SpriteBatch& spriteBatch) {
	spriteBatch.begin(GlyphSortType::FRONT_TO_BACK);
	//starmap.draw(spriteBatch);
	//ship.draw(spriteBatch);

	for (unsigned int i = 0; i < _entities.size(); i++) {
		_entities[i]->draw(spriteBatch);
	}
	
	for (std::unordered_map< int,CsDrawingBodyComponent* >::iterator it = drawingBodyComponents.begin(); it != drawingBodyComponents.end(); it++) {
		(*it).second->update();
	}
	for (std::unordered_map< int, CsDrawingPositionComponent* >::iterator it = csDrawingPositionComponents.begin(); it != csDrawingPositionComponents.end(); it++) {
		(*it).second->update();
	}
	//spriteBatch.draw(glm::vec4(0,0, 2000, 500), glm::vec4(0, 0, 1, -1.0f), spriteFont->_texID, 1.0f, ColorRGBA8(255, 255, 255, 255));
	spriteBatch.end();
	spriteBatch.renderBatch();
}


template<typename T>
void PlayingState::removeComponent(T* t , int a) {
	delete t->at(a);
	t->erase(a);
}

void PlayingState::input(InputManager& inputManager) {
	if (inputManager.getMouseWheel() != 0.0f) {
		_drawer->moveCamera(glm::vec3(0.0f, 0.0f, inputManager.getMouseWheel() / 20.0f));
	}

	//if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
	//	int x, y;
	//	SDL_GetMouseState(&x, &y);
	//	glm::vec2 coords = drawer.getWorldCoordinates(glm::vec2(x, y));

	//	if (coords.x >= 0 && coords.x <= 2048 && y >= 0 && y <= 2048) {
	//		ship.addTile(1, texcache, (int)((coords.y) / 64) * 32 + (coords.x / 64));

	//	}

	//}

	//if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
	//	int x, y;
	//	SDL_GetMouseState(&x, &y);
	//	glm::vec2 coords = drawer.getWorldCoordinates(glm::vec2(x, y));

	//	if (coords.x >= 0 && coords.x <= 2048 && y >= 0 && y <= 2048) {
	//		for (std::vector<Npc>::iterator it = ship.npcs.begin(); it != ship.npcs.end(); it++) {
	//			it->setPath((int)((coords.y) / 64) * 32 + (coords.x / 64), ship.tiles);
	//		}
	//	}
	//}

	if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
		*_running = false;
	}

	int x = 0;
	int y = 0;

	if (inputManager.isKeyDown(SDLK_w)) {
		y++;
	}
	if (inputManager.isKeyDown(SDLK_s)) {
		y--;
	}
	if (inputManager.isKeyDown(SDLK_a)) {
		x--;
	}
	if (inputManager.isKeyDown(SDLK_d)) {
		x++;
	}
	if (inputManager.isKeyPressed(SDLK_SPACE)) {
		

	
			csVec2PositionComponents.insert(std::pair<int, CsVec2PositionComponent*>(2, new CsVec2PositionComponent(bodyComponents.at(2)->getPosition(), bodyComponents.at(2)->getSize(), bodyComponents.at(2)->getAngle())));
			csDrawingPositionComponents.insert(std::pair<int, CsDrawingPositionComponent*>(2, new CsDrawingPositionComponent(spriteBatch, csVec2PositionComponents.at(2), drawingBodyComponents.at(2)->getTex())));

		removeComponent<std::unordered_map<int, CsBodyComponent*>>((&bodyComponents), 2);
		removeComponent<std::unordered_map<int, CsDrawingBodyComponent*>>(&drawingBodyComponents, 2);
		
		//delete bodyComponents.at(20);
		//bodyComponents.erase(20);

		//delete drawingBodyComponents.at(20);
		//drawingBodyComponents.erase(20);
	}
	

	if (inputManager.isKeyPressed(SDLK_h)){
		if (!socket.Open(port))
		{
			printf("failed to create socket!\n");

		}
		_listening = true;
		std::cout << "Hosting... Listening...";
		
	}
	if(inputManager.isKeyPressed(SDLK_j)){
		if (!socket.Open(port))
		{
			printf("failed to create socket!\n");

		}

		Address add = Address(192, 168, 178, 59, 30000);

		std::cout << "Client... Connecting to: ";
		std::string f = std::to_string((int)add.GetAddressIP()[0]) + "."
			+ std::to_string((int)add.GetAddressIP()[1]) + "." +
			std::to_string((int)add.GetAddressIP()[2]) + "." +
			std::to_string((int)add.GetAddressIP()[3]);
		std::cout << (f.c_str());
		std::cout << ":";
		printf(std::to_string((int)add.GetPort()).c_str());
		std::cout << "\n";
		std::string s = " ";
		//const char data[] = s.c_str();
		//socket.Send(Address(192, 168, 0, 102, port), s.c_str(), sizeof(s.c_str()));
		_listening = true;
		socket.Send(Address(add.GetAddress(), add.GetPort()), s.c_str(), sizeof(s.c_str()));

	}

	glm::vec3 camSpeedMultiplier(4.0f, 4.0f, 4.0f);
	if (inputManager.isKeyDown(SDLK_LSHIFT)) {
		camSpeedMultiplier = glm::vec3(2.0f, 2.0f, 1.0f);
	}

	glm::vec3 mov(x, y, 0.0f);
	glm::vec3 camSpeed(2.0f, 2.0f, 1.0f);
	if (mov != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		mov = glm::normalize(mov);
		mov *= camSpeed;
		_drawer->moveCamera(glm::normalize(mov) * camSpeed * camSpeedMultiplier);
	}

	dynamic_cast<Charactar*>(_entities[0])->input(inputManager, _entities);
	dynamic_cast<Charactar*>(_entities[1])->input(inputManager, _entities);

	for (unsigned int i = 1; i < _entities.size(); i++) {
		_entities[i]->input(inputManager);
	}
}
int tick = 0;
void PlayingState::update() {
	tick++;
	//SEND
	
	if (_connected) {
		unsigned char buffer[32];
		float x = dynamic_cast<EntityBody*>(_entities[0])->getBody()->GetPosition().x;
		float y = dynamic_cast<EntityBody*>(_entities[0])->getBody()->GetPosition().y;

		memcpy(&buffer, &x, sizeof(x));
		memcpy(&buffer[sizeof(y)]  , &y, sizeof(y));
		socket.Send(Address(_host.GetAddress(), _host.GetPort()), buffer, sizeof(buffer));
	}
//	std::cout << "SENT\n";

	//RECEIVE
	while (_listening)
	{
		Address sender;
		unsigned char buffer[32] = "";
		int bytes_read = socket.Receive(sender, buffer, sizeof(buffer));
		if (bytes_read <= 0) {
			if(tick %120 == 0)
				std::cout << "Silence...";
			break;
		}
		_host = sender;
		_connected = true;
		float x;
		memcpy(&x, &buffer , sizeof(x));
		float y;
		memcpy(&y, &buffer[sizeof(y)] , sizeof(y));
		//sscanf_s(bufferX, "%d", &x);
		//sscanf_s(bufferY, "%d", &y);
		//std::cout << x;
		//std::cout << " ";
		//std::cout << y << std::endl;
		dynamic_cast<EntityBody*>(_entities[1])->getBody()->SetTransform(b2Vec2(x,y),0.0f);
		/*std::string s = std::to_string((int)sender.GetAddressIP()[0]) + "."
			+ std::to_string((int)sender.GetAddressIP()[1])+ "."+
			std::to_string((int)sender.GetAddressIP()[2]) +"."+ 
			std::to_string((int)sender.GetAddressIP()[3]);
		printf(s.c_str());
		printf(":");
		printf(std::to_string((int)sender.GetPort()).c_str());
		printf("\n");*/
		break;
	}

	

	_world->Step(timeStep, velocityIterations, positionIterations);

	
	//manager.updateEntities();

	for (std::unordered_map<int, CsBodyComponent* >::iterator it = bodyComponents.begin(); it != bodyComponents.end(); it++) {
		(*it).second->update();
	}

	for (std::unordered_map<int, CsVec2PositionComponent* >::iterator it = csVec2PositionComponents.begin(); it != csVec2PositionComponents.end(); it++) {
		(*it).second->update();
	}



	for (unsigned int i = 0; i < _entities.size(); i++) {
		_entities[i]->update();
	}


}