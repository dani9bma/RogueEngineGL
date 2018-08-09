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
#include "Source/Developer/BuildTool/BuildTool.h"
#include "Source/Developer/Physics/DebugDrawer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Source/Developer/Utils/Input.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGUI/imgui_dock.h>
#include <ImGUI/ImGuiFileDialog.h>
#include <ImGUI/ImGuizmo.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


namespace Skel
{
	class EditorApp
	{
	public:
		void Start(); //Starts Init, Tick, Update
		void Run();
		void OnInit();
		void OnTick(float DeltaTime);
		void OnDestroy();
		FORCEINLINE Window* GetWindow() const { return m_window; }
	public:

		Entity* sponza = nullptr;
		Entity* garrosh = nullptr;
		Entity* crysis = nullptr;
		Entity* knob = nullptr;

		Shader* shader = nullptr;
		Shader* skyboxShader = nullptr;
		Camera* camera = nullptr;
		DirectionalLight* light = nullptr;
		Skybox* skybox = nullptr;

		Model* crysisModel = nullptr;
		Model* garroshModel = nullptr;
		Model* sponzaModel = nullptr;
		Model* knobModel = nullptr;

		FrameBuffer* frameBuffer = nullptr;
		ImVec2 size = ImVec2(1280, 720);

		std::string path = "";
		bool dialog = false;
		char name[1024] = {};
		float* objectMatrix;
		glm::vec4 lRayStart_world;
		glm::vec4 lRayEnd_world;
		glm::vec3 lRayDir_world;
		btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	private:
		Window * m_window = nullptr;
		bool m_paused = true;
	};
}