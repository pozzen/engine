#include "Scene.h"

ST_NS_BEGIN

Scene::Scene(int width, int height):
	_renderManager(width, height)
{
	_width = width;
	_height = height;
}

Scene::~Scene()
{

}

void Scene::update(float deltaTime)
{
	_time += deltaTime;
	Component::updateAll(deltaTime);
}

void Scene::render()
{
	assert(_mainCamera);
	render(_mainCamera);
//	renderDeferred(_mainCamera);
}

void Scene::render(const Camera *camera)
{
	// Update camera
	_activeCamera = camera;
	_renderManager.getUBO().update(camera->getViewProjection(), camera->getPositionTransformed(), _time);

	// Update render manager and render
	_renderManager.update(this);
	_renderManager.render();

	// Clean up
	_activeCamera = nullptr;


//	_activeCamera = camera;
////	_ubo.update(camera->getViewProjection(), camera->getPositionAbsolute(), _time);
//	_ubo.update(camera->getViewProjection(), camera->getTransform().getPosition(), _time);

//	// Do frustum culling
////	Frustum frustum = _activeCamera->getFrustum();
////	vector<Mesh *> visibleMeshes;
////	vector<mat4> meshTransforms;
////	vector<Light *> visibleLights;

////	cull(frustum, visibleMeshes, meshTransforms, visibleLights);

////	// Separate objects from lights
////	vector<Light *> lights;
////	getLights(this, lights);

//	// Render Scene
//	// Render objects that have their own shader first (skyboxes, ...)
//	// These object will only render when passed a null ShaderRef as
//	// the shader argument.
////	Node::render(nullptr);

//	if (visibleLights.size())
//	{
//		// Render each light
//		bool firstPass = true;

//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//		for (Light *light: visibleLights)
//		{
//			light->bind();
////			Node::render(light->shader());
//			for (unsigned int i = 0; i < visibleMeshes.size(); i++)
//			{
//				Mesh *mesh = visibleMeshes[i];

//				mesh->getMaterial()->bind(light->shader());
//				mesh->render(meshTransforms[i]);
//				mesh->getMaterial()->unbind(light->shader());
//			}
//			if (firstPass)
//			{
//				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//				glDepthFunc(GL_LEQUAL);
//				firstPass = false;
//			}
//		}

//		glDepthFunc(GL_LESS);
//		glDisable(GL_BLEND);
//	}
//	else
//	{
//		// Render without lights
////		Node::render(_defaultShader);
//		for (unsigned int i = 0; i < visibleMeshes.size(); i++)
//		{
//			Mesh *mesh = visibleMeshes[i];

//			mesh->getMaterial()->bind();
//			mesh->render(meshTransforms[i]);
//			mesh->getMaterial()->unbind();
//		}
//	}

//	// Clean up
//	_activeCamera = nullptr;

//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_STENCIL_TEST);
}

void Scene::renderDeferred(const Camera *camera)
{
//	// Enable OpenGL stuff
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//	glEnable(GL_STENCIL_TEST);
//	glDepthFunc(GL_LESS);

//	// Update camera
//	_activeCamera = camera;
//	_ubo.update(camera->getViewProjection(), camera->getTransform().getPosition(), _time);
//	glViewport(0, 0, _width, _height);

//	// Bind GBuffer for writing
//	_gBuffer.bind();

//	// Render everything with the deferred shader
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

////	Node::render(_deferredShader);

//	// Unbind GBuffer and bind again for reading
//	_gBuffer.unbind();

//	// Clear buffers
//	vec3 clearColor = _clearColor.asVec3();
//	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	// Pre-pass
////	Node::render(nullptr);

//	// Render what's in the GBuffer
//	_gBuffer.render();

//	// Clean up
//	_activeCamera = nullptr;

//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_STENCIL_TEST);
}

//bool Scene::onEvent(SDL_Event *event)
//{
//	if (_mainCamera)
//	{
//		return _mainCamera->onEvent(event);
//	}
//	return false;
//}

void Scene::resized(int width, int height)
{
	_width = width;
	_height = height;
}

Color Scene::getClearColor() const
{
	return _renderManager.getClearColor();
}

void Scene::setClearColor(const Color &clearColor)
{
	_renderManager.setClearColor(clearColor);
}

Color Scene::getAmbientColor() const
{
	return _renderManager.getAmbientColor();
}

void Scene::setAmbientColor(const Color &ambientColor)
{
	_renderManager.setAmbientColor(ambientColor);
}

Camera *Scene::mainCamera() const
{
	return _mainCamera;
}

void Scene::setMainCamera(Camera *mainCamera)
{
	_mainCamera = mainCamera;
}

const Camera *Scene::_activeCamera = nullptr;

const Camera *Scene::activeCamera()
{
	return _activeCamera;
}

RenderManager &Scene::getRenderManager()
{
	return _renderManager;
}

ST_NS_END
