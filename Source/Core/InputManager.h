#ifndef _INPUT_MANAGER_H_INCLUDED_
#define _INPUT_MANAGER_H_INCLUDED_

#include "Engine.h"
#include "InputHandler.h"

ST_NS_BEGIN

class InputManager
{
public:
	static void registerHandler(InputHandler *handler);
	static void unregisterHandler(InputHandler *handler);

	static bool isMouseCaptured();
	static void setMouseCaptured(bool mouseCaptured);

	static void dispatchEvent(SDL_Event *event);

private:
	static vector<InputHandler *> _handlers;
	static bool _mouseCaptured;

};

ST_NS_END

#endif // _INPUT_MANAGER_H_INCLUDED_
