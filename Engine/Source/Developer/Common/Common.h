/*
 * @module  Utils
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <src/GL/glew.h>
#include <iostream>
#include "../Utils/Log.h"

#define UNREF_PARAM(P)          (P)
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) Common::GLClearError();\
	x;\
	ASSERT(Common::GLLogCall(#x, __FILE__, __LINE__))

namespace Skel
{
	class SKEL_API Common
	{
	public:
		static void GLClearError()
		{
			while (glGetError() != GL_NO_ERROR);
		}

		static bool GLLogCall(const char* func, const char* file, int line)
		{
			while (GLenum error = glGetError())
			{
				SK_LOGP(Error, Rendering, "(%d)%s:%d->%s", error, file, line, func);
				return false;
			}

			return true;
		}
	};

}

