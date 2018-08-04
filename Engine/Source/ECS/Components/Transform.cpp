/*
 * @module Maths
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "transform.h"

namespace Skel
{
	Transform::Transform()
	{
	}

	Transform::Transform(Shader* shader)
		:m_shader(shader)
	{
		m_transform = glm::translate(m_transform, glm::vec3(0.0f, -5.0, -2.0f));
		m_transform = glm::scale(m_transform, glm::vec3(0.1f, 0.1f, 0.1f));
		m_transform = glm::rotate(m_transform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_position = glm::vec3(0.0f, -5.0f, -2.0f);
		m_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		m_size = glm::vec3(0.1f, 0.1f, 0.1f);
		m_angle = 180.0f;


		shader->setUniformMat4("model", m_transform);
	}

	glm::mat4 Transform::setRotation(float angle, bool x /*= true*/, bool y /*= true*/, bool z /*= true*/)
	{
		glm::mat4 s;

		float xPos = x ? 1.0f : 0.0f;
		float yPos = y ? 1.0f : 0.0f;
		float zPos = z ? 1.0f : 0.0f;


		s = glm::translate(s, m_position);
		s = glm::scale(s, m_size);
		s = glm::rotate(s, glm::radians(angle), glm::vec3(xPos, yPos, zPos));

		m_angle = angle;
		m_rotation = glm::vec3(xPos * angle, yPos * angle, zPos * angle);

		return s;
	}

	glm::mat4 Transform::setPosition(float x, float y, float z)
	{
		glm::mat4 s;

		s = glm::translate(s, glm::vec3(x, y, z));
		s = glm::scale(s, m_size);
		s = glm::rotate(s, glm::radians(m_angle), m_rotation);

		m_position = glm::vec3(x, y, z);

		return s;
	}

	glm::mat4 Transform::setSize(float x, float y, float z)
	{
		glm::mat4 s;

		s = glm::translate(s, m_position);
		s = glm::scale(s, glm::vec3(x, y, z));
		s = glm::rotate(s, glm::radians(m_angle), m_rotation);

		m_size = glm::vec3(x, y, z);

		return s;
	}

	glm::mat4 Transform::setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle)
	{
		glm::mat4 s;

		s = glm::translate(s, position);
		s = glm::scale(s, size);
		s = glm::rotate(s, glm::radians(angle), rotation);

		return s;
	}
}