#include "Context.h"
#include "../../../imgui/imgui.h"


extern bool ImGui_ImplDX11_Init(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
extern void ImGui_ImplDX11_Shutdown();
extern void ImGui_ImplDX11_NewFrame();
extern void ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data);
extern void ImGui_ImplDX11_InvalidateDeviceObjects();
extern bool ImGui_ImplDX11_CreateDeviceObjects();


using namespace Skel;

Context::Context(DXWindow* window)
{
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = 0;
	bufferDesc.Height = 0;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = window->getHandle();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

	//Create our SwapChain
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	//Create our Render Target
	m_device->CreateRenderTargetView(BackBuffer, NULL, &m_renderTargetView);
	BackBuffer->Release();

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	BackBuffer->GetDesc(&desc);
	depthStencilDesc.Width = desc.Width;
	depthStencilDesc.Height = desc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	m_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	m_device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);


	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = desc.Width;
	viewport.Height = desc.Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	m_deviceContext->RSSetViewports(1, &viewport);
}

Context::~Context()
{
	m_swapChain->Release();
	m_device->Release();
	m_deviceContext->Release();
	m_renderTargetView->Release();
	m_depthStencilBuffer->Release();
	m_depthStencilView->Release();
}

void Context::update()
{
	//Clear our backbuffer
	float bgColor[4] = { (0.0f, 0.0f, 0.0f, 0.0f) };
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//Set our Render Target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, (float*)&clear_color);


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//Refresh the Depth/Stencil view
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Context::draw()
{
	m_swapChain->Present(0, 0);
}
