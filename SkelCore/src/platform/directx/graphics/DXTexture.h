#pragma once

#include "Context.h"

namespace Skel
{
	class DXTexture
	{
	private:
		Context* m_context;
		ID3D11ShaderResourceView* m_texture;
		ID3D11SamplerState* m_textureSamplerState;
	public:
		DXTexture(Context* context, const wchar_t* path);
		~DXTexture();
		void update();
	};
}