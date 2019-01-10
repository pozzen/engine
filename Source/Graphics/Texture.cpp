#include "Texture.h"
#include "Core/ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"

ST_NS_BEGIN

TextureRef Texture::load(const string &fileName, GLuint textureWrap)
{
	TextureRef textureRef = ResourceManager::get<Texture>(fileName);

	if (!textureRef)
	{
		Texture *texture = new Texture(fileName, textureWrap);
		textureRef = ResourceManager::add<Texture>(fileName, texture);
	}

	return textureRef;
}

Texture::Texture(const string &fileName, GLuint textureWrap, GLuint filter):
	_name(fileName)
{
	int nComponents;
	unsigned char *data = stbi_load(fileName.c_str(), &_width, &_height, &nComponents, 4);

	if (!data)
	{
		cerr<<"Texture loading failed for '"<<fileName<<"'."<<endl;
		return;
	}

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	if (filter == GL_NEAREST_MIPMAP_LINEAR || filter == GL_NEAREST_MIPMAP_LINEAR ||
		filter == GL_LINEAR_MIPMAP_NEAREST || filter == GL_LINEAR_MIPMAP_LINEAR)
	{
		glGenerateMipmap(GL_TEXTURE_2D);

		// Anisotropic filtering
		float maxAni;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAni);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, glm::min(maxAni, 4.0f));
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);

	_loaded = true;
}

Texture::~Texture()
{
	if (_loaded) glDeleteTextures(1, &_texture);
}

void Texture::bind(GLuint unit) const
{
	assert(_loaded);
	assert(unit >= 0 && unit < 32);

	GLState::setActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, _texture);
}

GLuint Texture::getTexture() const
{
	return _texture;
}

const string &Texture::getName() const
{
	return _name;
}

int Texture::getWidth() const
{
	return _width;
}

int Texture::getHeight() const
{
	return _height;
}

ST_NS_END
