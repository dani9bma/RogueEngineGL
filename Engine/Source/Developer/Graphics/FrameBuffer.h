#pragma once

#include <src/GL/glew.h>

#include "../Common/Common.h"

namespace Skel
{
	class SKEL_API FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();
		void bind(int width, int height);
		void unbind();
		void AttachTexture();
		void AttachDepthStencil();
		void CreateAndAttachRenderBuffer(); //Probably going to change this a different file
		inline unsigned int GetBuffer() const { return m_FBO; };
		inline uint GetTexture() const { return m_texture; }
	private:
		uint m_FBO;
		uint m_RBO;
		uint m_texture;
		int m_width = 0;
		int m_height = 0;
	};
}