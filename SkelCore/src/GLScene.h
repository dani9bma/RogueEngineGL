/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "graphics/opengl/opengl.h"
#include "graphics/window.h"
#include "graphics/camera/camera.h"
#include "graphics/lighting/DirectionalLight.h"
#include "utils/common.h"
#include "utils/log.h"
#include "graphics/model.h"
#include "graphics/skybox.h"
#include "entity/entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Skel
{
	class Scene3DOpenGL
	{
	public:
		Scene3DOpenGL()
		{
			Window* window = new Window(1280, 720, "Skel Engine");

			Shader* shader = new Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/basic.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/basic.frag");
			Shader* skyboxShader = new Shader("E:/Dev/SkelEngine/SkelCore/src/shaders/cubemap.vert", "E:/Dev/SkelEngine/SkelCore/src/shaders/cubemap.frag");

			shader->enable();

			Camera camera = Camera(1280, 720, 0.1f, window, shader);

			DirectionalLight light = DirectionalLight(shader, camera);
			glm::vec3 lightPos(1.0f, -5.0f, 15.0f);
			light.setLightDirection(lightPos);
			light.setIntensity(3.f);

			Skybox skybox = Skybox(skyboxShader);

			Model* crysisModel = new Model("models/nanosuit/nanosuit.obj");
			Model* garroshModel = new Model("models/garrosh.obj");
			Model* sponzaModel = new Model("models/sponza/sponza_optimized.obj");
			Model* swThroneModel = new Model("models/swThrone.obj");


			Entity*sponza = new Entity(sponzaModel, shader);
			Entity*garrosh = new Entity(garroshModel, shader);
			Entity*crysis = new Entity(crysisModel, shader);
			Entity*throne = new Entity(swThroneModel, shader);

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 300.0f);
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

				sponza->draw();

				garrosh->setPosition(10.0f, -5.0f, -2.0f);
				garrosh->setSize(4.0f, 4.0f, 4.0f);
				garrosh->setRotation(glfwGetTime(), false, true, false);
				//garrosh->setTransform(glm::vec3(10.0f, -5.0, -2.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glfwGetTime() * 2.0f);
				garrosh->draw();

				crysis->setPosition(0.0f, -5.0f, -2.0f);
				crysis->setSize(1.0f, 1.0f, 1.0f);
				crysis->setRotation(180.0f, false, true, false);
				//crysis->setTransform(glm::vec3(0.0f, -5.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
				crysis->draw();

				throne->setPosition(0.0f, -5.0f, 15.0f);
				throne->setSize(1.0f, 1.0f, 1.0f);
				throne->draw();

				//Render
				camera.update();
				window->update();
			}

		}
	};
}