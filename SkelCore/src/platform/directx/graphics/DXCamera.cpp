#include "DXCamera.h"

using namespace Skel;

DXCamera::DXCamera(Context* context, DXWindow* window)
	:m_context(context)
{
	//Create the buffer to send to the cbuffer in effect file
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	m_context->getDevice()->CreateBuffer(&cbbd, NULL, &m_cbPerObjectBuffer);

	//Camera information
	camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	//Set the Projection matrix
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)window->getWidth() / window->getHeight(), 1.0f, 1000.0f);
}

DXCamera::~DXCamera()
{
	m_cbPerObjectBuffer->Release();
}

void DXCamera::update()
{
	auto World = XMMatrixIdentity();
	XMMATRIX WVP;

	//Keep the cubes rotating
	rot += 0.00005f;
	if (rot > 6.28f)
		rot = 0.0f;

	//Define cube1's world space matrix
	XMVECTOR rotaxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	Rotation = XMMatrixRotationAxis(rotaxis, rot);
	//Translation = XMMatrixTranslation(0.0f, 0.0f, 4.0f);

	//Set cube1's world space using the transformations
	auto cube1World = Rotation;

	WVP = cube1World * camView * camProjection;

	m_cbObj.WVP = XMMatrixTranspose(WVP);

	m_context->getDeviceContext()->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &m_cbObj, 0, 0);

	m_context->getDeviceContext()->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);
}
