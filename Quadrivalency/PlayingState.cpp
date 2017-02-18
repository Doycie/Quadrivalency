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

void PlayingState::init(Drawer * drawer, bool* running) {
	_drawer = drawer;
	_running = running;

	_world = new b2World(b2Vec2(0.0f, -9.81f));
	//CHARACTAR
	Charactar *e = new Charactar();
	e->init(glm::vec2(5, 10), glm::vec2(1,2), _world, texCache.getTexture("Assets/birbSheet.png"));
	_entities.push_back(e);
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

	
	if (!socket.Open(port))
	{
		printf("failed to create socket!\n");

	}

	// send a packet

	

	// receive packets

	

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

	//spriteBatch.draw(glm::vec4(0,0, 2000, 500), glm::vec4(0, 0, 1, -1.0f), spriteFont->_texID, 1.0f, ColorRGBA8(255, 255, 255, 255));
	spriteBatch.end();
	spriteBatch.renderBatch();
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
		std::cout << "SENDING UDP PACKETS THROUGH HYPER SPACE\n";

		std::string s = std::to_string((int)dynamic_cast<EntityBody*>(_entities[0])->getBody()->GetPosition().x);
		//const char data[] = s.c_str();
		socket.Send(Address(192, 168, 178, 115, port), s.c_str(), sizeof(s.c_str()));
		std::cout << "SENT\n";
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

	for (unsigned int i = 1; i < _entities.size(); i++) {
		_entities[i]->input(inputManager);
	}
}

void PlayingState::update() {
	

	// create socket

	while (true)
	{
		Address sender;
		unsigned char buffer[256] = "";

		int bytes_read = socket.Receive(sender, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break;

		//process packet
	
		printf((const  char *)buffer );
		printf("\n");

		std::string s = std::to_string((int)sender.GetAddressIP()[0]) + "."
			+ std::to_string((int)sender.GetAddressIP()[1])+ "."+
			std::to_string((int)sender.GetAddressIP()[2]) +"."+ 
			std::to_string((int)sender.GetAddressIP()[3]);
		printf(s.c_str());
		printf(":");
		printf(std::to_string((int)sender.GetPort()).c_str());
		printf("\n");

		break;
	}


	_world->Step(timeStep, velocityIterations, positionIterations);

	for (unsigned int i = 0; i < _entities.size(); i++) {
		_entities[i]->update();
	}
}