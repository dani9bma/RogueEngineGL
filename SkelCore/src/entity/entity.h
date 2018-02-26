/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include "../graphics/model.h"
#include "../graphics/opengl/shader.h"
#include "components/component.h"
#include "components/mesh_component.h"
#include "../math/transform.h"

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Skel { namespace entity {

	class Entity
	{
	private:
		std::unordered_map<component::ComponentType*, component::Component*> m_components;
		maths::Transform m_transform;
		glm::mat4 m_oldTransform;
		graphics::Shader* m_shader;
	public:
		Entity() { }
		Entity(graphics::Model* mesh, graphics::Shader* shader);
		void addComponent(component::Component* component);
		void draw();
		void setSize(float x, float y, float z);
		void setRotation(float angle, bool x = true, bool y = true, bool z = true);
		void setPosition(float x, float y, float z);
		void setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle);

		template <typename T>
		T* getComponent()
		{
			component::ComponentType* type = T::getStaticType();
			auto it = m_components.find(type);
			if (it == m_components.end())
				return nullptr;

			return (T*)it->second;
		}

		inline maths::Transform getTransform() const { return m_transform; } // Make this a component
	};

} }