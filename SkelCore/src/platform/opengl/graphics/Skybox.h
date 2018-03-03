#pragma once
#include "opengl/shader.h"
#include "camera/camera.h"
#include "opengl/VertexArray.h"
#include "opengl/VertexBuffer.h"
#include "opengl/texture.h"

#include <string>
#include <vector>

#include "opengl/stb_image.h"

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