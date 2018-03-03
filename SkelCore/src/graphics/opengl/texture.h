/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <GL/glew.h>
#include <iostream>
#include "shader.h"

#include "../../utils/common.h"
#include "../../utils/log.h"

namespace Skel
{
	class Texture
	{
	public:
		Texture() { }
		Texture(int id) { m_textureID = id; }
		Texture(const char* path, Shader* shader);
		Texture(std::string path);
		void loadCubemapTexture(const char* path, int index);
		~Texture();
		void draw(int n);
		inline unsigned int getID() { return m_textureID; }
	private:
		unsigned int m_textureID;
	};
}