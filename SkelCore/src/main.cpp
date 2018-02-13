/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "graphics/opengl/opengl.h"
#include "graphics/window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Skel;

int main(void)
{
	float vertices[] = {
		// positions      
		0.5f, -0.5f, 0.0f,// bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		0.0f,  0.5f, 0.0f,// top 
	};

	unsigned int indices[] =
	{
		0, 1, 2,
	};

	graphics::Window window = graphics::Window(1280, 720, "Skel Engine");
	graphics::Shader shader = graphics::Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/basic.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/basic.frag");
	graphics::VertexArray VAO = graphics::VertexArray();
	graphics::VertexBuffer VBO = graphics::VertexBuffer(vertices, sizeof(vertices), graphics::BufferUsage::STATIC);
	graphics::IndexBuffer EBO = graphics::IndexBuffer(indices, 3);
	VAO.addBuffer(0, 3, VBO);
	VAO.unbind();
	EBO.unbind();

	while (!window.closed())
	{
		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.8f;
		float redValue = (sin(timeValue) / 2.0f) + 0.3f;
		float blueValue = (sin(timeValue) / 2.0f) + 0.1f;
		shader.enable();
		glm::mat4 trans;
		trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5, 0.0, 0.0));
		trans = glm::scale(trans, glm::vec3(0.5, 1.0, 1.0));
		shader.setUniformMat4("transform", trans);
		shader.setUniform4f("vertexColor", redValue, greenValue, blueValue, 1.0f);

		shader.enable();
		VAO.bind();
		EBO.draw();
		VAO.unbind();
		//Render
		window.update();
	}

}