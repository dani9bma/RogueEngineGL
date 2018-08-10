#pragma once

#include <src/GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Utils/Log.h"
#include "../Common/Common.h"

namespace Skel
{
	enum GameState
	{
		PAUSED,
		PLAY
	};

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
		inline int GetWidth() { if (m_width == 0) m_width = 1600; return m_width; }
		inline int GetHeight() { if (m_height == 0) m_height = 900; return m_height; }
		inline void SetGameState(GameState state) { if (state == PAUSED) m_paused = true; else m_paused = false; }
		inline bool IsPaused() const { return m_paused; }

		void setMousePosition(double x, double y);
	private:
		int m_width;
		int m_height;
		double m_lastTime;
		int m_fps;
		double m_x = 0, m_y = 0;
		SKString m_title;
		GLFWwindow* m_window;
		bool m_wireframe = false;
		bool m_paused = true;

	private:
		friend static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		
	};
}