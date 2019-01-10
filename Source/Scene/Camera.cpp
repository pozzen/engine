#include "Camera.h"

ST_NS_BEGIN

Camera::Camera()
{
}

Camera::Camera(float fov, float aspect, float zNear, float zFar):
	_aspectRatio(aspect), _fov(fov), _zNear(zNear), _zFar(zFar)
{
	_projection = perspective(radians(fov), aspect, zNear, zFar);
}

Camera::~Camera()
{

}

mat4 Camera::getViewProjection() const
{
	return _projection * getView();
}

mat4 Camera::getView() const
{
	vec3 position = getPositionTransformed();
	quat rotation = getRotationTransformed();

	return glm::lookAt(position, position+normalize(glm::rotate(rotation, vec3(0.0, 0.0, 1.0))), _up);
}

Frustum Camera::getFrustum() const
{

}

mat4 Camera::getProjection() const
{
	return _projection;
}

void Camera::setProjection(const mat4 &projection)
{
	_projection = projection;
}

ST_NS_END
