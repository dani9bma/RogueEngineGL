#include "DXTexture.h"

#include <WICTextureLoader.h>
#include <DirectXMath.h>

using namespace Skel;
using namespace DirectX;

DXTexture::DXTexture(Context* context, const wchar_t* path)
	:m_context(context)
{
	auto hr = CreateWICTextureFromFile(m_context->getDevice(), path, nullptr, &m_texture);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MipLODBias = 0.0f;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//sampDesc.BorderColor[0] = 0.4f;
	//sampDesc.BorderColor[1] = 0.4f;
	//sampDesc.BorderColor[2] = 0.4f;
	//sampDesc.BorderColor[3] = 1.0f;
	sampDesc.MinLOD = -FLT_MAX;
	sampDesc.MaxLOD = FLT_MAX;


	m_context->getDevice()->CreateSamplerState(&sampDesc, &m_textureSamplerState);
}

DXTexture::~DXTexture()
{
	m_texture->Release();
	m_textureSamplerState->Release();
}

void DXTexture::update()
{
	m_context->getDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	m_context->getDeviceContext()->PSSetSamplers(0, 1, &m_textureSamplerState);
}

