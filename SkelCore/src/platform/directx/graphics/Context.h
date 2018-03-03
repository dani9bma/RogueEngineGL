#pragma once

#include <d3d11.h>

#include "DXWindow.h"


namespace Skel
{
	class Context
	{
	private:
		IDXGISwapChain*			m_swapChain;
		ID3D11Device*			m_device;
		ID3D11DeviceContext*	m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D*		m_depthStencilBuffer;
		ID3D11DepthStencilView* m_depthStencilView;
	public:
		Context(DXWindow* window);
		~Context();
		void update();
		void draw();

		inline IDXGISwapChain* getSwapChain() const { return m_swapChain; }
		inline ID3D11Device* getDevice() const { return m_device; }
		inline ID3D11DeviceContext* getDeviceContext() const { return m_deviceContext; }
		inline ID3D11RenderTargetView* getRenderTargetView() const { return m_renderTargetView; }
		inline ID3D11DepthStencilView* getDepthStencilView() const { return m_depthStencilView; }
	};
}
