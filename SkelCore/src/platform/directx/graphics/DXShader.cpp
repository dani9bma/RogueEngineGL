#include "DXShader.h"

using namespace Skel;

DXShader::DXShader(Context* context)
	:m_context(context)
{
}

DXShader::~DXShader()
{
	
}

void DXShader::setShaders(const wchar_t* vsPath, const wchar_t* psPath)
{
	//Compile Shaders from shader file
	auto hr = D3DCompileFromFile(
		vsPath,
		0,
		0,
		"main", "vs_4_0",
		0, 0,
		&m_VSBuffer,
		0);
	D3DCompileFromFile(
		psPath,
		0,
		0,
		"main", "ps_4_0",
		0, 0,
		&m_PSBuffer,
		0);
	//Create the Shader Objects
	m_context->getDevice()->CreateVertexShader(m_VSBuffer->GetBufferPointer(), m_VSBuffer->GetBufferSize(), NULL, &m_VS);
	m_context->getDevice()->CreatePixelShader(m_PSBuffer->GetBufferPointer(), m_PSBuffer->GetBufferSize(), NULL, &m_PS);

	//Set Vertex and Pixel Shaders
	m_context->getDeviceContext()->VSSetShader(m_VS, 0, 0);
	m_context->getDeviceContext()->PSSetShader(m_PS, 0, 0);
}

void DXShader::setInputLayout(D3D11_INPUT_ELEMENT_DESC layout[])
{
	UINT numElements = 2;
	//Create the Input Layout
	m_context->getDevice()->CreateInputLayout(layout, numElements, m_VSBuffer->GetBufferPointer(),
		m_VSBuffer->GetBufferSize(), &m_inputLayout);

	//Set the Input Layout
	m_context->getDeviceContext()->IASetInputLayout(m_inputLayout);
	m_context->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
