#include "DXIndexBuffer.h"

using namespace Skel;

DXIndexBuffer::DXIndexBuffer(unsigned long indices[], int size, Context* context)
	: m_context(context)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = size;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = indices;
	m_context->getDevice()->CreateBuffer(&indexBufferDesc, &iinitData, &m_indexBuffer);

	m_context->getDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

DXIndexBuffer::~DXIndexBuffer()
{

}
