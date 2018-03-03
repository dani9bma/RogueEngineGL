/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../utils/common.h"

namespace Skel
{
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	enum class BufferUsage
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() { }
		VertexBuffer(float data[], GLsizei size, BufferUsage usage);
		VertexBuffer(Vertex data[], GLsizei size, BufferUsage usage);
		~VertexBuffer();
		void bind();
		void unbind();
		inline unsigned int GetBuffer() const { return m_VBO; };
	private:
		unsigned int m_VBO;
		int m_componentCount; //Gets the the size of the vertex attribute
	};
}