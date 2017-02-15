#pragma once
#define GLEW_STATIC

#include <gl\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

#include <SDL\SDL_timer.h>
#include <SOIL\SOIL.h>

#include <iostream>
#include <chrono>
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
#include "PlayingState.h"

class MainGame
{
public:

	MainGame();

	void start();

private:

	PlayingState _playingState;

	SpriteBatch spriteBatch;
	SpriteBatch hudSpriteBatch;

	InputManager inputManager;

	SpriteFont * spriteFont;

	Drawer drawer;

	bool running;

	SDL_Window* window;
	SDL_Event windowEvent;

	float camSpeed = 5.0f;

	//Ship ship;
	//Starmap starmap;

	//Ship2 ship;
};