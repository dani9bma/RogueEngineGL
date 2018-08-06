/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "Source/Developer/Graphics/opengl.h"
#include "Source/Developer/Core/window.h"
#include "Source/Developer/Scene/camera.h"
#include "Source/Developer/Scene/DirectionalLight.h"
#include "Source/Developer/Common/Common.h"
#include "Source/Developer/Utils/Log.h"
#include "Source/Developer/ECS/components/model.h"
#include "Source/Developer/Graphics/Skybox.h"
#include "Source/Developer/ECS/Entity.h"
#include "Source/Developer/Graphics/FrameBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Source/Developer/Utils/Input.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGUI/imgui_dock.h>

using namespace Skel;

Skel::Entity* sponza = nullptr;
Skel::Entity* garrosh = nullptr;
Skel::Entity* crysis = nullptr;
Skel::Entity* knob = nullptr;

int main(void)
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
	Model* garroshModel = new Model("../Engine/Res/models/floor.obj");
	Model* sponzaModel = new Model("../Engine/Res/models/knob/mitsuba.obj");
	Model* knobModel = new Model("../Engine/Res/models/knob/mitsuba.obj");

	sponza = new Entity(sponzaModel, shader);
	sponza->setPosition(-50.0f, -5.0f, 30.0f);
	sponza->setSize(4.0f, 4.0f, 4.0f);

	garrosh = new Entity(garroshModel, shader);
	garrosh->setPosition(7.0f, -9.0f, -2.0f);
	garrosh->setSize(50.0f, 4.0f, 50.0f);

	crysis = new Entity(crysisModel, shader);
	crysis->setPosition(0.0f, -5.0f, -2.0f);
	crysis->setSize(1.0f, 1.0f, 1.0f);
	crysis->setRotation(180.0f, false, true, false);

	knob = new Entity(knobModel, shader);
	knob->setPosition(0.0f, -5.0f, 30.0f);
	knob->setSize(4.0f, 4.0f, 4.0f);
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
	io.Fonts->AddFontFromFileTTF("../Engine/Res/fonts/Roboto-Regular.ttf", 17.0f);
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Setup style
	ImGui::StyleColorsDark();

	// Setup style
	ImGui::StyleColorsDark();

	ImGui::InitDock();

	ImVec2 size = ImVec2(1280, 720);

	while (!window->closed())
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Render
		frameBuffer->bind(size.x, size.y);
		GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		light.update();
		skybox.update(camera, camera.getProjection());

		shader->enable();


		//crysis->setTransform(glm::vec3(0.0f, -5.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
		crysis->draw();

		garrosh->draw();

		sponza->draw();
		knob->draw();

		frameBuffer->unbind();
		GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					// Exit...
					ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				//...
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				//...
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (ImGui::Begin("Engine", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			ImGui::SetWindowPos("Engine", ImVec2(0.0f, 5.0f));
			ImGui::SetWindowSize("Engine", ImVec2(window->GetWidth(), window->GetHeight()));
			// dock layout by hard-coded or .ini file
			ImGui::BeginDockspace();

			if (ImGui::BeginDock("Game")) {
				size = ImGui::GetWindowSize();

				ImGui::GetWindowDrawList()->AddImage(
					(void *)frameBuffer->GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
					ImVec2((ImGui::GetCursorScreenPos().x + size.x) - 2.0f, (ImGui::GetCursorScreenPos().y + size.y) - 15.0f), ImVec2(0, 1), ImVec2(1, 0));

			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Debug")) {
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Transform")) {
				ImGui::Text("TODO");
			}
			ImGui::EndDock();

			ImGui::EndDockspace();
		}
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