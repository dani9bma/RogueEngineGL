/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#pragma once

#include <Windows.h>

namespace Skel
{
	class DXWindow
	{
	public:
		DXWindow(int width, int height, const char* title);
		~DXWindow();
		void update();
		bool closed();
		void close();
		inline HWND getHandle() const { return m_window; }
		inline void getMousePosition(double& x, double& y) const { x = m_x; y = m_y; };
		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	private:
		int m_width;
		int m_height;
		double m_lastTime;
		int m_fps;
		double m_x, m_y;
		const char* m_title;
		HWND m_window;
		HINSTANCE m_instance;
		bool m_wireframe = false;
		bool m_closed = false;
	};
}
