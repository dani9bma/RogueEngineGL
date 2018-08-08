#pragma once

#include <src/GL/glew.h>

#include "VertexBuffer.h"
#include "../Common/Common.h"

namespace Skel
{
	class SKEL_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		/*
		* num Number of vertex attributes
		* index Index of the location on the shader
		*/
		void addBuffer(int index, int num, VertexBuffer buffer, GLsizei stride = 0, const void* offset = 0);
		void bind();
		void unbind();
		inline unsigned int getVertexArray() const { return m_VAO; };
	private:
		unsigned int m_VAO;
	};

}