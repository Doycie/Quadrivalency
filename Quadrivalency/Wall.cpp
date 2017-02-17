#include "Wall.h"



Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::init(glm::vec2 position, glm::vec2 size, b2World * world, GLuint tex)
{
	StaticEntity::init( position,size,  world,  tex);
	
}