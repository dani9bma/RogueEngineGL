/*
* @module UI
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "../imgui/imgui.h"
#include "../platform/opengl/graphics/window.h"
#include <GLFW/glfw3.h>
#include <functional>

extern bool        ImGui_ImplGlfwGL3_Init(GLFWwindow* window, bool install_callbacks);
extern void        ImGui_ImplGlfwGL3_Shutdown();
extern void        ImGui_ImplGlfwGL3_NewFrame();
extern void        ImGui_ImplGlfwGL3_RenderDrawData(ImDrawData* draw_data);
extern void        ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
extern bool        ImGui_ImplGlfwGL3_CreateDeviceObjects();

namespace Skel
{
	enum UIStyle
	{
		Dark,
		Light
	};

	class UIWindow
	{
	public:
		UIWindow(Window* window, UIStyle style, const char* title, const char* fontPath = "", float fontSize = 18.0f);
		~UIWindow();
		void Begin();
		void End();
		void AddButton(const char* title, void(*func)());
		void AddLabel(const char* fmt, ...);
	private:
		const char* m_title;
		Window* m_window;
		ImGuiIO& io = ImGuiIO();
	};
}
