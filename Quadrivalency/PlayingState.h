#pragma once

#include <gl\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

#include <SDL\SDL_timer.h>
#include <SOIL\SOIL.h>
#include <Box2d\Box2D.h>

#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "TextureCache.h"
#include "Drawer.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "InputManager.h"

#include "drawer.h"
#include "Charactar.h"
#include "Wall.h"
#include "Socket.h"
#include "Ball.h"
#include "EntityVisual.h"


class PlayingState
{
public:
	PlayingState();
	~PlayingState();

	void init(Drawer * drawer, bool* running);

	void draw(SpriteBatch& spriteBatch);
	void drawHud(SpriteBatch& hudSpriteBatch, SpriteFont * spriteFont);
	void update();
	void input(InputManager& inputManager);

private:
	const int port = 30000;
	Socket socket;
	Address _host;
	bool _listening;

	float timeStep = 1 / 20.0;
	int velocityIterations = 8;
	int positionIterations = 3;

	std::vector<Entity*> _entities;

	Drawer * _drawer;
	bool * _running;

	bool _connected =false;

	b2World* _world;

	GLuint tex;
	TextureCache texCache;
};
