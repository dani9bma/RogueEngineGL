/*
* @module UI
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "ui_window.h"

namespace Skel
{

	UIWindow::UIWindow(Window* window, UIStyle style, const char* title, const char* fontPath /*= ""*/, float fontSize /*= 18.0f*/)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (fontPath != "")
			io.Fonts->AddFontFromFileTTF(fontPath, fontSize);
		ImGui_ImplGlfwGL3_Init(window->getGLFWwindow(), true);
		switch (style)
		{
		case Dark:
			ImGui::StyleColorsDark();
			break;
		case Light:
			ImGui::StyleColorsLight();
			break;
		default:
			break;
		}
	}

	UIWindow::~UIWindow()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void UIWindow::Begin()
	{
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::Begin("Debug");
	}

	void UIWindow::End()
	{
		ImGui::End();		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UIWindow::AddButton(const char* title, void(*func)())
	{
		if (ImGui::Button(title))
			func();
	}

	void UIWindow::AddLabel(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		ImGui::TextV(fmt, args);
		va_end(args);
	}

}


