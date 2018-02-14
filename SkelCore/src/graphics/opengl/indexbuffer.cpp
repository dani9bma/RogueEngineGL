/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "indexbuffer.h"

namespace Skel { namespace graphics {


	IndexBuffer::IndexBuffer(unsigned int data[], int count)
		: m_count(count)
	{
		GLCall(glGenBuffers(1, &m_EBO));
		bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		unbind();
	}

	void IndexBuffer::draw()
	{
		GLCall(glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, 0));
	}

	void IndexBuffer::bind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
	}

	void IndexBuffer::unbind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

} }