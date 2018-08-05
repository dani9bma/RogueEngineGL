/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include "../Core/Window.h"
#include "../Graphics/Shader.h"

namespace Skel
{
	class Camera
	{
	public:
		Camera() {};
		Camera(int width, int height, float sensitivity, Window* window, Shader* shader);
		~Camera();
		void update();
		inline glm::mat4 getView() const { return m_view; }
		inline glm::vec3 getPosition() const { return m_cameraPos; }
		inline void setGameMode(bool gm) { m_gameMode = gm; }
		inline glm::mat4 getProjection() const { return m_projection; }
		void changeFOV(float value);
	private:
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraDirection;
		glm::vec3 m_cameraRight;
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;
		float m_sensitivity;
		float m_deltaTime;
		float m_lastFrame;
		float m_lastX;
		float m_lastY;
		float m_yaw;
		float m_pitch;
		float m_fov;
		Window* m_window;
		Shader* m_shader;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		bool m_gameMode = true;
		double m_x = 0, m_y = 0;
		double m_lastSysX = 0, m_lastSysY = 0;
		int timer = 0;
	};
}