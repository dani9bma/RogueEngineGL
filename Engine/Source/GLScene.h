/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "Graphics/opengl.h"
#include "Core/window.h"
#include "Scene/camera.h"
#include "Scene/DirectionalLight.h"
#include "Common/Common.h"
#include "Utils/Log.h"
#include "ECS/components/model.h"
#include "Graphics/Skybox.h"
#include "ECS/Entity.h"
#include "Graphics/FrameBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/Input.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

Skel::Entity* sponza = nullptr;
Skel::Entity* garrosh = nullptr;
Skel::Entity* crysis = nullptr;
Skel::Entity* throne = nullptr;

void GarroshVisible()
{
	garrosh->setVisibility(true);
}

void GarroshInvisible()
{
	garrosh->setVisibility(false);
}

void SponzaVisible()
{
	sponza->setVisibility(true);
}

void SponzaInvisible()
{
	sponza->setVisibility(false);
}

void CrysisVisible()
{
	crysis->setVisibility(true);
}

void CrysisInvisible()
{
	crysis->setVisibility(false);
}

void ThroneVisible()
{
	throne->setVisibility(true);
}

void ThroneInvisible()
{
	throne->setVisibility(false);
}

namespace Skel
{
	class Scene3DOpenGL
	{
	public:

		Scene3DOpenGL()
		{
			Window* window = new Window(1280, 720, "Skel Engine");

			Shader* shader = new Shader("../Engine/Res/Shaders/basic.vert", "../Engine/Res/Shaders/basic.frag");
			Shader* skyboxShader = new Shader("../Engine/Res/Shaders/cubemap.vert", "../Engine/Res/Shaders/cubemap.frag");

			shader->enable();

			Camera camera = Camera(1280, 720, 0.2f, window, shader);

			DirectionalLight light = DirectionalLight(shader, camera);
			glm::vec3 lightPos(0.0f, -5.0f, -2.0f);
			light.setLightDirection(lightPos);
			light.setIntensity(1.0f);

			Skybox skybox = Skybox(skyboxShader);

			Model* crysisModel = new Model("../Engine/Res/models/nanosuit/nanosuit.obj");
			Model* garroshModel = new Model("../Engine/Res/models/garrosh.obj");
			//Model* sponzaModel = new Model("../Engine/Res/models/OBJ.obj");
			Model* swThroneModel = new Model("../Engine/Res/models/swThrone.obj");


			//sponza = new Entity(sponzaModel, shader);
			//sponza->setPosition(-100.0f, -7.0f, 50.0f);
			//sponza->setSize(0.2f, 0.2f, 0.2f);

			garrosh = new Entity(garroshModel, shader);
			garrosh->setPosition(7.0f, -5.0f, -2.0f);
			garrosh->setSize(4.0f, 4.0f, 4.0f);

			crysis = new Entity(crysisModel, shader);
			crysis->setPosition(0.0f, -5.0f, -2.0f);
			crysis->setSize(1.0f, 1.0f, 1.0f);
			crysis->setRotation(180.0f, false, true, false);

			throne = new Entity(swThroneModel, shader);
			throne->setPosition(0.0f, -5.0f, 15.0f);
			throne->setSize(1.0f, 1.0f, 1.0f);

#if 0
			float garroshRotationY = garrosh->getTransform().getRotation().y;
			float garroshLocationX = garrosh->getTransform().getPosition().x;
			float garroshSizeX = garrosh->getTransform().getSize().x;
			float garroshRotationX = garrosh->getTransform().getRotation().x;
			float garroshLocationY = garrosh->getTransform().getPosition().y;
			float garroshSizeY = garrosh->getTransform().getSize().y;
			float garroshRotationZ = garrosh->getTransform().getRotation().z;
			float garroshLocationZ = garrosh->getTransform().getPosition().z;
			float garroshSizeZ = garrosh->getTransform().getSize().z;
#endif

			FrameBuffer* frameBuffer = new FrameBuffer();
			// Setup Dear ImGui binding
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

			ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
			ImGui_ImplOpenGL3_Init("#version 130");

			// Setup style
			ImGui::StyleColorsDark();

			// Setup style
			ImGui::StyleColorsDark();

			while (!window->closed())
			{
				
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				//Render
				frameBuffer->bind();
				GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
				GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
				GLCall(glEnable(GL_DEPTH_TEST));

				
				light.update();
				skybox.update(camera, camera.getProjection());

				shader->enable();
				
				//sponza->draw();

				

				//crysis->setTransform(glm::vec3(0.0f, -5.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
				crysis->draw();

				
				throne->draw();
				
				garrosh->draw();

				frameBuffer->unbind();
				GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
				GLCall(glClear(GL_COLOR_BUFFER_BIT));
				GLCall(glEnable(GL_DEPTH_TEST));
					
				ImGui::Begin("Scene Window");

				ImVec2 pos = ImGui::GetCursorScreenPos();

				ImGui::GetWindowDrawList()->AddImage(
					(void *)frameBuffer->GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
					ImVec2(ImGui::GetCursorScreenPos().x + 1920 / 2, ImGui::GetCursorScreenPos().y + 1080 / 2), ImVec2(0, 1), ImVec2(1, 0));

				ImGui::End();
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				//Render
				camera.update();
				window->update();

			}

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

		}
	};
}