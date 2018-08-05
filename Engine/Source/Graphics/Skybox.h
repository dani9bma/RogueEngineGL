#pragma once
#include "Shader.h"
#include "../Scene/Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

#include <string>
#include <vector>

#include "stb_image.h"

namespace Skel
{
	class Skybox
	{
	private:
		unsigned int m_skyboxVAO;
		Shader* m_shader;
		Camera m_camera;
		VertexArray m_vao = VertexArray();
		Texture m_texture = Texture();

		void loadCubemap();
	public:
		Skybox() {}
		Skybox(Shader* shader);
		~Skybox();
		void update(Camera camera, glm::mat4 projection);
	};

}