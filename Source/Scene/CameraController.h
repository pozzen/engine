#ifndef _CAMERA_CONTROLLER_H_INCLUDED_
#define _CAMERA_CONTROLLER_H_INCLUDED_

#include "Engine.h"
#include "Core/InputHandler.h"
#include "Scene/Component.h"

ST_NS_BEGIN

class CameraController: public Component, public InputHandler
{
public:
	CameraController(float lookSpeed = 0.008, float movementSpeed = 150.0);
	~CameraController();

	virtual void update(float deltaTime);

protected:
	virtual bool mouseMoved(float x, float y, float deltaX, float deltaY);
	virtual bool mouseDown(Uint8 key);
	virtual bool mouseUp(Uint8 key);
	virtual bool keyDown(SDL_Keycode key);
	virtual bool keyUp(SDL_Keycode key);

	float _movementSpeed = 150;
	float _lookSpeed = 0.008;

	float _acceleration = 10.0;
	float _deceleration = 20.0;
	vec3 _velocity = vec3(0.0);

	bool _mouseDown = false;
	bool _movingForward = false;
	bool _movingBackward = false;
	bool _movingLeft = false;
	bool _movingRight = false;

};

ST_NS_END

#endif // _CAMERA_CONTROLLER_H_INCLUDED_
