/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "window.h"

namespace Skel { namespace graphics {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0.5, 0.0, width, height);
	}

	Window::Window(int width, int height, const char* title)
		: m_width(width), m_height(height), m_title(title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_window)
		{
			//#TODO: Create Log Class and log this
			std::cout << "[GRAPHICS::WINDOW] Failed to Create Window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to Initialize GLEW!" << std::endl;
			return;
		}
		//#TODO: Create Log Class and log this
		std::cout << "[GRAPHICS::WINDOW] Glew Initialized: " << glewGetString(GLEW_VERSION) << "\n[GRAPHICS::WINDOW] OpenGL Initialized: " << glGetString(GL_VERSION) << std::endl;
		glViewport(0.5, 0.0, m_width, m_height);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	int Window::closed()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(m_window, 1);
	}

} }