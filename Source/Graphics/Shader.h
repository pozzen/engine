#ifndef _SHADER_H_INCLUDED_
#define _SHADER_H_INCLUDED_

#include "Engine.h"
#include "Core/Transform.h"
#include "Core/Resource.h"

ST_NS_BEGIN

class ShaderProgram: public Resource
{
public:
	ShaderProgram(const string &fileName, const vector<string> &defines);
	~ShaderProgram();

	bool isLoaded();

	GLuint getProgram() const;

private:
	GLuint _program = 0;
	GLuint _shaders[3];

	int _nShaders;
	bool _loaded = false;

	string loadShader(const string& fileName, const vector<string> *defines = nullptr);
	bool checkProgramError(GLuint shader, const string& errorMessage);
	bool checkShaderError(GLuint shader, const string& errorMessage, const string &fileName = "", const string &source = "");
	bool createShader(const string &fileName, unsigned int type, GLuint &shader, const vector<string> &defines);

};

class Shader
{
public:
	Shader(const string &fileName, vector<string> defines = {});
	Shader();

	void bind();
	void unbind();
	void update(const mat4 &viewProjection, const vec3 viewPosition);
	GLuint getProgram() const;
	bool isLoaded();

	void setUniform(const string &name, float value);
	void setUniform(const string &name, int value);
	void setUniform(const string &name, bool value);
	void setUniform(const string &name, GLuint value);
	void setUniform(const string &name, vec2 value);
	void setUniform(const string &name, vec3 value);
	void setUniform(const string &name, vec4 value);
	void setUniform(const string &name, mat4 value);

private:
	Reference<ShaderProgram> _programRef = nullptr;

};

ST_NS_END

#endif // _SHADER_H_INCLUDED_
