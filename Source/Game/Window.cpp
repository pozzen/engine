#include "Window.h"

ST_NS_BEGIN

Window *Window::_runningInstance = nullptr;

Window::Window(string title, int width, int height, bool fullscreen, bool resizable):
	_width(width), _height(height), _fullscreen(fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	_glContext = SDL_GL_CreateContext(_window);
	SDL_GL_SetSwapInterval(0);

	setFullscreen(fullscreen);

	glewInit();

	SDL_AddEventWatch(watchEvents, NULL);

	// Print OpenGL information
	const GLubyte *version = glGetString(GL_VERSION),
				*vendor = glGetString(GL_VENDOR),
				*renderer = glGetString(GL_RENDERER);

	cout<<"OpenGL version: "<<version<<endl
		<<"Vendor: "<<vendor<<endl
		<<"Renderer: "<<renderer<<endl<<endl;

	InputManager::registerHandler(this);
}

Window::~Window()
{
	InputManager::unregisterHandler(this);
	SDL_DelEventWatch(watchEvents, NULL);
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::fullscreen() const
{
	return _fullscreen;
}

void Window::setFullscreen(bool fullscreen)
{
	_fullscreen = fullscreen;
	SDL_SetWindowFullscreen(_window, fullscreen? SDL_WINDOW_FULLSCREEN: 0);
}

void Window::quit()
{
	_quitting = true;
}

int SDLCALL Window::watchEvents(void *userdata, SDL_Event *event)
{
	if (event->type == SDL_APP_WILLENTERBACKGROUND)
	{
		if (_runningInstance) _runningInstance->quit();
	}
	else
	{
		if (_runningInstance) InputManager::dispatchEvent(event);
	}

	return 1;
}

void Window::doIteration()
{
	if (_quitting) return;

//	SDL_GL_MakeCurrent(window, gl_context);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_quitting = true;
		}
		else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			resized(event.window.data1, event.window.data2);
		}
	}

	Uint64 now = SDL_GetPerformanceCounter();
	float deltaTime = float(now-_ticks)/SDL_GetPerformanceFrequency();

	render(_ticks? deltaTime: 0.0);

	_ticks = now;

	SDL_GL_SwapWindow(_window);
}

void Window::run()
{
	_runningInstance = this;
	while(!_quitting)
	{
		doIteration();
		SDL_Delay(2);
	}
}

ST_NS_END
