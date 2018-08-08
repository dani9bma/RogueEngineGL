#pragma once

#include "Camera.h"
#include "../Graphics/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Skel
{
	class SKEL_API DirectionalLight
	{
	public:
		DirectionalLight() {}
		DirectionalLight(Shader* shader, Camera* camera);
		~DirectionalLight();
		void update();
		void setLightDirection(glm::vec3 direction);
		void setIntensity(float value);
	private:
		Shader * m_shader;
		Camera* m_camera;
		glm::vec3 m_direction = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_intensity = glm::vec3(1.0f, 1.0f, 1.0f);
	};
}
