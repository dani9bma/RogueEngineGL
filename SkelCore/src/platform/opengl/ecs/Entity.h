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
#include "components/MeshComponent.h"
#include "../math/transform.h"

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Skel
{

	class Entity
	{
	private:
		std::unordered_map<ComponentType*, Component*> m_components;
		Transform m_transform;
		Shader* m_shader;
		bool m_visible = true;
	public:
		Entity() { }
		Entity(Model* mesh, Shader* shader);
		void addComponent(Component* component);
		void draw();
		void setSize(float x, float y, float z);
		void setRotation(float angle, bool x = true, bool y = true, bool z = true);
		void setPosition(float x, float y, float z);
		void setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle);
		void setVisibility(bool visible);

		template <typename T>
		T* getComponent()
		{
			ComponentType* type = T::getStaticType();
			auto it = m_components.find(type);
			if (it == m_components.end())
				return nullptr;

			return (T*)it->second;
		}

		inline Transform getTransform() const { return m_transform; }
	};
}