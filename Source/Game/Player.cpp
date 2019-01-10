#include "Player.h"
#include "Core/RenderManager.h"

ST_NS_BEGIN

Player::Player(const string &modelFileName):
	_model(modelFileName)
{
}

void Player::update(float deltaTime)
{
	vec3 position = getTransform().getPosition();

	// Apply directional force
	vec3 direction = vec3(0.0);
	direction.z = float(_movingForward-_movingBackward);
	direction.x = float(_movingLeft-_movingRight);
	if (direction.z || direction.x) direction = normalize(direction);

	vec3 xzVelocity = vec3(_velocity);
	xzVelocity.y = 0;

	if (abs(direction.z) < 0.1 && abs(direction.x) < 0.1)
		xzVelocity *= 1.0-(_deceleration*deltaTime);
	else
		xzVelocity += direction*_acceleration*deltaTime;

	float speed = glm::length2(xzVelocity);

	if (speed > 1.0)
		xzVelocity = normalize(xzVelocity);

	_velocity.x = xzVelocity.x * _movementSpeed;
	_velocity.z = xzVelocity.z * _movementSpeed;

	// Apply gravity
	if (position.y > _groundY)
	{
		_velocity += _gravity*deltaTime;
	}

	// Apply velocity
	getTransform().moveLocal(_velocity);

	// Apply collission detection
	position = getTransform().getPosition();
	if (position.y <= _groundY)
	{
		position.y = _groundY;
		getTransform().setPosition(position);
	}

//	vec3 xzVelocity = vec3(0.0);

//	if (abs(direction.z) < 0.1 && abs(direction.x) < 0.1)
//		xzVelocity *= 1.0-(_deceleration*deltaTime);
//	else
//		xzVelocity += direction*_acceleration*deltaTime;

//	float speed = glm::length2(xzVelocity);

//	if (speed > 1.0)
//		xzVelocity = normalize(xzVelocity);

//	// Apply gravity
//	if (getTransform().getPosition().y >= 0)
//	{
//		_velocity += _gravity*deltaTime;
//	}

//	if (speed > 0.0)
//		getTransform().moveLocal(_velocity * _movementSpeed);

//	Node::update(deltaTime);
}

void Player::addToBatch(RenderBatch &batch)
{
	mat4 model = getModelTransform();

	for (Mesh &mesh: _model.getMeshes())
	{
		batch.addRenderable(&mesh, model * mesh.getModelTransform(), 1);
	}
}

bool Player::keyDown(SDL_Keycode key)
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

bool Player::keyUp(SDL_Keycode key)
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

StaticModel Player::getModel()
{
	return _model;
}

void Player::setModel(const StaticModel &model)
{
	_model = model;
}

ST_NS_END
