#include "CameraController.h"
#include "Scene/Node.h"
#include "Core/InputManager.h"

ST_NS_BEGIN

CameraController::CameraController(float lookSpeed, float movementSpeed):
	_lookSpeed(lookSpeed), _movementSpeed(movementSpeed)
{
	scheduleUpdate();
	registerInputHandler();
}

CameraController::~CameraController()
{
	unscheduleUpdate();
	unregisterInputHandler();
}

void CameraController::update(float deltaTime)
{
	vec3 direction = vec3(0.0);
	direction.z = float(_movingForward-_movingBackward);
	direction.x = float(_movingLeft-_movingRight);
	if (direction.z || direction.x) direction = normalize(direction);

	if (abs(direction.z) < 0.1 && abs(direction.x) < 0.1)
		_velocity *= 1.0-(_deceleration*deltaTime);
	else
		_velocity += direction*_acceleration;

	float speed = glm::length2(_velocity);

	if (speed > 1.0)
		_velocity = normalize(_velocity);

	if (speed > 0.0)
		_parent->getTransform().moveLocal(_velocity * _movementSpeed * deltaTime);
}

bool CameraController::mouseMoved(float x, float y, float deltaX, float deltaY)
{
	if (!_mouseDown) return false;

	static vec3 up = vec3(0.0, 1.0, 0.0);

	Transform &transform = _parent->getTransform();
	transform.setRotation(glm::normalize(glm::angleAxis(-deltaX * _lookSpeed, up))
						  * transform.getRotation());
	transform.setRotation(glm::normalize(glm::angleAxis(-deltaY * _lookSpeed, cross(transform.getFront(), up)))
						  * transform.getRotation());

	return true;
}

bool CameraController::mouseDown(Uint8 key)
{
	if (key == SDL_BUTTON_LEFT)
	{
		InputManager::setMouseCaptured(true);
		_mouseDown = true;
		return true;
	}
	return false;
}

bool CameraController::mouseUp(Uint8 key)
{
	if (key == SDL_BUTTON_LEFT)
	{
		InputManager::setMouseCaptured(false);
		_mouseDown = false;
		return true;
	}
	return false;
}

bool CameraController::keyDown(SDL_Keycode key)
{
	if (key == SDLK_w)
	{
		_movingForward = true;
		return true;
	}
	if (key == SDLK_s)
	{
		_movingBackward = true;
		return true;
	}
	if (key == SDLK_a)
	{
		_movingLeft = true;
		return true;
	}
	if (key == SDLK_d)
	{
		_movingRight = true;
		return true;
	}
	return false;
}

bool CameraController::keyUp(SDL_Keycode key)
{
	if (key == SDLK_w)
	{
		_movingForward = false;
		return true;
	}
	if (key == SDLK_s)
	{
		_movingBackward = false;
		return true;
	}
	if (key == SDLK_a)
	{
		_movingLeft = false;
		return true;
	}
	if (key == SDLK_d)
	{
		_movingRight = false;
		return true;
	}
	return false;
}

ST_NS_END
