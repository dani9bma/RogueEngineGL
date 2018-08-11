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
Common::GLLogCall(#x, __FILE__, __LINE__)

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
                SKString errorString;
                
                switch(error)
                {
                    case GL_INVALID_ENUM:
                    errorString = "Invalid Enum";
                    break;
                    case GL_INVALID_VALUE:
                    errorString = "Invalid Value";
                    break;
                    case GL_INVALID_OPERATION:
                    errorString = "Invalid Operation";
                    break;
                    case GL_STACK_OVERFLOW:
                    errorString = "Operation cannot be done because it would overflow the limit of the stack size";
                    break;
                    case GL_STACK_UNDERFLOW:
                    errorString = "Stack is already at the lowest point";
                    break;
                    case GL_OUT_OF_MEMORY:
                    errorString = "The memory for that operation could not be allocated";
                    break;
                    case GL_INVALID_FRAMEBUFFER_OPERATION:
                    errorString = "Failed to read/write a framebuffer that is not complete";
                    break;
                    case GL_CONTEXT_LOST:
                    errorString = "OpenGL context has been lost, due to graphics card reset";
                    break;
                }
                
                
                SK_LOGP(Error, Rendering, "(%s)%s:%d->%s", errorString.c_str(), file, line, func);
				return false;
			}
            
			return true;
		}
	};
    
}

