/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/

#include "DXWindow.h"
#include "../../../utils/log.h"


using namespace Skel;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(handle, msg, wparam, lparam))
		return true;

	switch (msg)
	{
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE) {
			DestroyWindow(handle);
		}	
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(handle, msg, wparam, lparam);
}

DXWindow::DXWindow(int width, int height, const char* title)
	:m_width(width), m_height(height), m_title(title)
{
	//Define window style
	WNDCLASS wc = { 0 };
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WinProc;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = "DX11WindowClass";
	RegisterClass(&wc);

	m_window = CreateWindow("DX11WindowClass", title,
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		width / 2, height / 2, width, height,
		nullptr, nullptr, nullptr, nullptr);

	ShowWindow(m_window, SW_SHOWDEFAULT);
	UpdateWindow(m_window);
}

DXWindow::~DXWindow()
{
	UnregisterClass("DX11WindowClass", nullptr);
}

void DXWindow::update()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message != WM_QUIT)
		m_closed = false;
	else
		m_closed = true;
}

bool Skel::DXWindow::closed()
{
	return m_closed;
}

void Skel::DXWindow::close()
{
	m_closed = true;
}

