/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "MeshComponent.h"

namespace Skel
{
	MeshComponent::MeshComponent(Model* mesh)
		: m_mesh(mesh)
	{
	}

	void MeshComponent::draw(Shader* shader)
	{
		m_mesh->Draw(shader);
	}
}

