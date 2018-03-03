#pragma once

#include "platform\directx\graphics\DXWindow.h"
#include "platform\directx\graphics\context.h"
#include "platform\directx\graphics\DXShader.h"

namespace Skel
{
	class DXScene
	{
	public:
		DXScene()
		{
			DXWindow* window = new DXWindow(1280, 720, "Skel Engine");
			Context* context = new Context(window);
			DXShader* shader = new DXShader(context);
			shader->SetShaders(L"src/platform/directx/shaders/basicVert.hlsl", L"src/platform/directx/shaders/basicPixel.hlsl");

			while (!window->closed())
			{
				window->update();
				context->update();
				//Render

				context->draw();
			}

		}
	};
}