/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "shader.h"

namespace Skel { namespace graphics {


	Shader::Shader(const char* vertPath, const char* fragPath)
	{
		m_shaderID = load(vertPath, fragPath);
	}

	Shader::~Shader()
	{
		glUseProgram(0);
	}

	void Shader::enable()
	{
		glUseProgram(m_shaderID);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	std::string Shader::readShaderFromFile(const char* path)
	{
		FILE* file = fopen(path, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	unsigned int Shader::load(const char* vertPath, const char* fragPath)
	{
		std::string vertSourceString = readShaderFromFile(vertPath).c_str();
		std::string fragSourceString = readShaderFromFile(fragPath).c_str();
		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();
		int sucess;
		char infoLog[512];
		unsigned int programID;

		unsigned int vertexShader;
		GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
		GLCall(glShaderSource(vertexShader, 1, &vertSource, 0));
		GLCall(glCompileShader(vertexShader));

		GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess)); //See if the shader compiles
		if (sucess == GL_FALSE)
		{
			GLCall(glGetShaderInfoLog(vertexShader, 512, 0, infoLog));
			//#TODO Create Log Class and log this
			std::cout << "[GRAPHICS::SHADER::VERTEX] " << infoLog << std::endl;
		}

		unsigned int fragShader;
		GLCall(fragShader = glCreateShader(GL_FRAGMENT_SHADER));
		GLCall(glShaderSource(fragShader, 1, &fragSource, 0));
		GLCall(glCompileShader(fragShader));

		GLCall(glGetShaderiv(fragShader, GL_COMPILE_STATUS, &sucess)); //See if the shader compiles
		if (!sucess)
		{
			GLCall(glGetShaderInfoLog(fragShader, 512, 0, infoLog));
			//#TODO Create Log Class and log this
			std::cout << "[GRAPHICS::SHADER::FRAGMENT] " << infoLog << std::endl;
		}

		GLCall(programID = glCreateProgram());
		GLCall(glAttachShader(programID, vertexShader));
		GLCall(glAttachShader(programID, fragShader));
		GLCall(glLinkProgram(programID));
		GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &sucess));
		if (!sucess)
		{
			GLCall(glGetProgramInfoLog(fragShader, 512, 0, infoLog));
			//#TODO Create Log Class and log this
			std::cout << "[GRAPHICS::SHADER::PROGRAM] " << infoLog << std::endl;
		}
		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragShader));

		return programID;
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		GLCall(glUniform1f(getUniformLocation(name), value));
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		GLCall(glUniform1i(getUniformLocation(name), value));
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
	{
		GLCall(glUniform2f(getUniformLocation(name), vector.x, vector.y));
	}

	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
	{
		GLCall(glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z));
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
	{
		GLCall(glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
	}

	void Shader::setUniform4f(const GLchar* name, float r, float g, float b, float w)
	{
		GLCall(glUniform4f(getUniformLocation(name), r, g, b, w));
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4 matrix)
	{
		GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
	}

	int Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_shaderID, name);
	}

} }