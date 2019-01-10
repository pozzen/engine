#include "InputHandler.h"
#include "InputManager.h"

ST_NS_BEGIN

bool InputHandler::onEvent(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		return mouseDown(event->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		return mouseUp(event->button.button);
		break;
	case SDL_MOUSEWHEEL:
		return mouseScrolled(event->wheel.y);
		break;
	case SDL_MOUSEMOTION:
		return mouseMoved(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
		break;
	case SDL_KEYDOWN:
		return keyDown(event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		return keyUp(event->key.keysym.sym);
		break;
	}
	return false;
}

void InputHandler::registerInputHandler()
{
	InputManager::registerHandler(this);
}

void InputHandler::unregisterInputHandler()
{
	InputManager::unregisterHandler(this);
}

bool InputHandler::mouseMoved(float x, float y, float deltaX, float deltaY)
{
	return false;
}

bool InputHandler::mouseDown(Uint8 key)
{
	return false;
}

bool InputHandler::mouseUp(Uint8 key)
{
	return false;
}

bool InputHandler::mouseScrolled(Sint32 delta)
{
	return false;
}

bool InputHandler::keyDown(SDL_Keycode key)
{
	return false;
}

bool InputHandler::keyUp(SDL_Keycode key)
{
	return false;
}

void InputHandler::releaseAll()
{
}

ST_NS_END
