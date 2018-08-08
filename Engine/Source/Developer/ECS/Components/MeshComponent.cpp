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

