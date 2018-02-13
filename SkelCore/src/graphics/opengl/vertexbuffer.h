/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */
#pragma once

#include <GL/glew.h>

namespace Skel { namespace graphics {

	enum class BufferUsage
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(float data[], GLsizei size, BufferUsage usage);
		~VertexBuffer();
		void bind();
		void unbind();
		inline unsigned int GetBuffer() const { return m_VBO; };
	private:
		unsigned int m_VBO;
		int m_componentCount; //Gets the the size of the vertex attribute
	};

} }