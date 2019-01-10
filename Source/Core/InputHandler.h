#ifndef _INPUT_HANDLER_H_INCLUDED_
#define _INPUT_HANDLER_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class InputHandler
{
public:
	virtual bool onEvent(SDL_Event *event);
	virtual void registerInputHandler();
	virtual void unregisterInputHandler();

protected:
	virtual bool mouseMoved(float x, float y, float deltaX, float deltaY);
	virtual bool mouseDown(Uint8 key);
	virtual bool mouseUp(Uint8 key);
	virtual bool mouseScrolled(Sint32 delta);
	virtual bool keyDown(SDL_Keycode key);
	virtual bool keyUp(SDL_Keycode key);
	virtual void releaseAll();

};

ST_NS_END

#endif // _INPUT_HANDLER_H_INCLUDED_
