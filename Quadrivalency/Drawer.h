#pragma once
#include <GL\glew.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

class Drawer
{
public:

	Drawer();
	~Drawer();

	void init(GLuint shaderProgram);

	GLint uniTrans;

	glm::vec3 cameraPos;
	glm::vec3 desiredPos;
	glm::vec3 cameraSpeed;

	float cameraAngle;

	void moveCamera(glm::vec3 pos);
	void setCamera(glm::vec3 pos);

	glm::mat4 trans;

	glm::mat4 _orthoMatrix;

	void updateCamera();
	glm::vec2 getWorldCoordinates(glm::vec2 coords);
	glm::vec4 Drawer::getScreenBounds();

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	GLfloat vertices[28] = {
		//  Position      Color             Texcoords
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};
};
