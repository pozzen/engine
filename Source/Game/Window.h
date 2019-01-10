#ifndef _WINDOW_H_INCLUDED_
#define _WINDOW_H_INCLUDED_

#include "Engine.h"
#include "Core/InputHandler.h"
#include "Core/InputManager.h"

ST_NS_BEGIN

class Window: public InputHandler
{
public:
	Window(string title, int width, int height,	bool fullscreen = false, bool resizable = false);
	~Window();

	bool fullscreen() const;
	void setFullscreen(bool fullscreen);
	void doIteration();
	void run();
	void quit();

protected:
	virtual void render(float deltaTime) = 0;
	virtual void resized(int width, int height) = 0;

private:
	bool _quitting = false;
	SDL_Window *_window = NULL;
	SDL_GLContext _glContext;
	int _width;
	int _height;
	bool _fullscreen;
	Uint64 _ticks = 0.0;

	static Window *_runningInstance;
	static int SDLCALL watchEvents(void *userdata, SDL_Event* event);

};

ST_NS_END

#endif // _WINDOW_H_INCLUDED_
