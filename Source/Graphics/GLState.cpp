#include "GLState.h"
#include "Texture.h"
#include "Shader.h"

ST_NS_BEGIN

GLenum GLState::_activeTexture = 0;
GLuint GLState::_activeShaderProgram = 0;

GLenum GLState::getActiveTexture()
{
	return _activeTexture;
}

void GLState::setActiveTexture(GLenum unit)
{
	if (_activeTexture == unit) return;
	_activeTexture = unit;
	glActiveTexture(unit);
}

GLuint GLState::getActiveShaderProgram()
{
	return _activeShaderProgram;
}

void GLState::setActiveShaderProgram(ShaderProgram *program)
{
	if (_activeShaderProgram && program &&
			_activeShaderProgram == program->getProgram()) return;

	_activeShaderProgram = program->getProgram();
	glUseProgram(_activeShaderProgram);
}

ST_NS_END
