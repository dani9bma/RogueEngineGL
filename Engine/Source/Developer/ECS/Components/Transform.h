#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../../Graphics/shader.h"

namespace Skel
{
	class SKEL_API Transform
	{
	private:
		glm::mat4 m_transform;

		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec3 m_rotation;
		float	  m_angle;

		Shader* m_shader;
	public:
		Transform();
		Transform(Shader* shader);
		/*
		* angle in degrees
		*/
		glm::mat4 setRotation(float angle, bool x = true, bool y = true, bool z = true);
		glm::mat4 setPosition(float x, float y, float z);
		glm::mat4 setSize(float x, float y, float z);
		glm::mat4 setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle);

		inline glm::vec3 getPosition() { return m_position; }
		inline glm::vec3 getRotation() { return m_rotation; }
		inline glm::vec3 getSize() { return m_size; }

		inline glm::mat4& getTransformMatrice() { return m_transform; }
	};
}