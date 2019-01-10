#ifndef _CAMERA_H_INCLUDED_
#define _CAMERA_H_INCLUDED_

#include "Common.h"
#include "Node.h"
#include "Core/InputHandler.h"
#include "Core/Frustum.h"

ST_NS_BEGIN

class Camera: public Node
{
public:
	Camera();
	Camera(float fov, float aspect, float zNear, float zFar);
	~Camera();

	virtual mat4 getViewProjection() const;
	virtual mat4 getView() const;
	virtual Frustum getFrustum() const;

	mat4 getProjection() const;
	void setProjection(const mat4 &projection);

	NODE_TYPE(Camera)

protected:
	vec3 _up = vec3(0.0, 1.0, 0.0);
	mat4 _projection;

	float _aspectRatio;
	float _fov;
	float _zNear;
	float _zFar;

};

ST_NS_END

#endif // _CAMERA_H_INCLUDED_
