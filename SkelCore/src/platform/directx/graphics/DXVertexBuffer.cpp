#include "DXVertexBuffer.h"

using namespace Skel;

DXVertexBuffer::DXVertexBuffer(const void* vertices, unsigned int size, unsigned int stride, Context* context)
	: m_stride(stride), m_context(context)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = size;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;
	m_context->getDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);

	bind();
}

DXVertexBuffer::~DXVertexBuffer()
{
	unbind();
}

void DXVertexBuffer::bind()
{
	//Set the vertex buffer
	UINT stride = m_stride;
	UINT offset = 0;

	m_context->getDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
}

void DXVertexBuffer::unbind()
{
	m_vertexBuffer->Release();
}

