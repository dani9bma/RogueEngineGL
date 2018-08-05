/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <src/GL/glew.h>

#include "../Common/Common.h"

namespace Skel
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();
		void bind();
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
	};
}