/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "vertex_array.h"

namespace Skel { namespace graphics {

	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_VAO));
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
		GLCall(glVertexAttribPointer(index, num, GL_FLOAT, GL_FALSE, stride, offset));
		GLCall(glEnableVertexAttribArray(index));
	}

	void VertexArray::bind()
	{
		GLCall(glBindVertexArray(m_VAO));
	}

	void VertexArray::unbind()
	{
		GLCall(glBindVertexArray(0));
	}

} }