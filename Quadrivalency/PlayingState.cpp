#include "PlayingState.h"

PlayingState::PlayingState()
{
}

PlayingState::~PlayingState()
{
	for (int i = 0; i < _entities.size(); i++) {
		_world->DestroyBody(_entities[i].getBody());
	}

	delete _world;
}

void PlayingState::init(Drawer * drawer, bool* running) {
	_drawer = drawer;
	_running = running;
	tex = texCache.getTexture("image2.png");
	_world = new b2World(b2Vec2(0.0f, -9.81f));

	Charactar e;
	e.init(glm::vec2(50.0f, 50.0f), glm::vec2(64.0f,64.0f), _world, texCache);
	_entities.push_back(e);

	Wall w;
	w.init(glm::vec2(0.0f, 0.0f), glm::vec2(2048.0f, 64.0f), _world, texCache);
	_entities.push_back(w);

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

	for (auto i : _entities) {
		i.draw(spriteBatch);
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

	for (auto i : _entities) {
		i.input(inputManager);
	}
}

void PlayingState::update() {
	_world->Step(timeStep, velocityIterations, positionIterations);

	for (auto i : _entities) {
		i.update();
	}
}