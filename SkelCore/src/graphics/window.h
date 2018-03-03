/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../utils/log.h"
#include "../utils/common.h"

namespace Skel
{
	class Window
	{
	public:
		Window(int width, int height, const char*);
		~Window();
		void update();
		int closed();
		void close();
		inline GLFWwindow* getGLFWwindow() const { return m_window; }
		inline void getMousePosition(double& x, double& y) const { x = m_x; y = m_y; };
	private:
		int m_width;
		int m_height;
		double m_lastTime;
		int m_fps;
		double m_x, m_y;
		std::string m_title;
		GLFWwindow* m_window;
		bool m_wireframe = false;

	private:
		friend static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	};
}