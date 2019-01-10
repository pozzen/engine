#include "RenderManager.h"
#include "Scene/Scene.h"

ST_NS_BEGIN

RenderManager::RenderManager(int width, int height):
	_width(width), _height(height), _shadowFBO(1024, 1024, 0, true)
{
	_defaultShader = Shader(SHADER_PATH("Forward/MaterialAmbient"));
//	_deferredShader = Shader(DEFERRED_MATERIAL_SHADER);

	_fbo = new FrameBuffer(width, height, _msaa);
	_fxaaShader = Shader(SHADER_PATH("Filters/FXAA"));
	_screenShader = Shader(SHADER_PATH("Filters/Basic"));

	_shadowShader = Shader(SHADER_PATH("Forward/ShadowMap"));
}

void RenderManager::update(Node *node)
{
	_batch = RenderBatch();
	node->addToBatch(_batch);
}

void RenderManager::renderPass(RenderBatch &batch, int pass, Shader &shader)
{
	for (int i: batch._passes[pass])
	{
		shader.setUniform("model", batch._transforms[i]);
		Renderable *r = batch._renderables[i];
		r->getMaterial().bind(&shader);
		r->render();
	}
}

void RenderManager::renderLights(RenderBatch &batch, int pass)
{
	// Blend in lighting
	for (Light *light: batch._lights)
	{
		Shader *shader = &light->getShader();
		ShadowMap *shadow = light->getShadowMap();

		if (shadow)
		{
			_shadowFBO.bind();

			glViewport(0, 0, 1024, 1024);

			glClear(GL_DEPTH_BUFFER_BIT);

			_shadowCamera.setProjection(shadow->getProjection());
			_shadowCamera.getTransform().setPosition(light->getRotationTransformed() * vec3(0.0, 0.0, -200.0));
			_shadowCamera.getTransform().setRotation(light->getRotationTransformed());
			mat4 shadowViewProjection = _shadowCamera.getViewProjection();
			_shadowShader.setUniform("shadowViewProjection", shadowViewProjection);

			renderPass(batch, pass, _shadowShader);

			_shadowFBO.unbind();

			glViewport(0, 0, _width, _height);

			_shadowFBO.bindTexture(7);
			shader = &light->getShadowShader();
			shader->setUniform("shadowMap", 7);
			shader->setUniform("shadowViewProjection", shadowViewProjection);
		}

		//TODO: attach rockets to objects

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthFunc(GL_LEQUAL);

		light->bind(shadow != nullptr);
		renderPass(batch, pass, *shader);

		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
	}
}

void RenderManager::render()
{
	// Anti aliasing set up
	if (_fxaa || _msaa)
	{
		_fbo->bind();
	}

	// Enable OpenGL stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);

	glViewport(0, 0, _width, _height);

	// Clear buffers
	vec3 clearColor = _clearColor.asVec3();
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Render
	_defaultShader.setUniform("ambient", _ambientColor.asVec3());
	renderPass(_batch, 0, _defaultShader);
	renderPass(_batch, 1, _defaultShader);
	renderLights(_batch, 1);
	renderPass(_batch, 2, _defaultShader);
//	for (int i = 0; i < 3; i++)
//	{
//		renderPass(i);
//	}

	// Clean up
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_STENCIL_TEST);

	// Anti aliasing
	if (_fxaa || _msaa)
	{
		_fbo->unbind();

		glViewport(0, 0, _width, _height);

		if (_fxaa)
		{
			_fxaaShader.bind();
			_fxaaShader.setUniform("invTexSize", vec2(1.0/_width, 1.0/_height));
			_fxaaShader.setUniform("screenTexture", 0);
		}
		else
		{
			_screenShader.bind();
			_screenShader.setUniform("screenTexture", 0);
		}

		_fbo->bindTexture(0);
		_fsQuad.render();

		_fbo->unbindTexture(0);
	}
}

Color RenderManager::getClearColor() const
{
	return _clearColor;
}

void RenderManager::setClearColor(const Color &clearColor)
{
	_clearColor = clearColor;
}

Color RenderManager::getAmbientColor() const
{
	return _ambientColor;
}

void RenderManager::setAmbientColor(const Color &ambientColor)
{
	_ambientColor = ambientColor;
}

bool RenderManager::getFXAA() const
{
	return _fxaa;
}

void RenderManager::setFXAA(bool fxaa)
{
	_fxaa = fxaa;
	if (!_fbo)
	{
		_fbo = new FrameBuffer(_width, _height);
	}
}

int RenderManager::getMSAA() const
{
	return _msaa;
}

void RenderManager::setMSAA(int msaa)
{
	_msaa = msaa;
	if (_fbo)
	{
		delete _fbo;
		_fbo = new FrameBuffer(_width, _height, msaa);
	}
}

UniformBufferObject &RenderManager::getUBO()
{
	return _ubo;
}

ST_NS_END

