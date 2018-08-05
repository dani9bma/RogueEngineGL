/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include "../../Common/Types.h"
#include "../../Common/Defines.h"
#include <string>

namespace Skel
{
	class Entity;

	struct ComponentType
	{
		std::string name;
	};

	class SKEL_API Component
	{
	protected:
		Entity * m_entity;

	public:
		virtual Entity* getEntity() const { return m_entity; }
		virtual ComponentType* getComponentType() const { return nullptr; }
	};

}

