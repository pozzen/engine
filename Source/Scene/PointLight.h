#ifndef _POINT_LIGHT_H_INCLUDED_
#define _POINT_LIGHT_H_INCLUDED_

#include "Engine.h"
#include "Light.h"
#include "Graphics/Color.h"

ST_NS_BEGIN

class PointLight: public Light
{
public:
	PointLight(float radius, Color diffuse);
	PointLight(float radius, Color diffuse, Color specular);

	float radius() const;
	void setRadius(float radius);

	Color diffuse() const;
	void setDiffuse(const Color &diffuse);

	Color specular() const;
	void setSpecular(const Color &specular);

	virtual void bind(bool shadows = false);
	virtual Shader &getShader() const;
	virtual Shader &getShadowShader() const;

	virtual bool isVisible(const Frustum &frustum);

	NODE_TYPE("PointLight")

private:
	float _radius;
	Color _diffuse;
	Color _specular;

	static Shader _shader;
	static Shader _shaderShadows;

};

ST_NS_END

#endif // _POINT_LIGHT_H_INCLUDED_
