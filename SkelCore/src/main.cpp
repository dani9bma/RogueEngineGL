/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "graphics/opengl/opengl.h"
#include "graphics/window.h"
#include "graphics/camera/camera.h"
#include "graphics/lighting/directional_light.h"
#include "utils/common.h"
#include "utils/log.h"
#include "graphics/model.h"

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
		 0.5f,  0.5f, 0.0f,   1.0f,  0.0f,  0.0f,	1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,	  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,   // bottom right
		 -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,   // bottom left
		 -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,	0.0f, 1.0f

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

	graphics::DirectionalLight light = graphics::DirectionalLight(shader, camera);
	glm::vec3 lightPos(1.0f, 0.0f, 15.0f);
	light.setLightDirection(lightPos);
	light.setIntensity(3.f);

	graphics::Texture texture = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/ice.jpg", shader);
	graphics::Texture specular = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/ice.jpg", shader);
	graphics::Texture texture2 = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/wall.jpg", shader);
	graphics::Texture specular2 = graphics::Texture("E:/Dev/SkelEngine/SkelCore/src/textures/wall.jpg", shader);


	graphics::Model crysis("E:/Dev/SkelEngine/SkelCore/models/nanosuit/nanosuit.obj");
	graphics::Model cube("E:/Dev/SkelEngine/SkelCore/models/Rubiks Cube.obj");
	

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	shader->setUniformMat4("projection", projection);
	while (!window->closed())
	{
		//Render
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));

		
		light.update();
		shader->enable();
		/*Draw Cube*/

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -5.0, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setUniformMat4("model", model);
		crysis.Draw(shader);
		shader->enable();
		//Draw Floor
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.0f, -5.0f, 3.0f));
		model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.3f, 0.0005f, 0.3f));
		shader->setUniformMat4("model", model2);
		texture.draw(0);
		specular.draw(1);
		cube.Draw(shader);
		//Render
		camera.update();
		window->update();
	}

}