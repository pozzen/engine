#include "SpotLight.h"

ST_NS_BEGIN

Shader SpotLight::_shader;
Shader SpotLight::_shaderShadows;

SpotLight::SpotLight(float radius, float cutoff, Color diffuse):
	_radius(radius), _cutoff(cutoff), _diffuse(diffuse), _specular(diffuse)
{
	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialSpotLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialSpotLight"), {"SHADOWS"});
}

SpotLight::SpotLight(float radius, float cutoff, Color diffuse, Color specular):
	_radius(radius), _cutoff(cutoff), _diffuse(diffuse), _specular(specular)
{
	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialSpotLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialSpotLight"), {"SHADOWS"});
}

void SpotLight::bind(bool shadows = false)
{
	Shader *shader = &_shader;
	if (shadows) shader = &_shaderShadows;

	shader->bind();
	shader->setUniform("light.diffuse", _diffuse.asVec3());
	shader->setUniform("light.specular", _specular.asVec3());
	shader->setUniform("light.position", getPositionTransformed());
	shader->setUniform("light.direction", glm::rotate(getRotationTransformed(), vec3(0.0, 0.0, 1.0)));
	shader->setUniform("light.radius", _radius);
	shader->setUniform("light.cutoff", _cutoff);
}

float SpotLight::radius() const
{
	return _radius;
}

void SpotLight::setRadius(float radius)
{
	_radius = radius;
}

Color SpotLight::diffuse() const
{
	return _diffuse;
}

void SpotLight::setDiffuse(const Color &diffuse)
{
	_diffuse = diffuse;
}

Color SpotLight::specular() const
{
	return _specular;
}

void SpotLight::setSpecular(const Color &specular)
{
	_specular = specular;
}

Shader &SpotLight::getShader() const
{
	return _shader;
}

Shader &SpotLight::getShadowShader() const
{
	return _shaderShadows;
}

bool SpotLight::isVisible(const Frustum &frustum)
{
	// TODO
	return true;
}

ST_NS_END
