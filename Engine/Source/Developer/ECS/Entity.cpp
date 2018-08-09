#include "entity.h"

namespace Skel
{
	Entity::Entity(Model* mesh, Shader* shader)
	{
		addComponent(new MeshComponent(mesh));
		m_transform = Transform(shader);
		m_shader = shader;
	}

	void Entity::addComponent(Component* component)
	{
		m_components[component->getComponentType()] = component;
	}

	void Entity::draw()
	{
		if (m_visible)
		{
			m_shader->setUniformMat4("model", m_transform.getTransformMatrice());
			auto mesh = getComponent<MeshComponent>();
			mesh->draw(m_shader);
		}
	}

	void Entity::setSize(float x, float y, float z)
	{
		m_transform.getTransformMatrice() = m_transform.setSize(x, y, z); // This is bad code
	}

	void Entity::setRotation(float angle, bool x /*= true*/, bool y /*= true*/, bool z /*= true*/)
	{
		m_transform.getTransformMatrice() = m_transform.setRotation(angle, x, y, z); // This is bad code
	}

	void Entity::setPosition(float x, float y, float z)
	{
		m_transform.getTransformMatrice() = m_transform.setPosition(x, y, z); // This is bad code
	}

	void Entity::setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle)
	{
		m_transform.getTransformMatrice() = m_transform.setTransform(position, size, rotation, angle); // This is bad code
	}

	void Entity::setVisibility(bool visible)
	{
		m_visible = visible;
	}

	void Entity::SetTransformMatrix(glm::mat4 matrix)
	{
		m_transform.getTransformMatrice() = matrix;
	}

}

