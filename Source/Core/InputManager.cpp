#include "InputManager.h"

ST_NS_BEGIN

vector<InputHandler *> InputManager::_handlers;
bool InputManager::_mouseCaptured = false;

void InputManager::registerHandler(InputHandler *handler)
{
	_handlers.push_back(handler);
}

void InputManager::unregisterHandler(InputHandler *handler)
{
	for (vector<InputHandler *>::iterator it = _handlers.begin(); it != _handlers.end(); it++)
	{
		if (*it == handler)
		{
			_handlers.erase(it);
			return;
		}
	}
}

bool InputManager::isMouseCaptured()
{
	return _mouseCaptured;
}

void InputManager::setMouseCaptured(bool mouseCaptured)
{
	_mouseCaptured = mouseCaptured;
	SDL_SetRelativeMouseMode((SDL_bool)mouseCaptured);
}

void InputManager::dispatchEvent(SDL_Event *event)
{
	for (vector<InputHandler *>::iterator it = _handlers.begin(); it != _handlers.end(); it++)
	{
		if ((*it)->onEvent(event)) return;
	}
}

ST_NS_END
