#include "UniformBufferObject.h"

ST_NS_BEGIN

UniformBufferObject::UniformBufferObject()
{
	glGenBuffers(1, &_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) + sizeof(vec3) + sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _ubo, 0, sizeof(glm::mat4) + sizeof(GLfloat));
}

UniformBufferObject::~UniformBufferObject()
{
	glDeleteBuffers(1, &_ubo);
}

void UniformBufferObject::update(const mat4 &viewProjection, const vec3 &cameraPosition, float time)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(viewProjection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(vec3), glm::value_ptr(cameraPosition));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4) + sizeof(vec3), sizeof(GLfloat), &time);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

ST_NS_END
