/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "entity.h"

namespace Skel { namespace entity {


	Entity::Entity(graphics::Model* mesh, graphics::Shader* shader)
	{
		addComponent(new component::MeshComponent(mesh));
		m_transform = maths::Transform(shader);
		m_oldTransform = m_transform.getTransformMatrice();
		m_shader = shader;
	}

	void Entity::addComponent(component::Component* component)
	{
		m_components[component->getComponentType()] = component;
	}

	void Entity::draw()
	{
		m_shader->setUniformMat4("model", m_transform.getTransformMatrice());
		auto mesh = getComponent<entity::component::MeshComponent>();
		mesh->draw(m_shader);
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

} }