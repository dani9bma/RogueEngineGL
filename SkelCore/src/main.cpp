/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "graphics/opengl/opengl.h"
#include "graphics/window.h"
#include "graphics/camera/camera.h"
#include "utils/common.h"
#include "utils/log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Skel;

int main(void)
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	float floorVertices[] = {
		 0.5f,  0.5f, 0.0f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,   // bottom right
		 -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,   // bottom left
		 -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,	0.0f, 1.0f

	};
	
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	graphics::Window* window = new graphics::Window(1280, 720, "Skel Engine");
	graphics::Shader* shader = new graphics::Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/basic.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/basic.frag");
	graphics::Shader* lampShader = new graphics::Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/lamp.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/lamp.frag");
	graphics::VertexArray VAO = graphics::VertexArray();
	graphics::VertexArray VAO2 = graphics::VertexArray();
	graphics::VertexBuffer VBO = graphics::VertexBuffer(vertices, sizeof(vertices), graphics::BufferUsage::STATIC);
	graphics::VertexBuffer VBO2 = graphics::VertexBuffer(floorVertices, sizeof(floorVertices), graphics::BufferUsage::STATIC);
	graphics::IndexBuffer EBO = graphics::IndexBuffer(indices, 6);
	graphics::Camera camera = graphics::Camera(1280, 720, 0.1f, window, shader);
	VAO.addBuffer(0, 3, VBO, 8 * sizeof(float), (void*)0);
	VAO.addBuffer(1, 2, VBO, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO.addBuffer(2, 3, VBO, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.addBuffer(0, 3, VBO2, 8 * sizeof(float), (void*)0);
	VAO2.addBuffer(1, 2, VBO2, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.addBuffer(2, 3, VBO2, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	graphics::Texture texture = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/ice.jpg", shader);
	graphics::Texture specular = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/ice.jpg", shader);
	graphics::Texture texture2 = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/wall.jpg", shader);
	graphics::Texture specular2 = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/wall.jpg", shader);

	glm::vec3 lightPos(10.0f, 0.0f, 2.0f);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	shader->setUniformMat4("projection", projection);
	while (!window->closed())
	{
		//Render
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));

		texture.draw(0);
		specular.draw(1);
		//#TODO: Add This to a seperate class
		shader->enable();
		shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->setUniform3f("lightPos", lightPos);
		shader->setUniform3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->setUniform1i("material.diffuse", 0);
		shader->setUniform1i("material.specular", 1);
		shader->setUniform1f("material.shininess", 32.0f);
		shader->setUniform3f("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		shader->setUniform3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->setUniform3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken the light a bit to fit the scene
		shader->setUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setUniform3f("viewPos", camera.getPosition());
		//#ENDTODO: 
		/*Draw Cube*/
		VAO.bind();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(10.0f, 0.0, 10.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setUniformMat4("model", model);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		VAO.unbind();
		/*Draw Light Cube*/
		//#TODO: Add this to a separate class
		VAO.bind();
		shader->disable();
		lampShader->enable();
		lampShader->setUniformMat4("projection", projection);
		lampShader->setUniformMat4("view", camera.getView());
		glm::mat4 model3;
		model3 = glm::translate(model3, lightPos);
		model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
		model3 = glm::rotate(model3, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
		lampShader->setUniformMat4("model", model3);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		lampShader->disable();
		VAO.unbind();
		shader->enable();
		/*Draw Quad*/
		VAO2.bind();
		texture2.draw(0);
		specular2.draw(1);
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.0f, -5.0f, 3.0f));
		model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(80.0f, 80.0f, 80.0f));
		shader->setUniformMat4("model", model2);
		EBO.draw();
		VAO2.unbind();
		//Render
		camera.update();
		window->update();
	}

}