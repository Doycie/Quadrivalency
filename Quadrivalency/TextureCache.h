#pragma once
#include <iostream>	
#include <map>
#include <GL\glew.h>
#include <SOIL\SOIL.h>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLuint getTexture(std::string texturePath);

private:
	std::map<std::string, GLuint> _textureMap;
};
