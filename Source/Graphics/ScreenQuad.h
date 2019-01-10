#ifndef _SCREEN_QUAD_H_INCLUDED_
#define _SCREEN_QUAD_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class ScreenQuad
{
public:
	ScreenQuad();
	~ScreenQuad();

	void render();

private:
	GLuint _vao;
	GLuint _vbo;

};

ST_NS_END

#endif // _SCREEN_QUAD_H_INCLUDED_
