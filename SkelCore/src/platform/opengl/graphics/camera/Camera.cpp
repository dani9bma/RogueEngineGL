/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */
	
#include "camera.h"
#include "..\..\..\..\utils\Input.h"

namespace Skel
{
	Camera::Camera(int width, int height, float sensitivity, Window* window, Shader* shader)
	{
		m_cameraPos = glm::vec3(0.0f, 0.0f, 0.f);
		m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
		m_cameraRight = glm::normalize(glm::cross(m_cameraUp, m_cameraDirection));
		m_cameraFront = glm::vec3(0.0f, 0.0f, -10.0f);
		m_cameraUp = glm::vec3(0.0f, 3.0f, 0.0f);
		m_deltaTime = 0.0f;
		m_lastFrame = 0.0f;
		m_lastX = width / 2;
		m_lastY = height / 2;
		m_yaw = 0.0f;
		m_pitch = 0.0f;
		m_sensitivity = sensitivity;
		m_window = window;
		m_shader = shader;
	}

	Camera::~Camera()
	{
	}

	void Camera::update()
	{
		float cameraSpeed = 70.0f * m_deltaTime;
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		double x = 0, y = 0;

		if (m_gameMode)
		{
			//#TODO: Make Input class
			if (Input::isKeyPressed(m_window, KEY_W))
				m_cameraPos += cameraSpeed * m_cameraFront;
			if (Input::isKeyPressed(m_window, KEY_S))
				m_cameraPos -= cameraSpeed * m_cameraFront;
			if (Input::isKeyPressed(m_window, KEY_A))
				m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
			if (Input::isKeyPressed(m_window, KEY_D))
				m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
			if (Input::isKeyPressed(m_window, KEY_LEFT_SHIFT))
				m_cameraPos -= cameraSpeed * m_cameraUp;
			if (Input::isKeyPressed(m_window, KEY_SPACE))
				m_cameraPos += cameraSpeed * m_cameraUp;

			Input::GetMousePosition(m_window, x, y);
		}
	
		float xoffset = x - m_lastX;
		float yoffset = m_lastY - y;
		m_lastX = x;
		m_lastY = y;
		xoffset *= m_sensitivity;
		yoffset *= m_sensitivity;

		m_yaw += xoffset;

		m_pitch += yoffset;

		if (m_pitch > 89.f)
			m_pitch = 89.f;
		if (m_pitch < -89.f)
			m_pitch = -89.f;

		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_cameraFront = glm::normalize(front);
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
		m_shader->setUniformMat4("view", m_view);
	}
}