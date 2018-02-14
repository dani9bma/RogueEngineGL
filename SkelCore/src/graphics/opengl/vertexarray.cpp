/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assun��o
 * @Github https://github.com/dani9bma
 */

#include "vertexarray.h"

namespace Skel { namespace graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VAO);
		bind();
	}

	VertexArray::~VertexArray()
	{
		unbind();
	}

	void VertexArray::addBuffer(int index, int num, VertexBuffer buffer, GLsizei stride, const void* offset)
	{
		bind();
		buffer.bind();
		glVertexAttribPointer(index, num, GL_FLOAT, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(index);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_VAO);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

} }