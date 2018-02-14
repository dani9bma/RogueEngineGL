/*
 * @module Common
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* func, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		//#TODO Create Log Class and log this
		std::cout << "[OPENGL::ERROR] (" << error << ")" << file << ":" << line << "->" << func << std::endl;
		return false;
	}

	return true;
}