/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "vertexbuffer.h"

namespace Skel { namespace graphics {

	VertexBuffer::VertexBuffer(float data[], GLsizei size, BufferUsage usage)
	{
		glGenBuffers(1, &m_VBO);
		bind();
		if (usage == BufferUsage::DYNAMIC)
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		else
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		unbind();
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} }