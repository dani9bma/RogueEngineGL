/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <string>

namespace Skel { namespace entity {
	class Entity;
} }

namespace Skel { namespace entity { namespace component {

	struct ComponentType
	{
		std::string name;
	};

	class Component
	{
	protected:
		Entity* m_entity;

	public:
		virtual Entity* getEntity() const { return m_entity; }
		virtual ComponentType* getComponentType() const { return nullptr; }
	};

}}}