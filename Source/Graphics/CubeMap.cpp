#include "CubeMap.h"
#include "Core/ResourceManager.h"
#include "ThirdParty/stb_image.h"

ST_NS_BEGIN

CubeMapRef CubeMap::load(const string &fileName, const string &suffix)
{
	CubeMapRef cubeMapRef = ResourceManager::get<CubeMap>(fileName);

	if (!cubeMapRef)
	{
		CubeMap *cubeMap = new CubeMap(fileName, suffix);
		cubeMapRef = ResourceManager::add<CubeMap>(fileName, cubeMap);
	}

	return cubeMapRef;
}

CubeMap::CubeMap(const string &fileName, const string &suffix)
{
	_name = fileName;
	_name += "right";
	_name += suffix;

	static const string sides[] = { "right", "left", "top", "bottom", "front", "back" };

	glGenTextures(1, &_texture);
	GLState::setActiveTexture(GL_TEXTURE0);

	int width, height, nComponents;

	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
	for(GLuint i = 0; i < 6; i++)
	{
		string fileNameFull = fileName + sides[i] + suffix;
		unsigned char *data = stbi_load(fileNameFull.c_str(), &width, &height, &nComponents, 4);

		if (!data)
		{
			cerr<<"Texture loading failed for '"<<fileNameFull<<"'."<<endl;
			continue;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	_loaded = true;
}

CubeMap::~CubeMap()
{
	if (_loaded) glDeleteTextures(1, &_texture);
}

void CubeMap::bind(GLuint unit) const
{
	assert(_loaded);
	assert(unit >= 0 && unit < 32);

	GLState::setActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
}

GLuint CubeMap::getTexture() const
{
	return _texture;
}

const string &CubeMap::getName() const
{
	return _name;
}

ST_NS_END
