#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Engine.h"
#include "Scene/StaticModel.h"
#include "Core/InputHandler.h"

ST_NS_BEGIN

class Player: public Node, public InputHandler
{
public:
	Player(const string &modelFileName);

	virtual void update(float deltaTime);

	virtual void addToBatch(RenderBatch &batch);

	NODE_TYPE(Player)

	StaticModel getModel();
	void setModel(const StaticModel &model);

protected:
	virtual bool keyDown(SDL_Keycode key);
	virtual bool keyUp(SDL_Keycode key);

private:
	StaticModel _model;

	float _movementSpeed = 0.8;
	float _lookSpeed = 0.008;

	float _acceleration = 10.0;
	float _deceleration = 20.0;
	vec3 _velocity = vec3(0.0);
	vec3 _gravity = vec3(0.0, -1.0, 0.0);
	float _groundY = 2;

	bool _mouseDown = false;
	bool _movingForward = false;
	bool _movingBackward = false;
	bool _movingLeft = false;
	bool _movingRight = false;
};

ST_NS_END

#endif // _PLAYER_H_INCLUDED_
