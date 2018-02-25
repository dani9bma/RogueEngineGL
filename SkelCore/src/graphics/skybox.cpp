#include "skybox.h"

namespace Skel { namespace graphics {

	void Skybox::loadCubemap()
	{
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		m_vao.bind();

		//Creation of the vertex buffer
		VertexBuffer VBO = VertexBuffer(skyboxVertices, sizeof(skyboxVertices), BufferUsage::STATIC);

		m_vao.addBuffer(0, 3, VBO, 3 * sizeof(float), (void*)0);

		std::vector<const char*> faces
		{
			"cubemaptextures/right.jpg",
			"cubemaptextures/left.jpg",
			"cubemaptextures/top.jpg",
			"cubemaptextures/bottom.jpg",
			"cubemaptextures/front.jpg",
			"cubemaptextures/back.jpg",

			//TGA: 
			/*
			*front, back, up, down, right, left
			**/
		};
		
		for (GLuint i = 0; i < faces.size(); i++)
		{
			m_texture.loadCubemapTexture(faces[i], i);
		}

	}

	void Skybox::update(Camera camera, glm::mat4 projection)
	{
		glDepthFunc(GL_LEQUAL);
		m_shader->enable();
		auto view = glm::mat4(glm::mat3(camera.getView()));
		m_shader->setUniformMat4("view", view);
		m_shader->setUniformMat4("projection", projection);
		m_vao.bind();
		m_texture.draw(0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		m_vao.unbind();
		glDepthFunc(GL_LESS);
	}

	Skybox::Skybox(Shader* shader)
		: m_shader(shader)
	{
		loadCubemap();
	}

	Skybox::~Skybox()
	{
	}

}}

