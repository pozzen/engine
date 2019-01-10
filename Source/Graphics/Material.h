#ifndef _MATERIAL_H_INCLUDED_
#define _MATERIAL_H_INCLUDED_

#include "Engine.h"
#include "Texture.h"
#include "Shader.h"
#include "Color.h"

#include <assimp/scene.h>

ST_NS_BEGIN

class Material
{
public:
	Material(const string &fileName);
	Material(const Color &diffuse = Color::WHITE, float specularIntensity = 1.0f, const Color &ambient = Color::BLACK);
	Material(aiMaterial* material);
	~Material();

	void fromXML(const string &fileName);
	static const Material &null();

	void bind(Shader *shader) const;
	void unbind(Shader *shader) const;

	Color getDiffuse() const;
	void setDiffuse(const Color &diffuse);

	float getSpecularIntensity() const;
	void setSpecularIntensity(float specularIntensity);

	TextureRef getDiffuseTexture() const;
	void setDiffuseTexture(const TextureRef &diffuseTexture);

	TextureRef getSpecularTexture() const;
	void setSpecularTexture(const TextureRef &specularTexture);

	TextureRef getNormalTexture() const;
	void setNormalTexture(const TextureRef &normalTexture);

	TextureRef getBumpTexture() const;
	void setBumpTexture(const TextureRef &bumpTexture);

	float bumpiness() const;
	void setBumpiness(float bumpiness);

	Color getAmbient() const;
	void setAmbient(const Color &ambient);

	bool operator ==(const Material &other) const;
	bool operator !=(const Material &other) const;

private:
	Color _diffuse = Color::WHITE;
	float _specularIntensity = 1.0f;
	Color _ambient = Color::BLACK;

	TextureRef _diffuseTexture;
	TextureRef _specularTexture;
	TextureRef _normalTexture;
	TextureRef _bumpTexture;

	static Material _nullMaterial;

	void loadTextures(aiMaterial *mat, TextureType type);

};

ST_NS_END

#endif // _MATERIAL_H_INCLUDED_
