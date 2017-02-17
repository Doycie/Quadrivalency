#pragma once
#include <Box2d\Box2D.h>
#include <glm\glm.hpp>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "InputManager.h"
#include "TextureCache.h"
 class Entity
{
public:
	Entity();
	~Entity();

	virtual void init(glm::vec2 position, glm::vec2 size, b2World * world,GLuint tex);

	virtual void draw(SpriteBatch& spriteBatch);

	virtual void update();

	virtual void input(InputManager& inputManager);


protected:

	
	GLuint _tex;

	glm::vec2 _size;

 
 
 
 };
