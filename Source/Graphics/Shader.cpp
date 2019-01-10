#include <fstream>
#include <cstdio>
#include <sstream>
#include "Shader.h"
#include "GLState.h"
#include "Core/ResourceManager.h"

ST_NS_BEGIN

Shader::Shader(const string &shaderName, vector<string> defines)
{
	string uid = "shader:";
	uid += shaderName;
	for (uint i = 0; i < defines.size(); i++)
	{
		uid += "#";
		uid += defines[i];
	}

	_programRef = ResourceManager::get<ShaderProgram>(uid);

	if (!_programRef)
	{
		ShaderProgram *program = new ShaderProgram(shaderName, defines);
		_programRef = ResourceManager::add<ShaderProgram>(uid, program);
	}
}

Shader::Shader()
{
}

void Shader::bind()
{
	assert(_programRef);
	assert(_programRef->isLoaded());

	GLState::setActiveShaderProgram(&(*_programRef));
}

void Shader::unbind()
{
	GLState::setActiveShaderProgram(nullptr);
}

GLuint Shader::getProgram() const
{
	return _programRef? _programRef->getProgram(): 0;
}

bool Shader::isLoaded()
{
	return _programRef && _programRef->isLoaded();
}

void Shader::setUniform(const string &name, float value)
{
	bind();

	glUniform1f(glGetUniformLocation(_programRef->getProgram(), name.c_str()), value);
}

void Shader::setUniform(const string &name, int value)
{
	bind();

	glUniform1i(glGetUniformLocation(_programRef->getProgram(), name.c_str()), value);
}

void Shader::setUniform(const string &name, bool value)
{
	bind();

	glUniform1i(glGetUniformLocation(_programRef->getProgram(), name.c_str()), value);
}

void Shader::setUniform(const string &name, GLuint value)
{
	bind();

	glUniform1i(glGetUniformLocation(_programRef->getProgram(), name.c_str()), value);
}

void Shader::setUniform(const string &name, glm::vec2 value)
{
	bind();

	glUniform2fv(glGetUniformLocation(_programRef->getProgram(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniform(const string &name, vec3 value)
{
	bind();

	glUniform3fv(glGetUniformLocation(_programRef->getProgram(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniform(const string &name, vec4 value)
{
	bind();

	glUniform4fv(glGetUniformLocation(_programRef->getProgram(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniform(const string &name, mat4 value)
{
	bind();

	glUniformMatrix4fv(glGetUniformLocation(_programRef->getProgram(), name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgram::ShaderProgram(const string &shaderName, const vector<string> &defines)
{
	_program = glCreateProgram();

	vector<string> vsDefines = defines;
	vector<string> fsDefines = defines;
	vsDefines.push_back("VS");
	fsDefines.push_back("FS");

	if (!createShader(shaderName + ".vs", GL_VERTEX_SHADER, _shaders[0], vsDefines)) return;
	if (!createShader(shaderName + ".fs", GL_FRAGMENT_SHADER, _shaders[1], fsDefines)) return;

//	// Check for geometry shader before compiling
//	string geomShaderSrc = loadShader(fileName + ".gs");
//	if (geomShaderSrc.length())
//	{
//		_shaders[2] = createShader(geomShaderSrc, GL_GEOMETRY_SHADER);
//		_nShaders = 3;
//	}
//	else

	_nShaders = 2;

	for(unsigned int i = 0; i < _nShaders; i++)
		glAttachShader(_program, _shaders[i]);

	glLinkProgram(_program);
	if (!checkProgramError(_program, "Error linking shader program")) return;

	glValidateProgram(_program);
	if (!checkProgramError(_program, "Invalid shader program")) return;

	GLuint ubiVP = glGetUniformBlockIndex(_program, "matrices");
	glUniformBlockBinding(_program, ubiVP, 0);

	_loaded = true;
}

ShaderProgram::~ShaderProgram()
{
	if (!_loaded) return;

	for (int i = 0; i < _nShaders; i++)
	{
		glDetachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glDeleteProgram(_program);
}

string ShaderProgram::loadShader(const string& fileName, const vector<string> *defines)
{
	std::ifstream file;
	file.open((fileName).c_str());

	string result;
	string line;

	if(file.is_open())
	{
		int headerLinesSkipped = 0;
		int curLine = 0;

		while(file.good())
		{
			getline(file, line);
			if (line.find("#include") == 0)
			{
				string fullPath;
				if (size_type separator = fileName.find_last_of("/"))
				{
					fullPath += fileName.substr(0, separator+1);
				}
				fullPath += line.substr(10, line.size()-11);
				result.append(loadShader(fullPath));
			}
			else
			{
				if(line.find("#version") == 0 || line.find("precision") == 0)
				{
					headerLinesSkipped++;
				}

				result.append(line + "\n");
				curLine++;

				if (headerLinesSkipped == 2 && curLine < 3)
				{
					for (int i = 0; i < defines->size(); i++)
					{
						result.append("#define ");
						result.append((*defines)[i]);
						result.append("\n");
					}
					curLine = 3;
				}
			}
		}
		file.close();
	}
	else
	{
		cerr<<"Error: Could not open shader file: "<<fileName<<endl;
	}

	return result;
}

bool ShaderProgram::checkProgramError(GLuint shader, const string &errorMessage)
{
	// TODO: check error message size
	GLint success = 0;
	GLchar error[1024];

	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if(success == GL_FALSE)
	{
		glGetProgramInfoLog(shader, sizeof(error), NULL, error);

		cerr<<errorMessage<<":\n"<<error<<endl;

		return false;
	}

	return true;
}

bool ShaderProgram::checkShaderError(GLuint shader, const string &errorMessage, const string &fileName, const string &source)
{
	GLint success = 0;
	GLchar error[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(success == GL_FALSE)
	{
		glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr<<errorMessage<<":"<<endl;
		cerr<<"  "<<fileName<<endl;

		if (source.size() > 0)
		{
			int a;
			int errorLine;
			if (std::sscanf(error, "%d:%d", &a, &errorLine) != 2) return false;

			std::stringstream ss(source);
			string line;
			int curLine = 1;
			while (std::getline(ss, line))
			{
				if (curLine == errorLine)
				{
					cerr<<" > |"<<line<<endl;
				}
				else if (curLine >= errorLine-2)
				{
					cerr<<"   |"<<line<<endl;
				}
				if (curLine > errorLine+2) break;
				curLine++;
			}
		}

		cout<<error<<endl;

		return false;
	}

	return true;
}

bool ShaderProgram::createShader(const string &fileName, unsigned int type, GLuint &shader, const vector<string> &defines)
{
	shader = glCreateShader(type);

	if(shader == 0)
	{
		cerr<<"Error creating shader type "<<type<<endl;
		return 0;
	}

	const string source = loadShader(fileName, &defines);
	const GLchar *s = source.c_str();
	GLint length = source.length();

	glShaderSource(shader, 1, &s, &length);
	glCompileShader(shader);

	if (!checkShaderError(shader, "Error compiling shader", fileName, source)) return false;

	return true;
}

bool ShaderProgram::isLoaded()
{
	return _loaded;
}

GLuint ShaderProgram::getProgram() const
{
	return _program;
}

ST_NS_END
