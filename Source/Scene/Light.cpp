#include "Light.h"
#include "Core/RenderManager.h"

ST_NS_BEGIN

Light::Light()
{
	setCanCastShadows(true);
}

void Light::addToBatch(RenderBatch &batch)
{
	batch.addLight(this);
}

void Light::setCanCastShadows(bool canCastShadows)
{
	if (canCastShadows) _shadowMap = new ShadowMap(mat4(1.0));
	else
	{
		if (_shadowMap) delete _shadowMap;
		_shadowMap = nullptr;
	}
}

ShadowMap *Light::getShadowMap()
{
	return _shadowMap;
}

ShadowMap::ShadowMap(const mat4 &projection):
	_projection(projection)
{

}

const mat4 &ShadowMap::getProjection() const
{
	return _projection;
}

void ShadowMap::setProjection(const mat4 &projection)
{
	_projection = projection;
}

ST_NS_END
