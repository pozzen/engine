#include "DirectionalLight.h"

ST_NS_BEGIN

Shader DirectionalLight::_shader;
Shader DirectionalLight::_shaderShadows;

DirectionalLight::DirectionalLight(Color diffuse):
	_diffuse(diffuse), _specular(diffuse)
{
	_shadowMap->setProjection(glm::ortho(-400.0, 400.0, -400.0, 400.0, 1.0, 500.0));

	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialDirectionalLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialDirectionalLight"), {"SHADOWS"});
}

DirectionalLight::DirectionalLight(Color diffuse, Color specular):
	_diffuse(diffuse), _specular(specular)
{
	_shadowMap->setProjection(glm::ortho(-400.0, 400.0, -400.0, 400.0, 1.0, 500.0));

	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/MaterialDirectionalLight"));
	if (!_shaderShadows.isLoaded()) _shaderShadows = Shader(SHADER_PATH("Forward/MaterialDirectionalLight"), {"SHADOWS"});
}

void DirectionalLight::bind(bool shadows)
{
	vec3 rotation = normalize(glm::rotate(getRotationTransformed(), vec3(0.0, 0.0, 1.0)));

	Shader *shader = &_shader;
	if (shadows) shader = &_shaderShadows;

	shader->bind();
	shader->setUniform("light.diffuse", _diffuse.asVec3());
	shader->setUniform("light.specular", _specular.asVec3());
	shader->setUniform("light.direction", rotation);
}

Color DirectionalLight::diffuse() const
{
	return _diffuse;
}

void DirectionalLight::setDiffuse(const Color &diffuse)
{
	_diffuse = diffuse;
}

Color DirectionalLight::specular() const
{
	return _specular;
}

void DirectionalLight::setSpecular(const Color &specular)
{
	_specular = specular;
}

Shader &DirectionalLight::getShader() const
{
	return _shader;
}

Shader &DirectionalLight::getShadowShader() const
{
	return _shaderShadows;
}

bool DirectionalLight::isVisible(const Frustum &frustum)
{
	// TODO
	return true;
}

ST_NS_END
