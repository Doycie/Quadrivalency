#include "Drawer.h"
#include <iostream>
#include "SpriteBatch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Drawer::Drawer(GLuint shaderProgram)
{
	_orthoMatrix = glm::ortho(0.0f,(float) WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
	cameraPos = glm::vec3(0.5f, 0.0f, 1.0f);
	cameraAngle = 0.0f;
	//SETUP VAO TO REMEMBER ATTRIBUTES ON VBOS
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//SETUP VBO 
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);



	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_DYNAMIC_DRAW);


	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
//	glVertexAttribPointer(colAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, 7 * sizeof(GL_UNSIGNED_BYTE), (void*)(2 * sizeof(GLfloat)));
	glVertexAttribPointer(colAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	//glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	uniTrans = glGetUniformLocation(shaderProgram, "trans");

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Drawer::~Drawer()
{
	
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}


void Drawer::moveCamera(glm::vec3 pos)
{
	cameraPos += pos;

}

void Drawer::updateCamera() {


	//trans = glm::rotate(trans, cameraAngle, glm::vec3(0.0f, 0.0f, 1.0f));
//	trans = glm::translate(trans, cameraPos);

	glm::vec3 translate(-cameraPos.x + WINDOW_WIDTH / 2, -cameraPos.y + WINDOW_HEIGHT / 2, 0.0f);
	trans = glm::translate(_orthoMatrix, translate);

	glm::vec3 scale(cameraPos.z, cameraPos.z, 0.0f);
	trans = glm::scale(glm::mat4(1.0f), scale) * trans;

	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));



}

glm::vec2 Drawer::getWorldCoordinates(glm::vec2 coords)
{
	
		coords.y = WINDOW_HEIGHT - coords.y;

		coords -= glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		coords /= cameraPos.z;

		coords += glm::vec2(cameraPos.x,cameraPos.y);
		return coords;
	
	
}

