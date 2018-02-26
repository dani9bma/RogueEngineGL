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
#include "graphics/skybox.h"
#include "entity/entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Skel;

int main(void)
{
	float floorVertices[] = {
		 0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,	0.0f, -1.0f,  0.0f,	1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,	0.0f, 1.0f

	};
	
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	graphics::Window* window = new graphics::Window(1280, 720, "Skel Engine");
	graphics::Shader* shader = new graphics::Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/basic.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/basic.frag");
	graphics::Shader* skyboxShader = new graphics::Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/cubemap.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/cubemap.frag");
	graphics::Camera camera = graphics::Camera(1280, 720, 0.1f, window, shader);

	graphics::DirectionalLight light = graphics::DirectionalLight(shader, camera);
	glm::vec3 lightPos(1.0f, -5.0f, 15.0f);
	light.setLightDirection(lightPos);
	light.setIntensity(3.f);

	graphics::Skybox skybox = graphics::Skybox(skyboxShader);

	graphics::Model* crysisModel = new graphics::Model("models/nanosuit/nanosuit.obj");
	graphics::Model* garroshModel = new graphics::Model("models/garrosh.obj");
	graphics::Model cube("models/floor.obj");
	graphics::Model* sponzaModel = new graphics::Model("models/sponza/sponza.obj");

	shader->enable();

	entity::Entity* sponza = new entity::Entity(sponzaModel, shader);
	entity::Entity* garrosh = new entity::Entity(garroshModel, shader);
	entity::Entity* crysis = new entity::Entity(crysisModel, shader);
	//sponza->getTransform().setPosition(0.0f, -0.5f, -2.0f);
	//sponza->getTransform().setRotation(180.0f, false, true, false);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 200.0f);
	shader->setUniformMat4("projection", projection);

	while (!window->closed())
	{
		//Render
		GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));

		
		light.update();
		skybox.update(camera, projection);
		shader->enable();

		/*glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -5.0, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setUniformMat4("model", model);*/

		sponza->draw();

		garrosh->setRotation(glfwGetTime(), false, true, false);
		//garrosh->setPosition(50.0f, -5.0f, -2.0f);
		garrosh->setSize(4.0f, 4.0f, 4.0f);
		garrosh->draw();

		crysis->setPosition(0.0f, -5.0f, -2.0f);
		crysis->setSize(1.0f, 1.0f, 1.0f);
		crysis->setRotation(180.0f, false, true, false);
		crysis->draw();



		/*sponza.Draw(shader);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -5.0, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setUniformMat4("model", model);
		crysis.Draw(shader);

		glm::mat4 model3;
		model3 = glm::translate(model3, glm::vec3(10.0f, -5.0, -2.0f));
		model3 = glm::scale(model3, glm::vec3(4.0f, 4.0f, 4.0f));
		model3 = glm::rotate(model3, glm::radians(180.0f) + (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setUniformMat4("model", model3);
		garrosh.Draw(shader);*/

		//Render
		camera.update();
		window->update();
	}

}