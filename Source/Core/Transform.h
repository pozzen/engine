#ifndef _TRANSFORM_H_INCLUDED_
#define _TRANSFORM_H_INCLUDED_

#include "Engine.h"
#include <glm/gtx/transform.hpp>

ST_NS_BEGIN

class Transform
{
public:
	Transform(const vec3 &position = vec3(), const vec3 &rotation = vec3(), const vec3 &scale = vec3(1.0, 1.0, 1.0)): _position(position), _rotation(rotation), _scale(scale) { }

	const mat4 &getModel() const;

	const vec3 &getPosition() const;
	void setPosition(const vec3 &position);

	const quat &getRotation() const;
	void setRotation(const quat &rotation);

	const vec3 &getScale() const;
	void setScale(const vec3 &scale);

	void rotateLocalX(float angle);
	void rotateLocalY(float angle);
	void rotateLocalZ(float angle);

	void rotate(float angle, vec3 axis);
	void rotateLocal(float angle, vec3 axis);

	void move(vec3 direction);
	void moveLocal(vec3 direction);

	void lookAtLocal(vec3 target);

	vec3 getRight() const;
	vec3 getUp() const;
	vec3 getFront() const;

private:
	vec3 _position;
	quat _rotation;
	vec3 _scale;

	mutable bool _changed = true;
	mutable mat4 _model;

};

ST_NS_END

#endif // _TRANSFORM_H_INCLUDED_
