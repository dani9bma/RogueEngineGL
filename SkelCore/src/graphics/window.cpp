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

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		auto* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_x = xpos;
		win->m_y = ypos;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		/*if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);*/
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
			LOG_ERROR("GRAPHICS::WINDOW", "Failed to create Window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK)
		{
			LOG_ERROR("GRAPHICS", "Failed to load GLEW");
			return;
		}

		LOG_INFO("GRAPHICS", "GLEW Initialized %s", glewGetString(GLEW_VERSION));
		LOG_INFO("GRAPHICS", "OpenGL initialized %s", glGetString(GL_VERSION));
		glViewport(0.5, 0.0, m_width, m_height);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		glfwSetCursorPosCallback(m_window, mouse_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetWindowUserPointer(m_window, this);
		glfwSwapInterval(0); //V-Sync
		m_lastTime = glfwGetTime();
		m_fps = 0;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::update()
	{
		// Measure speed
		double currentTime = glfwGetTime();
		m_fps++;
		if (currentTime - m_lastTime >= 1.0) // If last prinf() was more than 1 sec ago
		{ 
			LOG_INFO("UTILS", "%d FPS", m_fps);
			m_fps = 0;
			m_lastTime += 1.0;
		}
		if (glfwGetKey(this->getGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			this->close();

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