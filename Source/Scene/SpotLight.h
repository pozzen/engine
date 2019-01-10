#ifndef _SPOT_LIGHT_H_INCLUDED_
#define _SPOT_LIGHT_H_INCLUDED_

#include "Engine.h"
#include "Light.h"
#include "Graphics/Color.h"

ST_NS_BEGIN

class SpotLight: public Light
{
public:
	SpotLight(float radius, float cutoff, Color diffuse);
	SpotLight(float radius, float cutoff, Color diffuse, Color specular);

	float radius() const;
	void setRadius(float radius);

	Color diffuse() const;
	void setDiffuse(const Color &diffuse);

	Color specular() const;
	void setSpecular(const Color &specular);

	virtual void bind(bool shadows);
	virtual Shader &getShader() const;
	virtual Shader &getShadowShader() const;

	virtual bool isVisible(const Frustum &frustum);

	NODE_TYPE("SpotLight")

private:
	float _radius;
	float _cutoff;
	Color _diffuse;
	Color _specular;

	static Shader _shader;
	static Shader _shaderShadows;

};

ST_NS_END

#endif // _SPOT_LIGHT_H_INCLUDED_
