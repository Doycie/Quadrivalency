
#include "MainGame.h"

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


MainGame::MainGame() {

}

void MainGame::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawer.updateCamera();

	spriteBatch.begin(GlyphSortType::FRONT_TO_BACK);

	//starmap.draw(spriteBatch);

	ship.draw(spriteBatch);


	spriteBatch.end();
	spriteBatch.renderBatch();


	hudSpriteBatch.begin();

	char buffer[256];
	sprintf_s(buffer, "GoodDay");
	spriteFont->draw(hudSpriteBatch, buffer, glm::vec2(1024, 1024), glm::vec2(1.0f), 0.0f, ColorRGBA8(0, 255, 255, 255));

	hudSpriteBatch.end();
	hudSpriteBatch.renderBatch();


	SDL_GL_SwapWindow(window);
}

void MainGame::input() {

	inputManager.update();

	while (SDL_PollEvent(&windowEvent))
	{
		switch (windowEvent.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords((float)windowEvent.motion.x, (float)windowEvent.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(windowEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(windowEvent.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(windowEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(windowEvent.button.button);
			break;
		case SDL_MOUSEWHEEL:
			inputManager.setMouseWheel((float)windowEvent.wheel.y);
			break;
		}
	}


	if (inputManager.getMouseWheel() != 0.0f) {
		drawer.moveCamera(glm::vec3(0.0f, 0.0f, inputManager.getMouseWheel() / 20.0f));
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		glm::vec2 coords = drawer.getWorldCoordinates(glm::vec2(x, y));

		if (coords.x >= 0 && coords.x <= 2048 && y >= 0 && y <= 2048) {


			ship.addTile(1, texcache, (int)((coords.y) / 64) * 32 + (coords.x / 64));

		}

	}

	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		glm::vec2 coords = drawer.getWorldCoordinates(glm::vec2(x, y));

		if (coords.x >= 0 && coords.x <= 2048 && y >= 0 && y <= 2048) {

			for (std::vector<Npc>::iterator it = ship.npcs.begin(); it != ship.npcs.end(); it++) {
				it->setPath((int)((coords.y) / 64) * 32 + (coords.x / 64), ship.tiles);
			}
		}
	}


	if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
		running = false;
	}

	if (inputManager.isKeyDown(SDLK_w)) {
		drawer.moveCamera(glm::vec3(0.0f, camSpeed, 0.0f));
	}
	if (inputManager.isKeyDown(SDLK_s)) {
		drawer.moveCamera(glm::vec3(0.0f, -camSpeed, 0.0f));
	}
	if (inputManager.isKeyDown(SDLK_a)) {
		drawer.moveCamera(glm::vec3(-camSpeed, 0.0f, 0.0f));
	}
	if (inputManager.isKeyDown(SDLK_d)) {
		drawer.moveCamera(glm::vec3(camSpeed, 0.0f, 0.f));
	}

}

void MainGame::update() {

	for (std::vector<Npc>::iterator it = ship.npcs.begin(); it != ship.npcs.end(); it++) {
		it->update();
	}


	ship.update();


}


void MainGame::start(){

	//SDL INITIALISATION
	SDL_Init(SDL_INIT_VIDEO);



	//SDL OPENGL WINDOW CREATION
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow("Hi.., Im Mr. Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

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

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	drawer.init(shaderProgram);
	spriteFont = new SpriteFont("Fonts/chintzy.ttf",40);


	spriteBatch.init(drawer.vao, drawer.vbo);
	hudSpriteBatch.init(drawer.vao, drawer.vbo);


	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	ship.init(texcache);
	starmap.init(texcache);

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	running = true;


	drawer.setCamera(glm::vec3(1024.0f, 1024.0f, 1.0f));




	int ticks = 0;
	unsigned int lastTime = 0, currentTimeInt, seconds = 0;

	double oldTime = SDL_GetTicks();

	while (running)
	{

		ticks++;

		currentTimeInt = static_cast<double>(SDL_GetTicks());
		if (currentTimeInt > lastTime + 1000) {
			seconds++;
			std::string s = std::to_string(ticks / seconds);
			char const *pchar = s.c_str();  //use char const* as target type
			SDL_SetWindowTitle(window, pchar);
			lastTime = currentTimeInt;
			ticks = 0;
			seconds = 0;
		}

		


		while (double(SDL_GetTicks() - oldTime) /1000.0< 1.0 / 60.0) {
			SDL_Delay(1);
			
		}

		oldTime = SDL_GetTicks();
		
		input();
		update();
		draw();
	
		
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	SDL_GL_DeleteContext(context);

	SDL_Quit();
	

}

