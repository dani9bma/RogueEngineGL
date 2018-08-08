#pragma once

#include <src/GL/glew.h>

#include "../Common/Common.h"

namespace Skel
{
	class SKEL_API IndexBuffer
	{
	public:
		IndexBuffer() {}
		IndexBuffer(unsigned int data[], int count);
		~IndexBuffer();
		void bind();
		void unbind();
		void draw();
		inline unsigned int GetBuffer() const { return m_EBO; };
	private:
		unsigned int m_EBO;
		int m_count;
	};
}