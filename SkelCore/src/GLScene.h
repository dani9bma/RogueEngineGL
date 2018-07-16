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

#include "imgui/imgui.h"

extern bool        ImGui_ImplGlfwGL3_Init(GLFWwindow* window, bool install_callbacks);
extern void        ImGui_ImplGlfwGL3_Shutdown();
extern void        ImGui_ImplGlfwGL3_NewFrame();
extern void        ImGui_ImplGlfwGL3_RenderDrawData(ImDrawData* draw_data);
extern void        ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
extern bool        ImGui_ImplGlfwGL3_CreateDeviceObjects();


namespace Skel
{
	class Scene3DOpenGL
	{
	public:
		Scene3DOpenGL()
		{
			float transparentVertices[] = {
				// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
				0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
				0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
				1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

				0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
				1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
				1.0f,  0.5f,  0.0f,  1.0f,  0.0f
			};



			Window* window = new Window(1280, 720, "Skel Engine");

			Shader* shader = new Shader("src/platform/opengl/shaders/basic.vert", "src/platform/opengl/shaders/basic.frag");
			Shader* glassShader = new Shader("src/platform/opengl/shaders/glass.vert", "src/platform/opengl/shaders/glass.frag");
			Shader* skyboxShader = new Shader("src/platform/opengl/shaders/cubemap.vert", "src/platform/opengl/shaders/cubemap.frag");

			unsigned int transparentVAO, transparentVBO;
			glGenVertexArrays(1, &transparentVAO);
			glGenBuffers(1, &transparentVBO);
			glBindVertexArray(transparentVAO);
			glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glBindVertexArray(0);

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


			Entity* sponza = new Entity(sponzaModel, shader);
			Entity* garrosh = new Entity(garroshModel, shader);
			Entity* crysis = new Entity(crysisModel, shader);
			Entity* throne = new Entity(swThroneModel, shader);

			Texture windowTexture("src/textures/window.png", shader);

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 300.0f);
			shader->setUniformMat4("projection", projection);

			// Setup ImGui binding
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.MouseDrawCursor = false;
			io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 18.0f);
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
			ImGui_ImplGlfwGL3_Init(window->getGLFWwindow(), true);

			// Setup style
			ImGui::StyleColorsDark();

			bool show_another_window = true;

			bool wireframe = false;

			bool gameMode = true;

			
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

				glassShader->enable();
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(0.0f, 0.0, 2.0f));
				model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glassShader->setUniformMat4("model", model);
				glassShader->setUniformMat4("projection", projection);
				glassShader->setUniformMat4("view", camera.getView());

				glBindVertexArray(transparentVAO);
				windowTexture.draw(0);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				
				shader->enable();

				ImGui_ImplGlfwGL3_NewFrame();

				if (show_another_window)
				{
					ImGui::Begin("Debug", &show_another_window);
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);					if(ImGui::Button("Wireframe"))
						if (!wireframe)
						{
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
							wireframe = true;
						}
						else
						{
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
							wireframe = false;
						}

					ImGui::Text("Press G to enter Game Mode");
					ImGui::Text("Press Ctrl-G to exit Game Mode");

					ImGui::End();
				}

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
				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				window->update();
			}

			ImGui_ImplGlfwGL3_Shutdown();
			ImGui::DestroyContext();

		}
	};
}