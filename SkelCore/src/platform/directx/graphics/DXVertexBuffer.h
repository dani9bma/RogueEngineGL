#pragma once

#include "Context.h"

namespace Skel
{
	class DXVertexBuffer
	{
	private:
		ID3D11Buffer * m_vertexBuffer;
		D3D11_INPUT_ELEMENT_DESC* m_layout;
		Context* m_context;
		unsigned int m_stride;

	public:
		DXVertexBuffer(const void* vertices, unsigned int size, unsigned int stride, Context* context);
		~DXVertexBuffer();
		void bind();
		void unbind();
	};
}
#pragma once
