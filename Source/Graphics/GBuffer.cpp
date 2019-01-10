#include "GBuffer.h"
#include "GLState.h"

ST_NS_BEGIN

Shader GBuffer::_shader;

GBuffer::GBuffer(int width, int height)
{
	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	// Position color buffer
	glGenTextures(1, &_positionTexture);
	glBindTexture(GL_TEXTURE_2D, _positionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _positionTexture, 0);

	// Normal color buffer
	glGenTextures(1, &_normalTexture);
	glBindTexture(GL_TEXTURE_2D, _normalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _normalTexture, 0);

	// Color + Specular color buffer
	glGenTextures(1, &_colSpecTexture);
	glBindTexture(GL_TEXTURE_2D, _colSpecTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _colSpecTexture, 0);

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cerr<<"Error creating GBuffer"<<endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (!_shader.isLoaded())
	{
		_shader = Shader(SHADER_PATH("Deferred/Quad"));
		_shader.setUniform("gPosition", 0);
		_shader.setUniform("gNormal", 1);
		_shader.setUniform("gAlbedoSpec", 2);
	}
}

GBuffer::~GBuffer()
{
	unbind();
	glDeleteFramebuffers(1, &_fbo);
}

void GBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void GBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::render()
{
	if (!_shader.isLoaded()) return;

	_shader.bind();

	GLState::setActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _positionTexture);
	GLState::setActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _normalTexture);
	GLState::setActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _colSpecTexture);

	_quad.render();

	_shader.unbind();
}

ST_NS_END
