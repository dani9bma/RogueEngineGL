/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "platform/opengl/graphics/opengl/opengl.h"
#include "platform/opengl/graphics/window.h"
#include "platform/opengl/graphics/camera/camera.h"
#include "platform/opengl/graphics/lighting/DirectionalLight.h"
#include "utils/common.h"
#include "utils/log.h"
#include "platform/opengl/graphics/model.h"
#include "platform/opengl/graphics/skybox.h"
#include "platform/opengl/ecs/entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui/ui_window.h"

extern bool        ImGui_ImplGlfwGL3_Init(GLFWwindow* window, bool install_callbacks);
extern void        ImGui_ImplGlfwGL3_Shutdown();
extern void        ImGui_ImplGlfwGL3_NewFrame();
extern void        ImGui_ImplGlfwGL3_RenderDrawData(ImDrawData* draw_data);
extern void        ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
extern bool        ImGui_ImplGlfwGL3_CreateDeviceObjects();

bool m_wireframe(false);

void Wireframe()
{
	if (!m_wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_wireframe = true;
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_wireframe = false;
	}
}

namespace Skel
{
	class Scene3DOpenGL
	{
	public:
		Scene3DOpenGL()
		{
			Window* window = new Window(1280, 720, "Skel Engine");

			Shader* shader = new Shader("SkelCore/src/platform/opengl/shaders/basic.vert", "SkelCore/src/platform/opengl/shaders/basic.frag");
			Shader* skyboxShader = new Shader("SkelCore/src/platform/opengl/shaders/cubemap.vert", "SkelCore/src/platform/opengl/shaders/cubemap.frag");

			shader->enable();

			Camera camera = Camera(1280, 720, 0.1f, window, shader);

			DirectionalLight light = DirectionalLight(shader, camera);
			glm::vec3 lightPos(1.0f, -5.0f, 15.0f);
			light.setLightDirection(lightPos);
			light.setIntensity(3.f);

			Skybox skybox = Skybox(skyboxShader);

			Model* crysisModel = new Model("SkelCore/models/nanosuit/nanosuit.obj");
			Model* garroshModel = new Model("SkelCore/models/garrosh.obj");
			Model* sponzaModel = new Model("SkelCore/models/SmallTropicalIsland/Small_Tropical_Island.obj");
			Model* swThroneModel = new Model("SkelCore/models/swThrone.obj");


			Entity* sponza = new Entity(sponzaModel, shader);
			sponza->setPosition(-100.0f, -7.0f, 50.0f);
			Entity* garrosh = new Entity(garroshModel, shader);
			Entity* crysis = new Entity(crysisModel, shader);
			Entity* throne = new Entity(swThroneModel, shader);

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 300.0f);
			shader->setUniformMat4("projection", projection);

			sponza->setSize(1.0f, 1.0f, 1.0f);

			bool gameMode = true;

			UIWindow* debugWindow = new UIWindow(window, Dark, "Debug", "SkelCore/fonts/Roboto-Regular.ttf");

			while (!window->closed())
			{

				//Render
				GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
				GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
				GLCall(glEnable(GL_DEPTH_TEST));
				GLCall(glEnable(GL_BLEND));
				GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

				debugWindow->Begin();
				debugWindow->AddLabel("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				debugWindow->AddButton("Wireframe", Wireframe);
				debugWindow->AddLabel("Press G to enter Game Mode");
				debugWindow->AddLabel("Press Ctrl-G to exit Game Mode");
				debugWindow->End();

				if (glfwGetKey(window->getGLFWwindow(), GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window->getGLFWwindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				{
					camera.setGameMode(false);
					gameMode = false;
					glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				else if (glfwGetKey(window->getGLFWwindow(), GLFW_KEY_G) == GLFW_PRESS)
				{
					camera.setGameMode(true);
					gameMode = true;
					glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
					
					
				//Render
				camera.update();
				

				window->update();
			}

		}
	};
}