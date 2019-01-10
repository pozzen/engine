#include "Material.h"
#include "Core/ResourceManager.h"

ST_NS_BEGIN

Material Material::_nullMaterial;

Material::Material(const string &fileName)
{
	fromXML(fileName);
}

Material::Material(const Color &diffuse, float specularIntensity, const Color &ambient):
	_diffuse(diffuse), _specularIntensity(specularIntensity), _ambient(ambient)
{
}

Material::Material(aiMaterial *material)
{
	loadTextures(material, TEXTURE_DIFFUSE);
	loadTextures(material, TEXTURE_SPECULAR);
	loadTextures(material, TEXTURE_NORMAL);
}

Material::~Material()
{
}

void Material::fromXML(const string &fileName)
{
	XMLDocument document;
	document.LoadFile(fileName.c_str());

	XMLElement *mat = document.FirstChildElement("material");

//	const char *shader = mat->Attribute("shader");
//	if (shader)
//		material.setShader(Shader::load(shader));

	XMLElement *diffuse = mat->FirstChildElement("diffuse");
	if (diffuse)
	{
		const char *path = diffuse->Attribute("texture");
		if (path)
			setDiffuseTexture(Texture::load(path));

		const char *color = diffuse->Attribute("color");
		if (color)
			setDiffuse(Color::fromHTMLNotation(color));
	}

	XMLElement *specular = mat->FirstChildElement("specular");
	if (specular)
	{
		const char *path = specular->Attribute("texture");
		if (path)
			setSpecularTexture(Texture::load(path));

		const char *intensity = specular->Attribute("intensity");
		if (intensity)
			setSpecularIntensity(atof(intensity));
	}

	XMLElement *normal = mat->FirstChildElement("normal");
	if (normal)
	{
		const char *path = normal->Attribute("texture");
		if (path)
			setNormalTexture(Texture::load(path));
	}

	XMLElement *ambient = mat->FirstChildElement("ambient");
	if (ambient)
	{
		const char *color = ambient->Attribute("color");
		if (color)
			setAmbient(Color::fromHTMLNotation(color));
	}
}

const Material &Material::null()
{
	return _nullMaterial;
}

void Material::bind(Shader *shader) const
{
	if (!shader) return;
	shader->bind();

	GLuint i = 0;

	if (_diffuseTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("material.textureDiffuse", i);
		_diffuseTexture->bind(i);
		i++;
	}
	shader->setUniform("material.hasDiffuseMap", _diffuseTexture);

	if (_specularTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("material.textureSpecular", i);
		_specularTexture->bind(i);
		i++;
	}
	shader->setUniform("material.hasSpecularMap", _specularTexture);

	if (_normalTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("material.textureNormal", i);
		_normalTexture->bind(i);
		i++;
	}
	shader->setUniform("material.hasNormalMap", _normalTexture);

	if (_bumpTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("material.textureBump", i);
		_bumpTexture->bind(i);
		i++;
	}
	shader->setUniform("material.hasBumpMap", _bumpTexture);

	shader->setUniform("material.diffuse", _diffuse.asVec3());
	shader->setUniform("material.specular", _specularIntensity);
	shader->setUniform("material.ambient", _ambient.asVec3());

	GLState::setActiveTexture(0);
}

void Material::unbind(Shader *shader) const
{
	if (!shader) return;
	shader->bind();

	GLuint i = 0;
	if (_diffuseTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("texture_diffuse", 50);
		glBindTexture(GL_TEXTURE_2D, 0);
		i++;
	}
	shader->setUniform("material.hasDiffuseMap", false);

	if (_specularTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("texture_specular", 50);
		glBindTexture(GL_TEXTURE_2D, 0);
		i++;
	}
	shader->setUniform("material.hasSpecularMap", false);

	if (_normalTexture)
	{
		GLState::setActiveTexture(GL_TEXTURE0 + i);
		shader->setUniform("texture_normal", 50);
		glBindTexture(GL_TEXTURE_2D, 0);
		i++;
	}
	shader->setUniform("material.hasNormalMap", false);
}

Color Material::getDiffuse() const
{
	return _diffuse;
}

void Material::setDiffuse(const Color &diffuse)
{
	_diffuse = diffuse;
}

float Material::getSpecularIntensity() const
{
	return _specularIntensity;
}

void Material::setSpecularIntensity(float specularIntensity)
{
	_specularIntensity = specularIntensity;
}

TextureRef Material::getDiffuseTexture() const
{
	return _diffuseTexture;
}

void Material::setDiffuseTexture(const TextureRef &diffuseTexture)
{
	_diffuseTexture = diffuseTexture;
}

TextureRef Material::getSpecularTexture() const
{
	return _specularTexture;
}

void Material::setSpecularTexture(const TextureRef &specularTexture)
{
	_specularTexture = specularTexture;
}

TextureRef Material::getNormalTexture() const
{
	return _normalTexture;
}

void Material::setNormalTexture(const TextureRef &normalTexture)
{
	_normalTexture = normalTexture;
}

TextureRef Material::getBumpTexture() const
{
	return _bumpTexture;
}

void Material::setBumpTexture(const TextureRef &bumpTexture)
{
	_bumpTexture = bumpTexture;
}

Color Material::getAmbient() const
{
	return _ambient;
}

void Material::setAmbient(const Color &ambient)
{
	_ambient = ambient;
}

bool Material::operator ==(const Material &other) const
{
	return (_diffuse == other.getDiffuse() &&
			_specularIntensity == other.getSpecularIntensity() &&
			_ambient == other.getAmbient() &&
			_diffuseTexture == other.getDiffuseTexture() &&
			_specularTexture == other.getSpecularTexture() &&
			_normalTexture == other.getNormalTexture() &&
			_bumpTexture == other.getBumpTexture());
}

bool Material::operator !=(const Material &other) const
{
	return !operator ==(other);
}

void Material::loadTextures(aiMaterial *mat, TextureType type)
{
	aiTextureType aiType;

	switch(type)
	{
	case TEXTURE_DIFFUSE: aiType = aiTextureType_DIFFUSE; break;
	case TEXTURE_SPECULAR: aiType = aiTextureType_SPECULAR; break;
	case TEXTURE_NORMAL: aiType = aiTextureType_NORMALS; break;
	}

	int nTextures = mat->GetTextureCount(aiType);

	for(GLuint i = 0; i < nTextures; i++)
	{
		aiString str;
		mat->GetTexture(aiType, i, &str);

		switch(type)
		{
		case TEXTURE_DIFFUSE: setDiffuseTexture(Texture::load(string("Assets/Textures/")+str.C_Str())); break;
		case TEXTURE_SPECULAR: setSpecularTexture(Texture::load(string("Assets/Textures/")+str.C_Str())); break;
		case TEXTURE_NORMAL: setNormalTexture(Texture::load(string("Assets/Textures/")+str.C_Str())); break;
		}
	}
}

ST_NS_END
