#include "TextureCache.h"


TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
	
}

GLuint TextureCache::getTexture(std::string texturePath) {

	//lookup the texture and see if its in the map
	auto mit = _textureMap.find(texturePath);

	//check if its not in the map
	if (mit == _textureMap.end()) {
		//Load the texture
		GLuint newTexture;
		glGenTextures(1, &newTexture);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, newTexture);
		int width, height;
		unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Insert it into the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		return newTexture;
	}
	return mit->second;
}
