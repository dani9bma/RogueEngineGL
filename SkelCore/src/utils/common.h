/*
 * @module  Utils
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <GL/glew.h>
#include <iostream>
#include "log.h"

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
		LOG_ERROR("OPENGL::ERROR", "(%d)%s:%d->%s", error, file, line, func);
		return false;
	}

	return true;
}