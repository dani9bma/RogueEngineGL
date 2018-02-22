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

namespace Skel { namespace graphics {

	class Texture
	{
	public:
		Texture(const char* path, Shader* shader);
		~Texture();
		void draw(int n);
	private:
		unsigned int m_textureID;
	};

} }