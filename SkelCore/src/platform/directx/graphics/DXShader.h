#pragma once

#include "Context.h"

#include <d3dcompiler.h>

namespace Skel
{
	class DXShader
	{
	private:
		Context* m_context;
		ID3DBlob* m_VSBuffer;
		ID3DBlob* m_PSBuffer;
		ID3D11VertexShader* m_VS;
		ID3D11PixelShader* m_PS;
		ID3D11InputLayout* m_inputLayout;
	public:
		DXShader(Context* context);
		~DXShader();
		void setShaders(const wchar_t* vsPath, const wchar_t* psPath);
		void setInputLayout(D3D11_INPUT_ELEMENT_DESC layout[]);
	};
}
