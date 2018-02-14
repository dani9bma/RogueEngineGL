/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Skel { namespace graphics {

	Texture::Texture(const char* path, Shader shader)
	{
		unsigned int texture;
		GLCall(glGenTextures(1, &texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));
		//set the texture wrapping parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		//sets the texture filtering parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0/*Level of detail*/, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else
		{
			//#TODO: Create Log Class and log this
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		shader.enable();
		shader.setUniform1i("ourTexture", 0);
		m_textureID = texture;
	}

	Texture::~Texture()
	{
	}

	void Texture::draw()
	{
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	}

} }