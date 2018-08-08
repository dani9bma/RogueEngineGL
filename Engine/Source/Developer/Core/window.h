/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <src/GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Utils/Log.h"
#include "../Common/Common.h"

namespace Skel
{
	class SKEL_API Window
	{
	public:
		Window(int width, int height, const char*);
		~Window();
		void Update();
		int IsClosed();
		void Close();
		inline GLFWwindow* getGLFWwindow() const { return m_window; }
		inline void getMousePosition(double& x, double& y) const { x = m_x; y = m_y; };
		inline int GetWidth() { if (m_width == 0) m_width = 1280; return m_width; }
		inline int GetHeight() { if (m_height == 0) m_height = 720; return m_height; }

		void setMousePosition(double x, double y);
	private:
		int m_width;
		int m_height;
		double m_lastTime;
		int m_fps;
		double m_x = 0, m_y = 0;
		eastl::string m_title;
		GLFWwindow* m_window;
		bool m_wireframe = false;

	private:
		friend static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		
	};
}