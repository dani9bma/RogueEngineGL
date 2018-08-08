#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <src/GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Common/Common.h"
#include "../Utils/Log.h"

namespace Skel
{
	class SKEL_API Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();
		void enable();
		void disable();
		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const glm::vec2& vector);
		void setUniform3f(const GLchar* name, const glm::vec3& vector);
		void setUniform4f(const GLchar* name, const glm::vec4& vector);
		void setUniform4f(const GLchar* name, float r, float g, float b, float w);
		void setUniformMat4(const GLchar* name, const glm::mat4 matrix);
		int getUniformLocation(const GLchar* name);
		inline unsigned int getID() { return m_shaderID; }
	private:
		std::string readShaderFromFile(const char* path);
		unsigned int load(const char* vertPath, const char* fragPath);
	private:
		unsigned int m_shaderID;
	};
}