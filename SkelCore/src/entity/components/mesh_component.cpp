/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "mesh_component.h"

namespace Skel { namespace entity { namespace component {


	MeshComponent::MeshComponent(graphics::Model* mesh)
		: m_mesh(mesh)
	{
	}

	void MeshComponent::draw(graphics::Shader* shader)
	{
		m_mesh->Draw(shader);
	}

} } }