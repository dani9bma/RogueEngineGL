/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "FrameBuffer.h"

namespace Skel
{
	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &m_FBO);
		bind();
		AttachTexture();
		//AttachDepthStencil();
		CreateAndAttachRenderBuffer();
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			SK_LOG(Error, Rendering, "Frame is not complete");
		unbind();
	}

	FrameBuffer::~FrameBuffer()
	{
		unbind();
		GLCall(glDeleteFramebuffers(1, &m_FBO));
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void FrameBuffer::unbind()
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::AttachTexture()
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
	}

	void FrameBuffer::AttachDepthStencil()
	{

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_texture, 0);
	}

	void FrameBuffer::CreateAndAttachRenderBuffer()
	{
		glGenRenderbuffers(1, &m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
	}

}