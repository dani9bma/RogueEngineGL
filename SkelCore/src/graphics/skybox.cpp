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

		/*unsigned int skyboxVBO;
		glGenVertexArrays(1, &m_skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(m_skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_skyboxVertices), &m_skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);*/

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

		/*glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);


		int width, height, nrChannels;
		unsigned char* data;
		

		for (GLuint i = 0; i < faces.size(); i++)
		{
			data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap failed to load" << std::endl; //#TODO: Change to own class
				stbi_image_free(data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/

	}

	void Skybox::update(Camera camera, glm::mat4 projection)
	{
		glDepthFunc(GL_LEQUAL);
		m_shader->enable();
		auto view = glm::mat4(glm::mat3(camera.getView()));
		m_shader->setUniformMat4("view", view);
		m_shader->setUniformMat4("projection", projection);
		//glBindVertexArray(m_skyboxVAO);
		m_vao.bind();
		m_texture.draw(0);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		m_vao.unbind();
		//glBindVertexArray(0);
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

