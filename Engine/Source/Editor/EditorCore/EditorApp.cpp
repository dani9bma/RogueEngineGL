#include "EditorApp.h"

namespace Skel
{
	void EditorApp::Start()
	{
		OnInit();
		SK_LOG(LogLevel::Warning, LogModule::System, "Skel Editor Initialized");
		Run();
	}

	void EditorApp::Run()
	{
		double lastTime = ImGui::GetTime();
		int nbFrames = 0;

		while (!m_window->IsClosed())
		{
			double currentTime = ImGui::GetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0) {
				nbFrames = 0;
				lastTime += 1.0;
			
			}
			OnTick(lastTime);
		}

		OnDestroy();
	}

	void EditorApp::OnInit()
	{
		m_window = new Window(1280, 720, "Skel Engine");
		shader = new Shader("../Engine/Content/Shaders/basic.vert", "../Engine/Content/Shaders/basic.frag");
		skyboxShader = new Shader("../Engine/Content/Shaders/cubemap.vert", "../Engine/Content/Shaders/cubemap.frag");

		shader->enable();

		camera = new Camera(0.2f, m_window, shader);

		light = new DirectionalLight(shader, camera);
		glm::vec3 lightPos(0.0f, -5.0f, -2.0f);
		light->setLightDirection(lightPos);
		light->setIntensity(1.0f);

		skybox = new Skybox(skyboxShader);

		crysisModel = new Model("../Engine/Content/models/nanosuit/nanosuit.obj");
		garroshModel = new Model("../Engine/Content/models/floor.obj");
		sponzaModel = new Model("../Engine/Content/models/knob/mitsuba.obj");
		knobModel = new Model("../Engine/Content/models/knob/mitsuba.obj");

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

		frameBuffer = new FrameBuffer();
		// Setup Dear ImGui binding
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF("../Engine/Content/fonts/Roboto-Regular.ttf", 17.0f);
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

		ImGui_ImplGlfw_InitForOpenGL(m_window->getGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");

		// Setup style
		ImGui::StyleColorsSkel();

		ImGui::InitDock();

	}

	void EditorApp::OnTick(float DeltaTime)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Render
		frameBuffer->bind(m_window->GetWidth(), m_window->GetHeight());
		
		GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		light->update();
		skybox->Update(camera, camera->getProjection());

		shader->enable();


		//crysis->setTransform(glm::vec3(0.0f, -5.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
		crysis->draw();

		garrosh->draw();

		sponza->draw();
		knob->draw();

		frameBuffer->unbind();
		GLCall(glClearColor(0.2f, 0.3f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		if (ImGui::Begin("Engine", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			ImGui::SetWindowPos("Engine", ImVec2(0.0f, 20.0f));
			ImGui::SetWindowSize("Engine", ImVec2(m_window->GetWidth(), m_window->GetHeight()));
			// dock layout by hard-coded or .ini file
			ImGui::BeginDockspace();
	
			if (ImGui::BeginDock("Game"), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus)
			{
				if (m_window->IsPaused())
				{
					if (ImGui::Button("Play", ImVec2(50, 0)))
						m_window->SetGameState(PLAY);
				}
				else
				{
					if (ImGui::Button("Pause"))
						m_window->SetGameState(PAUSED);
				}
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Game")) 
			{
				size = ImGui::GetWindowSize();

				ImGui::GetWindowDrawList()->AddImage(
					(void *)frameBuffer->GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
					ImVec2((ImGui::GetCursorScreenPos().x + size.x) - 2.0f, (ImGui::GetCursorScreenPos().y + size.y) - 15.0f), ImVec2(0, 1), ImVec2(1, 0));
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Debug")) 
			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Transform")) 
			{
				ImGui::Text("TODO");
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Project Settings"))
			{
			
				ImGui::InputText("Project Name", name, sizeof(name));
				ImGui::Text(path.c_str());
				ImGui::SameLine();
				if (ImGui::Button("Choose Directory"))
					dialog = true;
				if (ImGui::Button("Create Project"))
				{
					BuildTool::CreateProject(name, path.c_str());
				}
				if (ImGui::Button("Load Project"))
				{
					//First user will locate the .skproject file
					//Load the project DLL
				}

			}
			ImGui::EndDock();

			ImGui::EndDockspace();
		}	
		ImGui::End();

		if (dialog)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Choose Directory", ".cpp\0.h\0.hpp\0\0", ".", ""))
			{
				if (ImGuiFileDialog::Instance()->IsOk == true)
				{
					path = ImGuiFileDialog::Instance()->GetCurrentPath();
				}
				else
				{
					path = "";
				}
				dialog = false;
			}
		}
	
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		//Render
		if (!m_window->IsPaused())
			camera->update();
			
		m_window->Update();
	}

	void EditorApp::OnDestroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

#include <json.hpp>
#include <iomanip>

using namespace Skel;
using namespace nlohmann;

int main()
{
	EditorApp app;
	app.Start();
}