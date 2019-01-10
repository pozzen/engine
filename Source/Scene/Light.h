#ifndef _LIGHT_H_INCLUDED_
#define _LIGHT_H_INCLUDED_

#include "Engine.h"
#include "Node.h"

ST_NS_BEGIN

class RenderBatch;

class ShadowMap
{
public:
	ShadowMap(const mat4 &projection);

	const mat4 &getProjection() const;
	void setProjection(const mat4 &projection);

private:
	mat4 _projection;

};

class Light: public Node
{
public:
	virtual void bind(bool shadows = false) = 0;
	virtual Shader &getShader() const = 0;
	virtual Shader &getShadowShader() const = 0;

	virtual void addToBatch(RenderBatch &batch);

	void setCanCastShadows(bool canCastShadows);
	ShadowMap *getShadowMap();

	NODE_TYPE("Light")

protected:
	Light();

	ShadowMap *_shadowMap = nullptr;

};

ST_NS_END

#endif // _LIGHT_H_INCLUDED_
