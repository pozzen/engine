#ifndef _SCENE_H_INCLUDED_
#define _SCENE_H_INCLUDED_

#include "Engine.h"
#include "Node.h"
#include "Camera.h"
#include "Light.h"
#include "Core/RenderManager.h"
#include "Graphics/Color.h"
#include "Graphics/UniformBufferObject.h"
#include "Graphics/GBuffer.h"

ST_NS_BEGIN

class Scene: public Node, public InputHandler
{
public:
	Scene(int width, int height);
	~Scene();

	void update(float deltaTime);
	void render();
	void render(const Camera *camera);
	void renderDeferred(const Camera *camera);
//	bool onEvent(SDL_Event *event);

	void resized(int width, int height);

	Color getClearColor() const;
	void setClearColor(const Color &clearColor);

	Color getAmbientColor() const;
	void setAmbientColor(const Color &ambientColor);

	Camera *mainCamera() const;
	void setMainCamera(Camera *mainCamera);

	RenderManager &getRenderManager();

	static const Camera *activeCamera();

	NODE_TYPE(Scene)

private:
	int _width = 0;
	int _height = 0;

	double _time = 0.0;

	Camera *_mainCamera = nullptr;

	RenderManager _renderManager;

	static const Camera *_activeCamera;

};

ST_NS_END

#endif // _SCENE_H_INCLUDED_
