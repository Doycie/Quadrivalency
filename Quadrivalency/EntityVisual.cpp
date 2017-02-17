#include "EntityVisual.h"



EntityVisual::EntityVisual()
{
}


EntityVisual::~EntityVisual()
{
}

void EntityVisual::init(glm::vec2 position, glm::vec2 size, GLuint tex) {
	_position = position;
	_size = size;
	_tex = tex;
}
void EntityVisual::draw(SpriteBatch& spriteBatch) {
	spriteBatch.draw(glm::vec4((_position.x- _size.x/2) * 64, (_position.y - _size.y/2) * 64, _size.x * 64 , _size.y* 64), glm::vec4(0, 0, 1, -1), _tex, 0.1f, ColorRGBA8(255, 255, 255, 255));
}