#include "Skybox.h"
#include "Scene.h"
#include "Core/RenderManager.h"

ST_NS_BEGIN

Shader Skybox::_shader;

const GLfloat skyboxVertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

Skybox::Skybox(string fileName, string suffix)
{
	_cubemap = CubeMap::load(fileName, suffix);
	if (!_shader.isLoaded()) _shader = Shader(SHADER_PATH("Forward/Cubemap"));

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindVertexArray(0);
}

void Skybox::render() const
{
	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(_vao);
	_shader.bind();
	_cubemap->bind(0);

	const Camera *camera = Scene::activeCamera();
	mat4 view = camera->getProjection() * mat4(mat3(camera->getView()));

	_shader.setUniform("cubeViewProjection", view);
	_shader.setUniform("skybox", 0);
	_shader.setUniform("model", getModelTransform());

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}

const Material &Skybox::getMaterial() const
{
	return Material::null();
}

void Skybox::addToBatch(RenderBatch &batch)
{
	batch.addRenderable(this, mat4(0.0), 0);
}

bool Skybox::isVisible(const Frustum &frustum)
{
	return true;
}

ST_NS_END
