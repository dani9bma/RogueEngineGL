/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Skel { namespace graphics {

	class Window
	{
	public:
		Window(int width, int height, const char*);
		~Window();
		void update();
		int closed();
		void close();
	private:
		int m_width;
		int m_height;
		double m_lastTime;
		int m_fps;
		std::string m_title;
		GLFWwindow* m_window;
	};

} }