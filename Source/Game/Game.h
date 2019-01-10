#ifndef _GAME_H_INCLUDED_
#define _GAME_H_INCLUDED_

#include "Engine.h"
#include "Window.h"
#include "Scene/Scene.h"

ST_NS_BEGIN

class Game: public Window
{
public:
	Game(string title, int width, int height, bool fullscreen = false, bool resizable = false);
	void createRoom();
	void createLights();

protected:
	void render(float deltaTime);
	void resized(int width, int height);
	bool keyDown(SDL_Keycode key);

private:
	Scene _scene;

};

ST_NS_END

#endif // _GAME_H_INCLUDED_
