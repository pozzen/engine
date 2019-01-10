#ifndef _GBUFFER_H_INCLUDED_
#define _GBUFFER_H_INCLUDED_

#include "Engine.h"
#include "Shader.h"
#include "ScreenQuad.h"

ST_NS_BEGIN

class GBuffer
{
public:
	GBuffer(int width, int height);
	~GBuffer();

	void bind();
	void unbind();
	void render();

private:
	GLuint _fbo;
	GLuint _rbo;
	GLuint _positionTexture;
	GLuint _normalTexture;
	GLuint _colSpecTexture;

	ScreenQuad _quad;

	static Shader _shader;

};

ST_NS_END

#endif // _GBUFFER_H_INCLUDED_
