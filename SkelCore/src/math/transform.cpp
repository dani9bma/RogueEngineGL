/*
 * @module Maths
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "transform.h"

namespace Skel { namespace maths {

	Transform::Transform()
	{
	}

	Transform::Transform(graphics::Shader* shader)
		:m_shader(shader)
	{
		m_transform = glm::translate(m_transform, glm::vec3(0.0f, -5.0, -2.0f));
		m_transform = glm::scale(m_transform, glm::vec3(0.1f, 0.1f, 0.1f));
		m_transform = glm::rotate(m_transform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_position = glm::translate(m_position, glm::vec3(0.0f, -5.0, -2.0f));
		m_size = glm::scale(m_size, glm::vec3(0.1f, 0.1f, 0.1f));
		m_rotation = glm::rotate(m_rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		shader->setUniformMat4("model", m_transform);
	}

	glm::mat4 Transform::setRotation(float angle, bool x /*= true*/, bool y /*= true*/, bool z /*= true*/)
	{
		float xPos = x ? 1.0f : 0.0f;
		float yPos = y ? 1.0f : 0.0f;
		float zPos = z ? 1.0f : 0.0f;

		glm::mat4 rotation;
		
		m_transform = glm::rotate(m_transform, glm::radians(angle), glm::vec3(xPos, yPos, zPos));
		//m_transform = glm::translate(m_position, glm::vec3(1.0f, 1.0f, 1.0f));
		//m_transform = glm::scale(m_size, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 r;

		m_rotation = glm::rotate(r, glm::radians(angle), glm::vec3(xPos, yPos, zPos));

		return m_transform;
	}

	glm::mat4 Transform::setPosition(float x, float y, float z)
	{
		glm::mat4 position;

		m_transform = glm::translate(m_transform, glm::vec3(x, y, z));
		//m_transform = glm::scale(m_size, glm::vec3(1.0f, 1.0f, 1.0f));
		//m_transform = glm::rotate(m_rotation, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 s;

		m_position = glm::translate(s, glm::vec3(x, y, z));

		return m_transform;
	}

	glm::mat4 Transform::setSize(float x, float y, float z)
	{
		glm::mat4 size;

		m_transform = glm::scale(m_transform, glm::vec3(x, y, z));
		//m_transform = glm::translate(m_position, glm::vec3(1.0f, 1.0f, 1.0f));
		//m_transform = glm::rotate(m_rotation, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 s;

		m_size = glm::scale(s, glm::vec3(x, y, z));

		return m_transform;
	}

} }