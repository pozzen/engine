#ifndef _DIRECTIONAL_LIGHT_H_INCLUDED_
#define _DIRECTIONAL_LIGHT_H_INCLUDED_

#include "Engine.h"
#include "Light.h"
#include "Graphics/Color.h"

ST_NS_BEGIN

class DirectionalLight: public Light
{
public:
	DirectionalLight(Color diffuse);
	DirectionalLight(Color diffuse, Color specular);

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
	Color _diffuse;
	Color _specular;

	static Shader _shader;
	static Shader _shaderShadows;

};

ST_NS_END

#endif // _DIRECTIONAL_LIGHT_H_INCLUDED_
