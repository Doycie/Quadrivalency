#pragma once
#include <Box2d\Box2D.h>

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "SpriteBatch.h"
#include <iostream>
#include "CsComponents.h"
#include <list>

class CsComponent;

class CsEntity
{
public:
	CsEntity();
	~CsEntity();

	void init();
	void addComponent(CsComponent* c);
	void removeComponent(std::string ID);
	void printComponents();
	CsComponent* getComponent(std::string ID);

private:
	std::list<CsComponent*> _components;
};

