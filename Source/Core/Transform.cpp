#include "Transform.h"

ST_NS_BEGIN

const mat4 &Transform::getModel() const
{
	if (_changed)
	{
		mat4 positionMatrix = glm::translate(_position);
		mat4 rotationMatrix = glm::mat4_cast(_rotation);
		mat4 scaleMatrix = glm::scale(_scale);

		_model = positionMatrix * rotationMatrix * scaleMatrix;

		_changed = false;
	}

	return _model;
}

const vec3 &Transform::getPosition() const
{
	return _position;
}

void Transform::setPosition(const vec3 &position)
{
	_position = position;
	_changed = true;
}

const quat &Transform::getRotation() const
{
	return _rotation;
}

void Transform::setRotation(const quat &rotation)
{
	_rotation = rotation;
	_changed = true;
}

const vec3 &Transform::getScale() const
{
	return _scale;
}

void Transform::setScale(const vec3 &scale)
{
	_scale = scale;
	_changed = true;
}

void Transform::rotateLocalX(float angle)
{
	setRotation(glm::rotate(_rotation, angle, getRight()));
}

void Transform::rotateLocalY(float angle)
{
	setRotation(glm::rotate(_rotation, angle, getUp()));
}

void Transform::rotateLocalZ(float angle)
{
	setRotation(glm::rotate(_rotation, angle, getFront()));
}

void Transform::rotate(float angle, vec3 axis)
{
	setRotation(glm::rotate(_rotation, angle, axis));
}

void Transform::rotateLocal(float angle, vec3 axis)
{
	setRotation(glm::rotate(_rotation, angle, glm::rotate(_rotation, axis)));
}

void Transform::move(vec3 direction)
{
	_position += direction;
	_changed = true;
}

void Transform::moveLocal(vec3 direction)
{
	_position += glm::rotate(_rotation, direction);
	_changed = true;
}

void Transform::lookAtLocal(vec3 target)
{
	// TODO
}

vec3 Transform::getRight() const
{
	return glm::rotate(_rotation, vec3(1.0, 0.0, 0.0));
}

vec3 Transform::getUp() const
{
	return glm::rotate(_rotation, vec3(0.0, 1.0, 0.0));
}

vec3 Transform::getFront() const
{
	return glm::rotate(_rotation, vec3(0.0, 0.0, 1.0));
}

ST_NS_END
