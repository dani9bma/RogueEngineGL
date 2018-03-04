#pragma once

#include "Context.h"

#include <DirectXMath.h>

using namespace DirectX;

namespace Skel
{
	//Create constant buffer's structure//
	struct cbObject
	{
		XMMATRIX  WVP;
	};


	class DXCamera
	{
	private:
		float rot;
		XMMATRIX Rotation;
		cbObject m_cbObj;
		ID3D11Buffer * m_cbPerObjectBuffer;
		XMVECTOR camPosition, camTarget, camUp;
		XMMATRIX camView, camProjection;
		Context* m_context;
	public:
		DXCamera(Context* context, DXWindow* window);
		~DXCamera();
		void update();
	};
}