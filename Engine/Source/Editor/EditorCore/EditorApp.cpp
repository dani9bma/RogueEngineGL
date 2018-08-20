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
		m_window = new Window(1600, 900, "Skel Engine");
		shader = new Shader(FileSystem::LoadResource("Shaders\\basic.vert"), FileSystem::LoadResource("Shaders\\basic.frag"));
		skyboxShader = new Shader(FileSystem::LoadResource("Shaders\\cubemap.vert"), FileSystem::LoadResource("Shaders\\cubemap.frag"));
        
		shader->enable();
        
		camera = new Camera(0.2f, m_window, shader);
        
		light = new DirectionalLight(shader, camera);
		glm::vec3 lightPos(0.0f, -5.0f, -2.0f);
		light->setLightDirection(lightPos);
		light->setIntensity(1.0f);
        
		skybox = new Skybox(skyboxShader);
        
		crysisModel = new Model(FileSystem::LoadResource("models\\nanosuit\\nanosuit.obj"));
		garroshModel = new Model(FileSystem::LoadResource("models\\Praying.dae"));
		sponzaModel = new Model(FileSystem::LoadResource("models\\knob\\mitsuba.obj"));
		knobModel = new Model(FileSystem::LoadResource("models\\knob\\mitsuba.obj"));
        
		sponza = new Entity(sponzaModel, shader);
		sponza->setPosition(-50.0f, -5.0f, 30.0f);
		sponza->setSize(4.0f, 4.0f, 4.0f);
        
		garrosh = new Entity(garroshModel, shader);
		garrosh->setPosition(7.0f, -9.0f, -2.0f);
		garrosh->setSize(1.0f, 1.0f, 1.0f);
        
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
		io.Fonts->AddFontFromFileTTF(FileSystem::LoadResource("fonts/Roboto-Regular.ttf").c_str(), 16.0f);
        
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
        
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
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
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("CreateProject"))
				{
					createProjectPopup = true;
				}
				if (ImGui::MenuItem("Load Project"))
				{
					loadProjectPopup = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Debug Window"))
				{
					debug = true;
				}
				if (ImGui::MenuItem("Project Settings"))
				{
					settings = true;
				}
				if (ImGui::MenuItem("Transform Window"))
				{
					transform = true;
				}
				if (ImGui::MenuItem("Game Window"))
				{
					dock = true;
				}
				ImGui::EndMenu();
			}
            
			ImGui::EndMainMenuBar();
		}
        
		if (createProjectPopup)
		{
			ImGui::Begin("Create Project", &createProjectPopup);
			ImGui::InputText("Project Name", name, sizeof(name));
			ImGui::Text(path.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Choose Directory"))
				dialog = true;
			if (ImGui::Button("Create Project"))
			{
				BuildTool::CreateProject(name, path.c_str());
				createProjectPopup = false;
			}
			ImGui::End();
		}
        
		if (loadProjectPopup)
		{
			ImGui::Begin("Load Project", &loadProjectPopup);
			ImGui::Text(projectPath.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Choose Project To Load"))
				loadDialog = true;
			if (ImGui::Button("Load Project"))
			{
				if (gameDLL)
				{
					FreeLibrary(gameDLL);
				}
                
				nlohmann::json j;
				SKString FullProjectPath = projectPath.c_str();
				FullProjectPath.append("\\");
				FullProjectPath.append(projectName.c_str());
				j = BuildTool::ReadSKProject(FullProjectPath);
				std::string dllPath = j["dll"];
				std::string n = j["name"];
				BuildTool::CompileProject(projectPath.c_str(), n.c_str());
				gameDLL = LoadLibraryA(dllPath.c_str());
				loadProjectPopup = false;
			}
			ImGui::End();
		}
		
        
		if (ImGui::Begin("Engine", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			ImGui::SetWindowPos("Engine", ImVec2(-2.0f, 15.0f));
			ImGui::SetWindowSize("Engine", ImVec2(m_window->GetWidth(), m_window->GetHeight()));
			// dock layout by hard-coded or .ini file
			ImGui::BeginDockspace();
			
			if (ImGui::BeginDock("Game", &dock)) 
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
				ImGui::SameLine();
				if (ImGui::Button("Compile"))
				{
					//Compile the game code
					FreeLibrary(gameDLL);
					nlohmann::json j;
					SKString FullProjectPath = projectPath.c_str();
					FullProjectPath.append("\\");
					FullProjectPath.append(projectName.c_str());
					j = BuildTool::ReadSKProject(FullProjectPath);
					std::string n = j["name"];
					BuildTool::CompileProject(projectPath.c_str(), n.c_str());
					std::string dllPath = j["dll"];
					gameDLL = LoadLibraryA(dllPath.c_str());
				}
				size = ImGui::GetWindowSize();
                
				ImGui::GetWindowDrawList()->AddImage(
					(void *)frameBuffer->GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
					ImVec2((ImGui::GetCursorScreenPos().x + size.x) - 22.0f, (ImGui::GetCursorScreenPos().y + size.y) - 60.0f), ImVec2(0, 1), ImVec2(1, 0));
                
				/*GUIZMO*/
				ImGuizmo::SetDrawlist();
                
				static const float identityMatrix[16] =
				{ 1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };
                
				//ImGuizmo::DrawCube(glm::value_ptr(camera->getView()), glm::value_ptr(camera->getProjection()), objectMatrix);
				float* objectMatrix = glm::value_ptr(crysis->getTransform().getTransformMatrice());
                
                
				static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
				static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
				static bool useSnap = false;
				static float snap[3] = { 1.f, 1.f, 1.f };
				static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
				static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
				static bool boundSizing = false;
				static bool boundSizingSnap = false;
                
				if (SKInput::isKeyPressed(m_window, KEY_W))
					mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
				if (SKInput::isKeyPressed(m_window, KEY_E))
					mCurrentGizmoOperation = ImGuizmo::ROTATE;
				if (SKInput::isKeyPressed(m_window, KEY_R))
					mCurrentGizmoOperation = ImGuizmo::SCALE;
				if (mCurrentGizmoOperation != ImGuizmo::SCALE)
				{
					mCurrentGizmoMode = ImGuizmo::WORLD;
				}
				else
				{
					mCurrentGizmoMode = ImGuizmo::LOCAL;
				}
                
				ImGuiIO& io = ImGui::GetIO();
				ImGuizmo::SetRect(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y, (ImGui::GetCursorScreenPos().x + size.x) - 2.0f, (ImGui::GetCursorScreenPos().y + size.y) - 15.0f);
				ImGuizmo::Manipulate(glm::value_ptr(camera->getView()), glm::value_ptr(camera->getProjection()), mCurrentGizmoOperation, mCurrentGizmoMode, objectMatrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
                
				crysis->SetTransformMatrix(glm::make_mat4(objectMatrix));
                
			}
			ImGui::EndDock();
			
			if (ImGui::BeginDock("Debug", &debug)) 
			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::EndDock();
			
			if (ImGui::BeginDock("Transform", &transform)) 
			{
				ImGui::Text("TODO");
			}
			ImGui::EndDock();
			
			ImGui::EndDockspace();
		}	
		ImGui::End();
        
		if (dialog)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Choose Directory", 0, ".", ""))
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
        
		if (loadDialog)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Choose Project", 0, ".", ""))
			{
				if (ImGuiFileDialog::Instance()->IsOk == true)
				{
					projectPath = ImGuiFileDialog::Instance()->GetCurrentPath();
					projectName = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					projectPath = "";
				}
				loadDialog = false;
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

using namespace Skel;

int main()
{
	EditorApp app;
	app.Start();
}