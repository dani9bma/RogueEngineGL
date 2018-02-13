/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include <GL/glew.h>
#include "vertexbuffer.h"

namespace Skel { namespace graphics {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		/*
		 * num Number of vertex attributes
		 * index Index of the location on the shader
		 */
		void addBuffer(int index, int num, VertexBuffer buffer);
		void bind();
		void unbind();
		inline unsigned int getVertexArray() const { return m_VAO; };
	private:
		unsigned int m_VAO;
	};

} }