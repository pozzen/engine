#include "PointLight.h"

ST_NS_BEGIN

Shader PointLight::_shader;
Shader PointLight::_shaderShadows;

PointLight::PointLight(float radius, Color diffuse):
	_radius(radius), _diffuse(diffuse), _specular(diffuse)
{
	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialPointLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialPointLight"), {"SHADOWS"});
}

PointLight::PointLight(float radius, Color diffuse, Color specular):
	_radius(radius), _diffuse(diffuse), _specular(specular)
{
	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialPointLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialPointLight"), {"SHADOWS"});
}

void PointLight::bind(bool shadows)
{
	Shader *shader = &_shader;
	if (shadows) shader = &_shaderShadows;

	shader->bind();
	shader->setUniform("light.diffuse", _diffuse.asVec3());
	shader->setUniform("light.specular", _specular.asVec3());
	shader->setUniform("light.position", getPositionTransformed());
	shader->setUniform("light.radius", _radius);
}

float PointLight::radius() const
{
	return _radius;
}

void PointLight::setRadius(float radius)
{
	_radius = radius;
}

Color PointLight::diffuse() const
{
	return _diffuse;
}

void PointLight::setDiffuse(const Color &diffuse)
{
	_diffuse = diffuse;
}

Color PointLight::specular() const
{
	return _specular;
}

void PointLight::setSpecular(const Color &specular)
{
	_specular = specular;
}

Shader &PointLight::getShader() const
{
	return _shader;
}

Shader &PointLight::getShadowShader() const
{
	return _shaderShadows;
}

bool PointLight::isVisible(const Frustum &frustum)
{
	// TODO
	return true;
}

ST_NS_END
