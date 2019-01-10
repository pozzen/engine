#ifndef _GLSTATE_H_INCLUDED_
#define _GLSTATE_H_INCLUDED_

#include "Engine.h"
#include "Core/Resource.h"

ST_NS_BEGIN

class ShaderProgram;

class GLState
{
public:
	static GLenum getActiveTexture();
	static void setActiveTexture(GLenum unit);

	static GLuint getActiveShaderProgram();
	static void setActiveShaderProgram(ShaderProgram *program);

private:
	static GLenum _activeTexture;
	static GLuint _activeShaderProgram;

};

ST_NS_END

#endif // _GLSTATE_H_INCLUDED_
