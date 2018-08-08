#include "VertexBuffer.h"

namespace Skel
{
	VertexBuffer::VertexBuffer(float data[], GLsizei size, BufferUsage usage)
	{
		GLCall(glGenBuffers(1, &m_VBO));
		bind();
		if (usage == BufferUsage::DYNAMIC)
		{
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		}
		else
		{
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}
	}

	VertexBuffer::VertexBuffer(Vertices data[], GLsizei size, BufferUsage usage)
	{
		GLCall(glGenBuffers(1, &m_VBO));
		bind();
		if (usage == BufferUsage::DYNAMIC)
		{
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		}
		else
		{
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}
	}

	VertexBuffer::~VertexBuffer()
	{
		unbind();
	}

	void VertexBuffer::bind()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	}

	void VertexBuffer::unbind()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}