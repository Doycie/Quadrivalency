
#define GLEW_STATIC

#include <gl\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

#include <SDL\SDL_timer.h>
#include <SOIL\SOIL.h>

#include <iostream>
#include <chrono>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <vector>

#include "TextureCache.h"
#include "Drawer.h"
#include "SpriteBatch.h"

#include "Ship.h"

bool readFileToBuffer(std::string filePath, std::string& buffer) {

	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return 1;

}
GLuint compileShader(const char* source, GLint type) {

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	char shaderlog[512];
	glGetShaderInfoLog(shader, 512, NULL, shaderlog);

	if (!status) {
		std::cout << "ERROR SHADER FAILED TO COMPILE BECAUSE THE CODE SUCKS TO BAD: " << std::endl;
		std::cout << shaderlog << std::endl;
		std::cin.get();
		exit(0);
	}
	else {

		std::cout << "Shader compiled succesfully :D. Here is some info: " << std::endl;
	}

	if (shaderlog[1] = ' ')
		std::cout << "Nevermind no info was found. Shader seems fine. I hope..." << std::endl;
	else
		std::cout << shaderlog << std::endl;

	return shader;
}

int main(int argc, char *argv[])
{


	//SDL INITIALISATION
	SDL_Init(SDL_INIT_VIDEO);



	//SDL OPENGL WINDOW CREATION
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("Hi.., Im Mr. Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_Event windowEvent;

	//GLEW FOR MODERN OPENGL
	glewExperimental = GL_TRUE;
	glewInit();


	//LOAD SHADERS
	std::string buffer;
	readFileToBuffer("Shaders/shader.vert", buffer);
	GLuint	vertexShader = compileShader(buffer.c_str(), GL_VERTEX_SHADER);
	readFileToBuffer("Shaders/shader.frag", buffer);
	GLuint fragmentShader = compileShader(buffer.c_str(), GL_FRAGMENT_SHADER);

	//USE SHADERS
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	TextureCache texcache;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Drawer drawer(shaderProgram);

	SpriteBatch spriteBatch;

	spriteBatch.init(drawer.vao,drawer.vbo);


	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Ship ship;

	//glEnable(GL_DEPTH_TEST);

	while (true)
	{

		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE)) break;
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN) {
				if (windowEvent.button.button == SDL_BUTTON_LEFT) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					glm::vec2 coords = drawer.getWorldCoordinates(glm::vec2(x, y));
					ship.addTile(1,texcache,coords);
				}
				if (windowEvent.button.button == SDL_BUTTON_RIGHT) {

				}
			}
			if (windowEvent.type == SDL_MOUSEWHEEL) {
				drawer.moveCamera(glm::vec3(0.0f, 0.0f, windowEvent.wheel.y/10.0f));

			}
			if (windowEvent.type == SDL_KEYDOWN) {
				switch (windowEvent.key.keysym.sym) {
				case SDLK_w:
					drawer.moveCamera(glm::vec3(0.0f, 5.0f, 0.0f));
					break;
				case SDLK_s:
					drawer.moveCamera(glm::vec3(0.0f, -5.0f, 0.0f));
					break;
				case SDLK_a:
					drawer.moveCamera(glm::vec3(-5.0f, 0.0f, 0.0f));
					break;
				case SDLK_d:
					drawer.moveCamera(glm::vec3(5.0f, 0.0f, 0.0f));
					break;
				}
			}
		}


		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

		drawer.updateCamera();

		spriteBatch.begin(GlyphSortType::FRONT_TO_BACK);
	
		
		spriteBatch.draw(glm::vec4(0.0f,0.0f,64.0f,64.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texcache.getTexture("image.png"), 0.0f, ColorRGBA8(255.0f,255.0f,255.0f,255.0f) , 0.0f);
	
		
		spriteBatch.draw(glm::vec4(64.0f,64.0f, 600.0f, 800.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texcache.getTexture("image2.png"), 0.0f, ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), 0.0f);


		ship.draw(spriteBatch);
		

		spriteBatch.end();
		spriteBatch.renderBatch();

		SDL_GL_SwapWindow(window);

	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;

}