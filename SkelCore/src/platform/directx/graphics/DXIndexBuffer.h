#pragma once

#include "Context.h"

namespace Skel
{
	class DXIndexBuffer
	{
	private:
		ID3D11Buffer* m_indexBuffer;
		Context* m_context;

	public:
		DXIndexBuffer(unsigned long indices[], int size, Context* context);
		~DXIndexBuffer();
		void bind();
		void unbind();
	};
}
