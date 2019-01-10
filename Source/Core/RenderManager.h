#ifndef _RENDER_MANAGER_H_INCLUDED_
#define _RENDER_MANAGER_H_INCLUDED_

#include "Engine.h"
#include "Graphics/Mesh.h"
#include "Scene/Light.h"
#include "Graphics/UniformBufferObject.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/ScreenQuad.h"
#include "Scene/Camera.h"

ST_NS_BEGIN

class RenderBatch
{
public:
	inline void addRenderable(Renderable *renderable, const mat4 &transform, int pass)
	{
		_renderables.push_back(renderable);
		_transforms.push_back(transform);

		assert(pass < 3 && pass >= 0);
		_passes[pass].push_back(_renderables.size() - 1);
	}

	inline void addLight(Light *light)
	{
		_lights.push_back(light);
	}

	vector<Renderable *> _renderables;
	vector<mat4> _transforms;
	vector<Light *> _lights;

	vector<int> _passes[3];

};

class RenderManager
{
public:
	RenderManager(int width, int height);

	UniformBufferObject &getUBO();

	void update(Node *node);
	void renderPass(RenderBatch &batch, int pass, Shader &shader);
	void renderLights(RenderBatch &batch, int pass);
	void render();

	Color getClearColor() const;
	void setClearColor(const Color &clearColor);

	Color getAmbientColor() const;
	void setAmbientColor(const Color &ambientColor);

	bool getFXAA() const;
	void setFXAA(bool fxaa);

	int getMSAA() const;
	void setMSAA(int msaa);

private:
	Shader _defaultShader;
	Color _clearColor = Color::BLACK;
	Color _ambientColor = Color(0.2, 0.2, 0.2);
	UniformBufferObject _ubo;

	RenderBatch _batch;

	int _width;
	int _height;

	Shader _fxaaShader;
	Shader _screenShader;
	bool _fxaa = false;
	int _msaa = 0;
	FrameBuffer *_fbo = nullptr;
	ScreenQuad _fsQuad;

	FrameBuffer _shadowFBO;
	Camera _shadowCamera;
	Shader _shadowShader;

//	Shader _deferredShader;
//	GBuffer _gBuffer;

};

ST_NS_END

#endif // _RENDER_MANAGER_H_INCLUDED_
