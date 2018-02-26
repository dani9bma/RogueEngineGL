/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include "component.h"
#include "../entity.h"
#include "../../graphics/model.h"
#include "../../graphics/opengl/shader.h"


namespace Skel { namespace entity { namespace component {

	class MeshComponent : public Component
	{
	private:
		graphics::Model* m_mesh;

	public:
		MeshComponent(graphics::Model* mesh);
		void draw(graphics::Shader* shader);

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "Mesh" });
			return &type;
		}

		inline virtual ComponentType* getComponentType() const override { return getStaticType(); }

	};

}}}