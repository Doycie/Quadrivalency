#pragma once
#include <Box2d\Box2D.h>

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "SpriteBatch.h"
#include <iostream>
#include "CsEntity.h"
#include <string>


class CsEntity;

class CsComponent {
public:
	CsComponent();
	~CsComponent();
	virtual void update();
	virtual void init();
	std::string getID() { return ID; }
protected:
	std::string ID = "INVALID BASE COMPONENT";
};


class CsVec2PositionComponent : public CsComponent  {
public:
	CsVec2PositionComponent(glm::vec2 positon,  glm::vec2 size, float angle);
	~CsVec2PositionComponent();
	glm::vec2& getPosition();
	glm::vec2& getSize();
	float getAngle();
private:
	glm::vec2 _pos;
	glm::vec2 _size;
	float _angle;
};

class CsBodyComponent : public CsComponent  {
public:
	CsBodyComponent(glm::vec2 position, b2World * world, glm::vec2 size);

	~CsBodyComponent();
	glm::vec2& getPosition();
	glm::vec2& getSize();
	float getAngle();
	void update();
	
private:
	glm::vec2 _size;
	b2Body* _body = nullptr;
	b2BodyDef _bodyDef;
};

class CsDrawingBodyComponent :public CsComponent {
public:
	CsDrawingBodyComponent(SpriteBatch* s, CsBodyComponent* c, GLuint tex);
	~CsDrawingBodyComponent();

	void update();
	GLuint getTex() {
		return _tex;
	}
private:
	GLuint _tex;
	SpriteBatch* spriteBatch;
	CsBodyComponent* _bodyComp;
};

class CsDrawingPositionComponent :public CsComponent {
public:
	CsDrawingPositionComponent(SpriteBatch* s, CsVec2PositionComponent* c, GLuint tex);
	~CsDrawingPositionComponent();

	void update();
private:
	GLuint _tex;
	SpriteBatch* spriteBatch;
	CsVec2PositionComponent* _posComp;
};
