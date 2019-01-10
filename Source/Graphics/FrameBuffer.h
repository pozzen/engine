#ifndef _FRAMEBUFFER_H_INCLUDED_
#define _FRAMEBUFFER_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class FrameBuffer
{
public:
	FrameBuffer(int width, int height, int samples = 0, bool shadowMap = false);
	~FrameBuffer();

	void bind();
	void unbind();
	void bindTexture(GLuint unit);
	void unbindTexture(GLuint unit);

private:
	GLuint _fbo;
	GLuint _rbo;
	GLuint _ibo;
	GLuint _fboTexture;
	GLuint _iboTexture;
	int _samples;
	uint _width;
	uint _height;

	void init();
	void initMSAA();
	void initShadowMap();

};

ST_NS_END

#endif // _FRAMEBUFFER_H_INCLUDED_
