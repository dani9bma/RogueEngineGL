/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <src/GL/glew.h>
#include <iostream>
#include "shader.h"

#include "../Common/Common.h"
#include "../Utils/Log.h"
#include "../Common/Types.h"

namespace Skel
{
	class SKEL_API Texture
	{
	public:
		Texture() { }
		Texture(int id) { m_textureID = id; }
		Texture(const char* path, Shader* shader);
		Texture(EAString path);
		void loadCubemapTexture(const char* path, int index);
		~Texture();
		void draw(int n);
		inline unsigned int getID() { return m_textureID; }
	private:
		unsigned int m_textureID;
	};
}